// Beginning of chi2 penalty code

// To set chi2 penalties based off quark PDF values at specific x and Q values,
// the x and Q values must be defined globally and not within fantomaschi2penalty()
// To use the value of a quark PDF, use pdfxfxqarray[lhafl]. The index number for each
// flavor LHAPDF ID is listed below
////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                        //
// *Key to using pdfxfxqarray[lhafl]*                                                     //
//                                                                                        //
// lhafl = 0:  tbar      								  //
// lhafl = 1:  bbar									  //
// lhafl = 2:  cbar									  //
// lhafl = 3:  sbar									  //
// lhafl = 4:  ubar									  //
// lhafl = 5:  dbar									  //
// lhafl = 6:  g									  //
// lhafl = 7:  d									  //
// lhafl = 8:  u									  //
// lhafl = 9:  s									  //
// lhafl = 10: c									  //
// lhafl = 11: b									  //
// lhafl = 12: t									  //
//                                                                                        //
////////////////////////////////////////////////////////////////////////////////////////////
double x_xfxq = 0.1;
double q_xfxq = sqrt(1.9);

int flindex(int fifl)
// Function to find the entry number based off flavor defined within steering_fantomas.txt
// Useful to define variables based off metamorph flavor ID.
// example:
// int ifl = 10; // define flavor by the ID given in the metamorph cards above
// int ikey = findKeyByValue(fifl); // define flavor array index using findKeyByValue and fifl
// double Af = Scm[ikey][0]; // define the normalization using ikey and j-th Scm value
////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                        //
// *Key to Scm[ifl][j] values*                                                            //
//                                                                                        //
// j = 0:       Normalization constant                                                    //
// j = 1,2:     Carrier parameters Sc(1) and Sc(2)                                        //
// j >= 3:      Modulator Sm parameters. j=3 corresponds to the value corresponding CP 1  //
//                                                                                        //
////////////////////////////////////////////////////////////////////////////////////////////
{
  for (int i = 0; i < iMet; i++)
  {
    if (iflavor[i] == fifl)
      return i;
  }
  
  // If no match is found, output warning and exit
  std::cout << "WARNING: ifl =  " << fifl << " is not defined in steering_fantomas.txt" << std::endl;
  std::cout << "Check that the flavor defined when using flindex in the chi2 penalty section of the "
               "steering_fantomas.txt file uses the correct fifl defined in the metamorph card section." 
            << std::endl;
  exit(3);
}

// Define initialize or define functions used within fantomaschi2penalty beforehand
double ReLU(double x);

double fantomaschi2penalty()
// *** Do not change name of function. ***
// This function is called for within the Fantomas module code to calculate the chi2 penalty defined below.
// Users are allowed to change the following code, as long as it returns a double value.
// Values that users can use in their penalties are listed below.
////////////////////////////////////////////////////////////////////////////////////////////
//											  //
// *List of allowed values to use within the following calculations*			  //
//											  //
// Scm[ifl][j]:  Map containing normalization, carrier, and modulator parameters	  //
// 		 ifl is defined as the metamorph flavor defined above.			  //
//		 j defines the specific parameter as defined above.			  //
// 			       		    	      		 	 		  //
// Ci[ifl][i]:   Map of Bezier coefficients Ci. The i-th Bezier coefficient is defined	  //
//   		 for all metamorphs.	    	    	 		       		  //
//		 The i-th Bezier coefficient for the metamorph defined by its		  //
//		 flavor above, ifl.	     	     	       	       	  		  //
//		 MetaRoster[ifl][i] where 0 < i < Nm					  //
//		 		    	      	  					  //
// pdfxfxqarray: The array which contains all 13 quark and g PDF values at x and q	  //
//   		 defined above. To use these values, x_xfxq and q_xfxq must be defined	  //
//		 globally.								  //
//		 									  //
// iMet:	 The total number of metamorphs used within the xFitter calculations.	  //
//											  //
// Nm[ifl]:	 The map containing the order of each metamorph.			  //
// 		 ifl is defined by the metamorph flavor ID defined above.		  //
//											  //
// iflavor[i]:   The array which contains all metamorph flavor IDs used within		  //
// 		 xFitter calculations.	      		       	   			  //
//		 Useful when calculating chi2 penalty contributions that include	  //
//		 all metamorphs. Flavors are listed in order of cards			  //
//											  //
// xFitterflag[i]: Flag which returns whether the metamorph flavor is used by xFitter	  //
// 		   flags are in order of metamorph cards above.	      	      		  //
//											  //
////////////////////////////////////////////////////////////////////////////////////////////
{
  // fantomas chi2 penalty value to return
  double fantochi2 = 0;
		
  std::cout << "iMet from fantomaschi2.C: " << iMet << std::endl;

  // variables used within the code locally
  int Nmtmp;
  int ifltmp;
  double w = 0.01;

  for (int i = 0; i < iMet; i++)
  {
    if (xFitterflag[i] == false)
    {
    }
    if (xFitterflag[i] == true)
    {
      ifltmp = iflavor[i];
      Nmtmp = Nm[ifltmp];
      std::cout << "Nm(" << ifltmp << ") = " << Nmtmp << std::endl;
      for (int j = 0; j < Nmtmp; j++)
      {
	std::cout << "Scm[" << ifltmp << "][" << j << "] = " << Scm[ifltmp][j] << std::endl;
	double Citmp = Ci[ifltmp][j];
	std::cout << "C[" << j << "] for ifl = " << ifltmp << ": " << Citmp << std::endl;
        //fantochi2 += (w/(Nmtmp+1)) * abs(log(abs(Citmp)));
        fantochi2 += ReLU(abs(Citmp)-10);
      }
    }
  }// for (int i = 0; i < iMet; i++)

  // lk24 added chi2 penalty when ubar>u and dbar>d around x=0.1 for low Q
  double w1 = 5.;
  double wud = 10.;

  for (int i = 0; i < 13; i++)
	  std::cout << pdfxfxqarray[i] << std::endl;

    //lk24 using lha ID notation, Iubar=5, Idbar=6, Id=8, Iu=9 (-1 since c++ starts at 0)
  // chi2 panelties prefer u(x>0.1)>ubar(x>0.1) and dbar(x>0.1)>d(x>0.1) (pi^+)
  double chiu = wud*ReLU(pdfxfxqarray[4]-pdfxfxqarray[8]);
  fantochi2 += chiu;

  double chid = wud*ReLU(pdfxfxqarray[7]-pdfxfxqarray[5]);
  fantochi2 += chid;

  double chiCg;
  //lk24 Scm[0][2] is Cg for the SU3 pion decomposition. chi2 penalty prefers -10<Cg<10.
  int gifl = 0;
  chiCg = w1*ReLU(abs(Scm[gifl][2])-10);
  fantochi2 += chiCg;

  return fantochi2;

}// fantomasconstrchi2()

// Define custom functions used within fantomasconstrchi2 if only initialized above

// lk24 added ReLU function to use in fantomas chi2 penalty
double ReLU(double x) {
  return std::max(0.0, x);
}

