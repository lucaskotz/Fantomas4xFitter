#ifndef METAMORPHCOLLECTION_H
#define METAMORPHCOLLECTION_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <map>
#include <string>
#include <cstring>
#include <algorithm>
#include "metamorph.h"
#include "fantomas.h"
#include "isNumber.h"

// lk22 changed maxSc from 2 to 3 to include normalization constant added to Carrier(x) in metamorph.h
const int maxSc = 3;	               // number of Sc variables for each flavor
//const int maxpars = 100;             // length of minuit pars list
const int maxMet = 10;	               // maximum number of flavors allowed by xFitter
const int maxctrlpts = 8;              // maximum number of control points for a given flavor
const int maxScm = maxSc + maxctrlpts; // maximum allowed values in array Scm
//bool xFitterCollectionSet = false;   // flag to determine if the Metamorph map has been created

class MetamorphCollection
// class object which contains functions are used to create, update,
// and return PDF values for a metamorph object corresponding to 
// specified flavors in the provided input card. Each metamorph object
// is created while reading the fantomas input cards. The metamorph
// objects are created inside the MetaVector, and then passed into
// MetaRoster as an element with iflavor mapped to it so the metamorph PDF
// values can be called for by particle ID.
{
private:
  std::vector <metamorph> MetaVector;    // Vector containing all metamorph objects for each flavor specified
  std::map <int, metamorph*> MetaRoster; // MetaRoster maps the flavor ID with the corresponding metamorph PDF
  std::map <int, int> iMetRoster;	 // Map of iMet to flavor ID to be used when updating parameters for given flavor

  int iMet = 0;	         // Number of metamorph functions
  int paraiMet = 0;      // variable used to select Scm parameters in MetamorphCollection::UpdateParameters()

  int iflavor[maxMet] = {0};  
  int Nm[maxMet] = {0};
  int MappingMode[maxMet] = {0};
  double xPower[maxMet] = {0};
  double Xs0[maxMet][maxctrlpts] = {{0}}, fp0[maxMet][maxctrlpts] = {{0}}, fm0[maxMet][maxctrlpts] = {{0}};
  double Xs[maxMet][maxctrlpts] = {{0}}, fp[maxMet][maxctrlpts] = {{0}}, fm[maxMet][maxctrlpts] = {{0}};
  std::string Scm0[maxMet][maxScm] = {{}};
  double Scm[maxMet][maxScm] = {{0}};
  // lk22 added vectors to help eliminate empty space for control points not used in calculations.
  std::vector<double> Xsvec;
  std::vector<double> fmvec;
  std::vector<double> fpvec;
  std::vector<double> Scmvec;

  double Xstmp[maxctrlpts] = {0};
  double Scmtmp[maxMet][maxScm] = {0};
  double fptmp[maxctrlpts] = {0};
  double fmtmp[maxctrlpts] = {0};

  std::string newflag = "NEW";	 // flag signaling to calculate PDF and use as control point for metamorph PDF
  std::string calcflag = "CALC"; // flag signaling to calculate PDF in the output card
  std::string fixflag = "FIX";	 // flag singlaing to use metamorph::Carrier(x) for control point in PDF calculation
  int k;			 // variable used to count the number of input control points for a given flavor
  int l;			 // variable used to count the number of control points used in a given metamorph
  int m;			 // variable used to count the number of control points for temporary metamorph
  int iPts[maxMet];	       	 // array containing # of entries for each flavor 

  // lk22 added strings to contain headers from fantomas card
  std::string flvheader[maxMet]; // array to store unique headers for each flavor in fantomas card
  std::string parsheader1;	 // header for first list of parameters in fantomas card
  std::string parsheader2;	 // header for second list of parameters in fantomas card

  bool xFitterflag[maxMet] = {false}; // array of flags. false = metamorph not called by xFitter. true = called by xFitter
public:
  MetamorphCollection()
  {   
    MetaVector.reserve(maxMet);
    Xsvec.reserve(maxScm);
    Scmvec.reserve(maxScm);
    fpvec.reserve(maxScm);
    fmvec.reserve(maxScm);
  } // MetamorphCollection constructor


  void PushMember()
  // MetamorpCollection::PushMember() is called inside the MetamorphCollection::ReadCard() function. 
  // The initial values read from MetamorphCollection::ReadCard() are used to create an initial metamorph
  // object inside the vector MetaVector. The boundary conditions are defined as well for the 
  // MetaVector element and then the Modulator function is calculated, allowing for the initial 
  // PDF values to be calculated.
  // The vector element is stored inside of MetaRoster, mapping the flavor and the metamorph object which will be used
  // to easily access the PDF value of any given flavor from the card. Scm is used to calculate the metamorph objects
  // instead of Scm0 since Scm will be updated by MetamorphCollection::UpdateParams() when xFitter varies the parameters 
  // Sc and Sm.
  {
    std::string flagcheck;

    // lk22 Added normalization into carrier function
    Scmtmp[iMet][0] = 1;	// Normalization in Carrier function defaults to 1 to build metamorph object
    for (int isc = 1; isc < maxSc; isc++) // loop copies Sc parameters read from ReadCard() to Scmtmp[iMet] array
    {
      double Sctmp = std::stod(Scm0[iMet][isc]);
      Scmtmp[iMet][isc] = Sctmp;
    }

    for (int i = 0; i < k; i++)
    // The for loop checks if Sm0 is a number. If Sm0 is found to be a number, then the 
    // input parameters for the corresponding control point will be pushed into a vector 
    // to eliminate empty entries caused by flagged points.
    // The vector calues  will be copied by the arrays used to calculate the metamorph 
    // objects for each flavor. 
    //
    // If Sm0 is not found to be a number, it will first check to see if it is set to the  
    // flag to return the metamorph PDF in the output card and not contribute to the metamorph.
    // If Sm0 is not set to the flag, the program will exit.
    {
      // lk22 Added routine to separate control points used for calculations from entire collective list            
      flagcheck = Scm0[iMet][i+maxSc];
      std::cout << "flagcheck = " << flagcheck << std::endl;

      if (isNumber(flagcheck) == true)
      {	
	Xstmp[i] = Xs0[iMet][i];
	Scmtmp[iMet][i+maxSc] = std::stod(flagcheck); // converts string to value
	fptmp[i] = fp0[iMet][i];
	fmtmp[i] = fm0[iMet][i];
	Xsvec.push_back(Xstmp[i]);
	Scmvec.push_back(Scmtmp[iMet][i+maxSc]);
	fmvec.push_back(fmtmp[i]);
	fpvec.push_back(fptmp[i]);

	l++;
	m++;
      } // if (isNumber(flagcheck == true)

      if (isNumber(flagcheck) == false)
      {
	if (flagcheck == calcflag)
	{
	  std::cout << "Flag detected to calculate metamorph PDF for x = " << Xs0[iMet][i] << "\n";
	  std::cout << "Metamorph value will be calculated in 'output/steering_fantomas_out.txt'" << std::endl;
	}
	else if (flagcheck == newflag)
	{
	  std::cout << "Flag detected to calculate metamorph PDF for x = " << Xs0[iMet][i] << "\n";
	  std::cout << Xs0[iMet][i] << " will be used as a control point in xFitter calculation" << std::endl;

	  Xstmp[i] = Xs0[iMet][i];
	  Scmtmp[iMet][i+maxSc] = 0; // Sm value will be calculated 
	  fptmp[i] = fp0[iMet][i];
	  fmtmp[i] = fm0[iMet][i];
	  
	  l++;
	}
	else if (flagcheck == fixflag)
	{
	  std::cout << std::endl << "Special value detected for control point x = " << Xs0[iMet][i] << std::endl;
	  std::cout << "Using metamorph::f(x) = Carrier(x) for control point." << std::endl;

	  Xstmp[i] = Xs0[iMet][i];
	  Scmtmp[iMet][i+maxSc] = -9999; // flags metamorph to use carrier function for metamorph value
	  fptmp[i] = fp0[iMet][i];
	  fmtmp[i] = fm0[iMet][i];
	  Xsvec.push_back(Xstmp[i]);
	  Scmvec.push_back(Scmtmp[iMet][i+maxSc]);
	  fmvec.push_back(fmtmp[i]);
	  fpvec.push_back(fptmp[i]);

	  l++;
	  m++;
	}
	else
	{
	  std::cout << "Flag not set to CALC/FIX/NEW in 'fantomas_steering.txt'. Make sure Sm(i) is either " \
	    "a number or set as CALC/FIX/NEW to calculate metamorph PDF at the control point without having it " \
	    "contribute to the metamorph PDF in xFitter." << std::endl;
	  exit(3);
	}
      } // if (isNumber(flagcheck) == false)
    } // for (int i = 0; i < k; i++)

    std::size_t newcheck;

    for (int i = maxSc; i < maxScm; i++) // check where the flag NEW is in the array Scm0, if any flagged points
    {
      newcheck = Scm0[iMet][i].find(newflag);
      if (newcheck != std::string::npos)
	break;
    }

    if (newcheck == std::string::npos)
    {
      for (int i = 0; i < k; i++)
      {
	Xs[iMet][i] = Xsvec[i];
	Scm[iMet][i+maxSc] = Scmvec[i];
	fm[iMet][i] = fmvec[i];
	fp[iMet][i] = fpvec[i];
      }
    }

    if (newcheck != std::string::npos)
    {
      int Nmtmp = Nm[iMet]-1;	// decreases Nm input value to calculate metamorph without NEW flagged control point
      double Xsmetatmp[maxctrlpts] = {0};
      double Scmmetatmp[maxScm] = {0};
      double fmmetatmp[maxctrlpts] = {0};
      double fpmetatmp[maxctrlpts] = {0};
      
      for (int i = 0; i < maxSc; i++)
	Scmmetatmp[i] = Scmtmp[iMet][i];

      for (int i = 0; i < m; i++)
      {
	Xsmetatmp[i] = Xsvec[i];
	Scmmetatmp[i+maxSc] = Scmvec[i];
	fmmetatmp[i] = fmvec[i];
	fpmetatmp[i] = fpvec[i];
      }

      metamorph metatmp(Nmtmp, Xsmetatmp, (Scmmetatmp+maxSc), Scmmetatmp, xPower[iMet]);
      metatmp.SetBoundary(MappingMode[iMet], fmmetatmp, fpmetatmp);
      metatmp.UpdateModulator();

      //lk23 Change Scmtmp to be for general case of f(x)=f_car(x)*F(f_mod(x))
      for (int i = 0; i < k; i++)
      {
	double xtmp = Xstmp[i];
	Scmtmp[iMet][i+maxSc] = metatmp.Modulator(xtmp)-1; // sets each Sm parameter to Pi for all control points
      }
    } // if (newcheck != std::string::npos)

    for (int i = 0; i < maxSc; i++)
      Scm[iMet][i] = Scmtmp[iMet][i];

    for (int i = 0; i < k; i++)
    {
      Xs[iMet][i] = Xstmp[i];
      Scm[iMet][i+maxSc] = Scmtmp[iMet][i+maxSc];
      fm[iMet][i] = fmtmp[i];
      fp[iMet][i] = fptmp[i];
    }

    //Scm[iMet][0] = -1+exp(Scmtmp[iMet][0]);
        
    MetaVector.emplace_back(Nm[iMet], (Xs[iMet]), (Scm[iMet]+maxSc), (Scm[iMet]), xPower[iMet]);
    MetaVector[iMet].SetBoundary(MappingMode[iMet], (fm[iMet]), (fp[iMet]));
    // MetaVector[paraiMet].UpdateModulator();
    MetaRoster.insert( std::pair<int, metamorph*>(iflavor[iMet], &(MetaVector[iMet])) );

    Xsvec.clear();
    Scmvec.clear();
    fpvec.clear();
    fmvec.clear();
  } // MetamorphCollection::PushMember()
  
  void ReadCard()
  // MetamorphCollection::ReadCard will read the input parameters for a given flavor in the fantomas steering card file. 
  // Xs, fp, fm, iflavor, MappingMode, and xPower are overwritten each loop after the MetamorphCollection::PushMember() 
  // function is called and will be stored internally in the metamorph object created using the inital values. Sm and Sc  
  // are stored in a 2-dimensional array. The values are stored for each metamorph function. The initial values of Sm 
  // and Sc will shifted by minuit within xFitter since they are treated as pointers inside the metamorph objects.  
  { 
    std::ifstream fantosteerin;
    
    const int lstr = 1000;	// define memory allocation for str
    char str[lstr];             // used to copy blocks of input params and be copied by stream
    std::string dummy;		// string to dump lines that won't be read
    std::stringstream stream(std::ios_base::app|std::ios_base::in|std::ios_base::out); // used to read blocks of params

    fantosteerin.open("steering_fantomas.txt", std::ifstream::in); // Open Fantomas steering card in xFitter
    // fantosteerin.open("../steering_fantomas.txt", std::ifstream::in); // Open Fantomas steering card in standalone
    if (!fantosteerin.is_open())
    {
      std::cout << "Unable to open Fantomas input file" << std::endl;
      exit(3); // Exit program if fantomas steering card cannot be found
    }

    if (fantosteerin.is_open())
    {
      while (!fantosteerin.eof())
      { 
	getline(fantosteerin,flvheader[iMet]); // stores card header of each loop
	getline(fantosteerin,parsheader1); // skips metamorph info header
	
	fantosteerin >> iflavor[iMet] >> Nm[iMet] >> MappingMode[iMet] \
		     >> xPower[iMet];
	for (int i = 1; i < maxSc; i++) 
	  fantosteerin >> Scm0[iMet][i]; // reads line containing minuit params

	fantosteerin.ignore();
	getline(fantosteerin,parsheader2); // skips initial metamorph param header

	fantosteerin.get(str,lstr,'#'); // copies entire block of input params into str to copy over to stream
	std::string strtemp;
	strtemp.assign(str);
	strtemp.pop_back(); // removes last empty line caused by delimiter in str
	stream.str(strtemp);	// copies string of input parameters into stringstream
      
	k = 0;			// resets number of input count
	l = 0;			// resets number of control point count
	m = 0;			// resets number of control point count for temporary metamorph (NEW flag only)
	while (!stream.eof()) 
	// while loop reads block of text of control point parameters in fantomas card. Each line in the
	// block of text is read line by line and the first two inputs are stored in Xstmp and Scmtmp.
	// isNumber() function checks if the input for Sm for a given control point is a number. If Scm is a 
	// number, then isNumber will return true where metamorph will use that control point to calculate
	// the metamorph function. If isNumber() returns false, Xs will be stored in XsCALC  to 
	// be used where the metamorph value will be calculated in the output card.
	{
	  std::string line;
	  std::stringstream streamtmp;
	  getline(stream, line); // reads next line in stream block.
	  streamtmp.str(line);	 // copies string line to stringstream to copy values over to variables.

	  // lk22 added if statements to assign default boundary conditions if no values are specified in input card.
          streamtmp >> Xs0[iMet][k] >> Scm0[iMet][k+maxSc];
	  if (streamtmp.eof())
	  {
	    fp0[iMet][k] = INFINITY;
	    fm0[iMet][k] = -1;
	  }
	  else if (!streamtmp.eof())
	    streamtmp >> fp0[iMet][k] >> fm0[iMet][k];
         
	  streamtmp.clear();

	  k++;
	} // while (!streamtmp.eof())

  
	memset (str, 0, lstr);      // clears current content in str
	strtemp.clear();       	    // clears current content in strtemp
	stream.clear();             // clears current content in stream

	PushMember();	// Creates metamorph object with parameters read from card and pushes it into vector and map

	if (l != Nm[iMet]+1)
	{
	  std::cout << "Error: The number of entries does not match with the specified Nm value for iflavor = " \
		    << iflavor[iMet] << " inside fantomas steering card" << std::endl;
	  exit(3);
	} // if (k != Nm)

	iMetRoster.insert( std::pair<int, int>(iflavor[iMet], iMet) );
	iPts[iMet] = k;

	++iMet;		// Adds to the count of Metamorph objects in card file

      } // while (fantosteerin.!eof())
	
    } //if (fantosteerin.is_open())

    fantosteerin.close();

    std::cout << "Fantomas intput card read successfully... \n" << std::endl;

  } // MetamorphCollection::ReadCard()

  void UpdateParameters(const int ifl, double *pars)
  // MetamorphCollection::UpdateParameters will be called every time xFitter updates the minuit parameters. 
  // Sc and Sm values are recalculated every update by adding the change from minuit to the initial value from the cards.
  // The initial value for each minuit parameter is set to 0 inside minuit.in.txt so that only the change is
  // added. metamorph::UpdateModulator() is called after the values are changed to recalculate the metamorph PDFs inside 
  // MetaVector, which will then update the elements in MetaRoster.
  {
    std::map<int,int>::iterator it;
    it = iMetRoster.find(ifl);	// iterator used to locate if there is an entry with iflavor = ifl

    if (it != iMetRoster.end())	// returns error if entry for ifl is not found
    {
    }
    else
    {
      std::cout << "Metamorph not found for iflavor = " << ifl << "\n"
		<< "Enter initial parameters in Fantomas steering card before continuing" << std::endl;
      exit(3);
    }
    
    paraiMet = iMetRoster[ifl];

      Scm[paraiMet][0] = pars[0];
      for (int i = 1; i < maxSc; i++)
	Scm[paraiMet][i] = Scmtmp[paraiMet][i] + pars[i];
      for (int i = 0; i < Nm[paraiMet]+1; i++)
	Scm[paraiMet][i+maxSc] = Scmtmp[paraiMet][i+maxSc] + pars[i+maxSc];

    //Scm[paraiMet][0] = -1+exp(Scmtmp[paraiMet][0] + pars[0]);
    if(Nm[paraiMet] == 0)
    {
    }
    if(Nm[paraiMet] != 0)
    {
      MetaVector[paraiMet].UpdateModulator();
    }

    xFitterflag[paraiMet] = true;

  } // Metamorph::UpdateParameters
  
  double f(const int ifl, const double x)
  // metamorph::f(x) will be called for and act on the specified metamorph object for a given
  // flavor ifl. ifl will be defined inside of xFitter when the fantomas PDF for a given flavor
  // is called for.
  {
    double ftmp;

    std::map<int,metamorph*>::iterator it;
    it = MetaRoster.find(ifl);	// iterator used to locate if there is an entry with iflavor = ifl

    if (it != MetaRoster.end())	// returns error if entry for ifl is not found
    {
    }
    else
    {
      std::cout << "Metamorph not found for iflavor = " << ifl << "\n"
		<< "Enter initial parameters in Fantomas steering card before continuing" << std::endl;
      exit(3);
    }
    // lk22 added norm to test sea fantomas parameterization error mismatch
    /*
    paraiMet = iMetRoster[ifl];

    const double b=Scm[paraiMet][0]+1;
    const double c=Scm[paraiMet][1]+1;
    double norm=exp(-lgamma(b)-lgamma(c)+lgamma(b+c));
    */
    ftmp = MetaRoster[ifl]->f(x); // metamorph::f(x) acting on specified metamorph object
    return ftmp;
    
  } // MetamorphCollection::f

  double MellinMoment(int ifl, int MellinPower, int npts=10000)
  {
    double momenttmp = MetaRoster[ifl]->GetMellinMoment(MellinPower,npts);
    // lk22 added norm to test sea fantomas parameterization error mismatch
    /*
    paraiMet = iMetRoster[ifl];

    const double b=Scm[paraiMet][0]+1;
    const double c=Scm[paraiMet][1]+1;
    double norm=exp(-lgamma(b)-lgamma(c)+lgamma(b+c));
    */
    return momenttmp;
  } // MetamorphCollection::MellinMoment

  //lk23 Added in function to return condition number of a specific metamorph flavor.
  double ConditionNumber(int ifl)
  {
    double condnumtmp = MetaRoster[ifl]->GetConditionNum();
    return condnumtmp;
  }

  double fantomasconstrchi2()
  // calculate the extra chi2 penalty induced by the constraint of 0<Ci~1.
  // routine will check if metamorph object has been called to be updated
  // by xFitter. If false, it will skip and go onto the next metamorph.
  // If true, then it will proceed with the calculation and add to final value.
  {
    double fantochi2 = 0;
    int Nmtmp;
    double Ci;
    int ifltmp;

    for (int i = 0; i < iMet; i++)
    {
      if (xFitterflag[i] == false)
      {
      }
      if (xFitterflag[i] == true)
      {
	Nmtmp = Nm[i];
	ifltmp = iflavor[i];
	for (int j = 0; j < Nmtmp+1; j++)
	{
	  Ci = MetaRoster[ifltmp]->Cs(j);
	  fantochi2 += abs(log(abs(Ci)));
	}
	double w = 0.01;
	fantochi2 *= (w/(Nmtmp+1))*fantochi2;
      }
    }// for (int i = 0; i < iMet; i++)
    
    return fantochi2;
    
  }// fantomasconstrchi2()

  void WriteCard()
  // Create an output card for Fantomas using the updated parameters of Sc and Sm.
  {
    std::ofstream fantosteerout;
    fantosteerout.open ("output/steering_fantomas_out.txt", std::ofstream::out);
    // fantosteerout.open ("../steering_fantomas_out.txt", std::ofstream::out); // used for standalone

    if (fantosteerout.is_open())
    {
      fantosteerout << "# Output card file of Fantomas steering card \n" << std::endl;
      for (int i = 0; i < iMet; i++)
      // output fantomas parameters into out card and loop over each input flavor
      {
	fantosteerout << flvheader[i] << std::endl;
 	fantosteerout << parsheader1 << std::endl;
	fantosteerout << iflavor[i] << "\t" << Nm[i] << "\t" << MappingMode[i] \
		      << "\t" << xPower[i] << "\t";
	for (int j = 1; j < maxSc; j++)            // loop that writes out all Sc parameter values
	  fantosteerout << Scm[i][j] << "\t";
	fantosteerout << std::endl;
	fantosteerout << parsheader2 << "\t f()" << std::endl; // header for metamorph parameters
	for (int j = 0; j < iPts[i]; j++)          // loop that writes out all metamorph parameter values
	{
	  // lk22 added routine to printout all control point PDF values.
	  fantosteerout << Xs0[i][j];

	  if (Scm0[i][j+maxSc] == calcflag)
	    fantosteerout << "\t" << (MetaRoster[iflavor[i]]->Modulator(Xs0[i][j]))-1;
	  else if (Scm0[i][j+maxSc] == fixflag)
	    fantosteerout << "\t" << fixflag;
	  else
	    fantosteerout << "\t" << Scm[i][j+maxSc];

	  if (fp[i][j] == INFINITY && fm[i][j] == -1 || fp[i][j] == 0 && fm[i][j] == 0)
	    fantosteerout << "\t" << "\t" << std::endl;
	  else if (fp[i][j] != INFINITY)
	    fantosteerout << "\t" << fp[i][j] << "\t" << fm[i][j] << std::endl;
	  
	  // lk22 added f() column after changing Sm to be Pi
	  // fantosteerout << "\t" << MetaRoster[iflavor[i]]->f(Xs0[i][j]) << std::endl;
	} // for (int j = 0; j < iPts[i]; j++)
      } // for (int i = 0; i < iMet; i++)
    } // if (fantosteerout.is_open())

    if (!fantosteerout.is_open())
      {
	std::cout << "Unable to open Fantomas output file" << std::endl;
	exit(3); // exit program if fantomas steering output card cannot be created
      }

    fantosteerout.close();

    std::cout << "\n Fantomas output card created successfully... \n" << std::endl;

  } // Writecard()

  void WriteC()
  {
    std::ofstream fantoCout;
    //lk22 added new C output card normalized to <xf>
    //std::ofstream fantonewCout;

    fantoCout.open ("output/fantomas_functional_parameters.txt", std::ofstream::out);

    if (fantoCout.is_open())
    {
      fantoCout << "# Output file containing the functional from each flavor \n" << std::endl;
      fantoCout << "# xf(x) = <xf>*x^Sc1*(1-x)^Sc2*(1+fbezier(x)) \n" << std::endl;
      for (int i = 0; i < iMet; i++)
      // output fantomas C coefficients into out card and loop over each input flavor
      {
	if (xFitterflag[i] == false)
	{
	}
	if (xFitterflag[i] == true)
	{
	  fantoCout << flvheader[i] << std::endl;
	  fantoCout << "<xf> = " << MellinMoment(iflavor[i],0) << std::endl;
	  for (int j = 1; j < maxSc; j++)            // loop that writes out all Sc parameter values
	    fantoCout << "Scm[" << j << "] = " << Scm[i][j] << std::endl;
	  fantoCout << std::endl;
	  for (int j = 0; j < Nm[i]+1; j++)
	  {
	    fantoCout << "C[" << j << "] = " << MetaRoster[iflavor[i]]->Cs(j) << "\n";
	  }//for (int j = 0; j < Nm[i]+1; j++) ->
	}//if (xFitterflag[i] == true) ->
      }//for (int i = 0; i < iMet; i++) ->
    }//if (fantoCout.is_open()) ->

    if (!fantoCout.is_open())
    {
      	std::cout << "Unable to open functional parameter file" << std::endl;
	exit(3); // exit program if fantomas bezier coefficients cannot be created
    }
    fantoCout.close();

    /*fantonewCout.open ("output/fantomas_modified_bezier_coefficients.txt", std::ofstream::out);

    if (fantonewCout.is_open())
    {
      fantonewCout << "# Output file containing the modified C coefficients from each flavor \n" << std::endl;
      double normtmp;		// overal normalization constant of metamorph
      double xf;		// momentum fraction of metamorph 
      double norm;		// coefficient to force normalization of metamorph to be <xf>
      for (int i = 0; i < iMet; i++)
      // output fantomas C coefficients into out card and loop over each input flavor
      {
	fantonewCout << flvheader[i] << std::endl;
	normtmp = Scm[i][0];
	xf = MellinMoment(iflavor[i],0); // 1st Mellin moment due to xf(x) being parameterized
	norm = normtmp/xf;
	for (int j = 0; j < Nm[i]+1; j++)
	{
	  fantonewCout << "C[" << j << "] = " << norm*MetaRoster[iflavor[i]]->Cs(j) << "\n";
	}
      }
    } 
    if (!fantonewCout.is_open())
    {
      	std::cout << "Unable to open modified Bezier coefficient file" << std::endl;
	exit(3); // exit program if fantomas bezier coefficients cannot be created
    }
    */
  } // WriteC()
  ~MetamorphCollection()
  {
    std::map<int,metamorph*>::iterator it;
    for(it = MetaRoster.begin(); it != MetaRoster.end(); ++it)
      MetaRoster.erase(it);
    MetaVector.clear();
    iMetRoster.clear();
  }
}; // class MetamorphCollection

#endif
