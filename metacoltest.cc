// metacoltest: A propgram to test the basic features of the MetamorphCollection
//              class object defined within MetamorphCollection.h.
//
// Author: Lucas Kotz
//
// Description: metacoltest.cc is compiled via the "make" command. Once compiled,
//              metacoltest.x can be run. The metacoltest.x executable aims to
//              mimic the steps performed within the xFitter Fantomas module
//              without the need to run xFitter. Specifics on the variables,
//              routines, and functions within metacoltest.x are described in the
//              comments of the corresponding sections. 
#include <cmath>
#include <iostream>
#include "fantomas.h"
#include <random>

using namespace std;

int main()
{
  // number of flavors used
  int Nfl = 3;
  // set flavor IDs to those defined within steering_fantomas.txt
  int iflg = 0;
  int iflS = 1;
  int iflV = 2;
  // define the order of the metamorphs (number of CPs in steering_fantomas.txt minus 1)
  int Nmg = 2;
  int NmS = 3;
  int NmV = 3;
  // define the total number of parameters
  int ng = 6;
  int nS = 7;
  int nV = 7;
  // create empty arrays used to shift initial metamorph parameter values
  double deltag[ng+1] = {0};
  double deltaS[nS+1] = {0};
  double deltaV[nV+1] = {0};
  // set normalizations to 1 for all flavors
  deltag[0] = 1;
  deltaS[0] = 1;
  deltaV[0] = 1;
  // Initialize flags used for MetamorphCollection to track which flavors are used
  bool xFitterCollectionSet = false;
  bool xFitterModulatorSet[Nfl] = {false};

  // read the steering_fantomas.txt card file using the functiong from fantomas.cc
  cout << "Reading steering_fantomas.txt..." << endl;
  readfantosteer();
  xFitterCollectionSet = true;
  cout << "steering_fantomas.txt card read successfully. \n" << endl;

  // update parameters for all metamorph flavors using the function from fantomas.cc
  cout << "Setting delta parameters..." << endl;
  updatefantopars(iflg,deltag);
  updatefantopars(iflS,deltaS);
  updatefantopars(iflV,deltaV);
  cout << "delta parameters set. \n" << endl;

  // print out momnentum fractions for each flavor
  // metamorph functions are for xf(x,Q). momentum fraction require n=0 here. This prescription follows the one we use in xFitter.
  int Mellinxf = 0;
  int Mellinf = -1;
  double momg; double momS; double momV;
  momg = fantoMellinMoment(iflg,Mellinxf); momS = fantoMellinMoment(iflS,Mellinxf); momV = fantoMellinMoment(iflV,Mellinxf); 
  double iV = fantoMellinMoment(iflV,Mellinf);

  cout << "Momentum fractions below may not satisfy the momentum sum rule. Metamorph functions are not normalized yet." << endl;
  cout << "<xg> = " << momg << endl;
  cout << "<xS> = " << momS << endl;
  cout << "<xV> = " << momV << endl;
  cout << "<V> = " << iV << endl;

  // Normalize metamorph functions
  // One of the normalizations is a free parameter. Here, S is chosen to be free. Then, update each flavor and recalculate momentum fractions
  cout << "\n Normalizing metamorph functions..." << endl;
  
  double AS = 0.89;
  deltaS[0] = AS;
  updatefantopars(iflS,deltaS);
  momS = fantoMellinMoment(iflS,Mellinxf);

  if (momS < 0 || momS > 1)
  {
    cout << "<xS> is not physical. Change steering_fantomas.txt values in the Sea metamorph card." << endl;
    exit (3);
  }
  
  // AV*<v>=2
  double AV = 2 / iV;
  deltaV[0] = AV;
  updatefantopars(iflV,deltaV);
  momV = fantoMellinMoment(iflV,Mellinxf);
  iV = fantoMellinMoment(iflV,Mellinf);
  
  // Ag*<xg> + AS*<xS> + AV*<xV> = 1
  double Ag = (1 - momS - momV) / momg;
  deltag[0] = Ag;
  updatefantopars(iflg,deltag);
  momg = fantoMellinMoment(iflg,Mellinxf);

  cout << "Normalization complete. \n" << endl;

  cout << "momentum fractions after normalization: " << endl;
  cout << "<xg> = " << momg << endl;
  cout << "<xS> = " << momS << endl;
  cout << "<xV> = " << momV << endl;
  cout << "<V> = " << iV << endl;
  cout << "total momentum: " << momg + momS + momV << endl;

  // define array of test point to print out the metamorph value at.
  int Nxtest = 10;
  double xtest[Nxtest];
  for (int i = 0; i < Nxtest; i++)
    xtest[i] = (1 - 0.001) / Nxtest * i + 0.001;

  cout << "Printing out metamorph values at test points..." << endl;
  for ( int i = 0; i < Nxtest; i++)
  {
    double xfg = fantopara(iflg, xtest[i]);
    double xfS = fantopara(iflS, xtest[i]);
    double xfV = fantopara(iflV, xtest[i]);
    cout << "xg(" << xtest[i] << ") = " << xfg << endl;
    cout << "xS(" << xtest[i] << ") = " << xfS << endl;
    cout << "xV(" << xtest[i] << ") = " << xfV << "\n" << endl;
  }
  cout << "Finished printing out metamorph values at test points.\n" << endl;

  // calculate the chi2 defined by fantomaschi2.h. set the local variable fantochi2 to the chi2 calculated.
  //lk25 commented out because calculating chi2 from fantomaschi2.h this way causes segmentation fault.
  //cout << "Calculating chi2 from fantomaschi2.h..." << endl;
  double fantochi2 = 0;
  //getfantochi2(fantochi2);
  //cout << "Fantomas chi2 = " << fantochi2 << endl;
  //cout << "Finished printing out fantomaschi2.h chi2.\n" << endl;

  // print all output files into output/ directory
  cout << "Creating Fantomas output files..." << endl;
  writefantoout(fantochi2);
  cout << "Finished writing Fantomas outputs.\n" << endl;
  
  // Shift the metamorph parameters by a random amount between 0 and 1
  // The first and last CPs for each flavor are fixed.
  // Below routine only changes Sc(1) and Sc(2), and the non-fixed CPs.
  cout << "Changing metamorph parameters...\n" << endl;
  random_device rd;
  mt19937 gen(rd()); // Mersenne Twister engine
  uniform_real_distribution<> dis(0.0, 1.0); // Range [0, 1)

  for (int i = 1; i < 3; i++)
    deltag[i] = dis(gen);
  for (int i = 1; i < 3; i++)
    deltaS[i] = dis(gen);
  for (int i = 1; i < 3; i++)
    deltaV[i] = dis(gen);

  // change the non-fixed CPs
  for (int i = 1; i < Nmg; i++)
    deltag[i+3] = dis(gen);
  for (int i = 1; i < NmS; i++)
    deltaS[i+3] = dis(gen);
  for (int i = 1; i < NmV; i++)
    deltaV[i+3] = dis(gen);

  // print out delta values
  for (int i = 0; i < ng; i++)
    cout << "deltag[" << i << "] = " << deltag[i] << endl;
  for (int i = 0; i < nS; i++)
    cout << "deltaS[" << i << "] = " << deltaS[i] << endl;
  for (int i = 0; i < nV; i++)
    cout << "deltaV[" << i << "] = " << deltaV[i] << endl;
  
  // Update metarmophs with new parameters
  cout << "Updating metamorphs..." << endl;
  updatefantopars(iflg,deltag);
  updatefantopars(iflS,deltaS);
  updatefantopars(iflV,deltaV);
  cout << "metamorphs updated with shifted values. \n" << endl;

  iV = fantoMellinMoment(iflV,Mellinf);
  momV = fantoMellinMoment(iflV,Mellinxf);
  momS = fantoMellinMoment(iflS,Mellinxf);
  momg = fantoMellinMoment(iflg,Mellinxf);
  
  cout << "Normalizing metamorphs with updated values..." << endl;
  AS = 0.89;
  updatefantopars(iflS,deltaS);
  momS = fantoMellinMoment(iflS,Mellinxf);
  
  // AV*<v>=2
  AV = 2 / iV;
  deltaV[0] = AV;
  updatefantopars(iflV,deltaV);
  momV = fantoMellinMoment(iflV,Mellinxf);
  iV = fantoMellinMoment(iflV,Mellinf);

  // Ag*<xg> + AS*<xS> + AV*<xV> = 1
  Ag = (1 - momS - momV) / momg;
  deltag[0] = Ag;
  updatefantopars(iflg,deltag);
  momg = fantoMellinMoment(iflg,Mellinxf);

  cout << "Normalization complete. Results may not be physical as delta parameters are randomly generated.\n If they are not physical, or the sum rules are not obeyed, run metacoltest.x again.\n" << endl;

  cout << "momentum fractions after normalization: " << endl;
  cout << "<xg> = " << momg << endl;
  cout << "<xS> = " << momS << endl;
  cout << "<xV> = " << momV << endl;
  cout << "<V> = " << iV << endl;
  cout << "total momentum: " << momg + momS + momV << endl;

  cout << "Printing out updated metamorph values at test points..." << endl;
  for ( int i = 0; i < Nxtest; i++)
  {
    cout << "xg(" << xtest[i] << ") = " << fantopara(iflg, xtest[i]) << endl;
    cout << "xS(" << xtest[i] << ") = " << fantopara(iflS, xtest[i]) << endl;
    cout << "xV(" << xtest[i] << ") = " << fantopara(iflV, xtest[i]) << "\n" << endl;
  }
  cout << "Finished printing out updated metamorph values at test points.\n" << endl;

  // calculate the chi2 defined by fantomaschi2.h. set the local variable fantochi2 to the chi2 calculated.
  //cout << "Recalculating chi2 from fantomaschi2.h..." << endl;
  //getfantochi2(fantochi2);
  //cout << "Updated Fantomas chi2 = " << fantochi2 << endl;
  //cout << "Finished printing out fantomaschi2.h chi2.\n" << endl;  
  
  // print all output files into output/ directory
  cout << "Creating updated Fantomas output files..." << endl;
  writefantoout(fantochi2);
  cout << "Finished writing updated Fantomas outputs.\n" << endl;
  
}
