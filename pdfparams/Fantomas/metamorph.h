/*****************************************************************
 *
 *     Program: Fantomas
 *
 *     Advanced parametrizations of nonpertubative QCD functions
 *
 *     Version Summer 2021
 *
 *    Description: the metamorph parametrization class
 *
 ******************************************************************
 */

#ifndef METAMORPH_H
#define METAMORPH_H

#include <iostream>
#include <cmath>
#include <math.h>
#include <fstream>
#include <omp.h>
#include <cstddef>
#include "cl2DArray.h"
#include "LUPinverse.h"

//========================================================================
// Auxiliary functions
//========================================================================

double DefCarrier(double x, double *a)
// The default carrier function. The input parameters are the momentum fraction x and a pointer to the array a with control parameters.
{
  return a[0]*pow(x,a[1])*pow(1.0 - x, a[2]);
}//DefCarrier ->


long int bic(int Nm, int k)
//Binomial coefficient C^Nm_k
{
  
  if (k > Nm)
    return 0;
  if (k == 0 || k == Nm)
    return 1;
  
  // Recur
  return bic(Nm - 1, k - 1)
    + bic(Nm - 1, k);
  
}//bic-> 


//========================================================================
// Class definitions
//========================================================================

class ControlPoint
//Defines a control point at position x, with the value f returned dependent on the control partmeter s in the interval fm <= 0 <= fp. 
{
public:
  double x;  //x position of the control point
  double *ps; //Pointer to an external parameter that will control the value of the function f
  double fm=0.0, fp=INFINITY; //minimal and maximal values of function f
  //MappingMode determines how the value of f is determined, given s.
  //MappingMode=0: no scaling
  //                         1: bounded linear scaling
  //                         2: bounded softsign scaling
  int  MappingMode=0; 
  
  int SetBoundary(int MappingModeIn=0,
		  double fmin=0.0, double fpin=INFINITY)
  {
    MappingMode=MappingModeIn;
      
    fm=fmin; fp=fpin; 
    if (fm >= fp)
      {
	std::cout << "STOP: wrong boundaries in ControlPoint. fm = "<<fm << " > fp ="<<fp<<std::endl;
	exit(3);
      }

    return 1;
  }//ControlPoint::SetBoundary->

  ControlPoint(double xin, double &psin, int MappingModeIn=0,
               double fmin=0.0, double fpin=INFINITY)
    {
      x=xin; ps= &psin;
      SetBoundary(MappingModeIn, fmin, fpin);
      
    }//constructor ControlPoint::ControlPoint ->

  double s()
  { return *ps;}
  
  double f()
    //the value of the function at the control point, given the parameter s
  {
    double sf=*ps, ftmp;
      
    switch (MappingMode)
      {
      case 0: //no scaling
        ftmp=sf;
        break;
      case 1: //bounded linear scaling
	ftmp = (fp+fm)/2.0 + (fp-fm)*sf/2.0;
        break;
      case 2: //bounded softsign scaling
        // Given a variable s in the interval (-infinity, +infinity), returns
        // a value in the interval f1m <= f <= fp. Softsign is approximately
        // linear in the interval -1 < s < 1 and is equal to (fp+fm)/2 for s=0.
	ftmp = (fp+fm)/2.0 + (fp-fm)*sf/(1.0+fabs(sf))/2.0;
        break;
      default:
        std::cout << "STOP in ControlPoint: mapping mode "<<MappingMode<<" is not implemented" <<std::endl;
        std::cout << "x = "<<x<<", s = "<<sf<<std::endl;
        exit(2);
      }//switch MappingMode

    // lk22 added display messages when using special value for control point
    //Check the boundaries and flagged values
    if ( sf == -9999)
    {
      ftmp = sf;
    }
    if (ftmp < fm ||  ftmp > fp)
      {
	if (ftmp != -9999)
	{
	  std::cout << std::endl << "The returned function is out of bounds  in ControlPoint::f" << std::endl;
	  std::cout << "The functions and the bounds are "<< fm <<" < " << ftmp << " < " << fp << std::endl; 
	}
      }

    return ftmp;

  }//ControlPoint::f->    
  
}; //class ControlPoint->

double DefCarrier(double x, double *a); //forward declaration for DefCarrier

//====================================================
class metamorph
/* metamorph provides a PDF parametrization dependent on the momentum fraction x of the form
          f(x) = Carrier(x, Sc)*Modulator(x, Sm),
    where 
    Carrier defines the asymptotic behavior of f(x) in the limits x->0 and x->1;
    Modulator(x,Sm) determines the behavior of f(x) over the interval 0 < x < 1.
    Carrier(x, Sc) is a smooth function dependent on the array of external parameters 
    Sc[], such as Carrier = x^Sc(0)*(1-x)^Sc(1).
    Modulator is given by a Bezier curve of order Ncp-1 that depends on x^xPower as its 
    argument, where default xPower=0.5.
    The shape of Modulator(x, Sm) is controlled by  external parameters Sm[] that set the 
    value of f(x) at Ncp user-selected control points CP at discrete x values Xs[0], Xs[1], ..., Xs[Ncp-1].
    Internally, Modulator(x, Sm) is controlled by a locally stored vector of Bezier coefficients C. 
    UpdateModulator() must be called every time the external parameters Sm are changed to update the vector C 
    before the function f(x) is called. 
    The metamorph can be constructed so that the  values of its f(x) at the control points are 
    constrained to lie within the interval fm(Xs[i]) <= f(Xs[i]) <= fp(Xs[i]), where fm(x) and fp(x)
    are the functions provided via the constructor of metamorph. 
*/
{ 
  int Nm; //numbers of free parameters in the carrier and modulator functions
  std::vector <ControlPoint> CP; //Control points for the modulator function
  std::vector <double> Xs; //X-value inputs
  double xPower;  //the modulator function has x^xPower as its argument
  double *pSc;     // pointer to an external array with parameters of the modulator function
  cl2DArray<double> *M = NULL, *InvM = NULL; //Matrices M and T for the modulator function, and their inverse matrices
  cl2DArray<double> *T = NULL, *InvT = NULL, *multi=NULL;
  double *C, *P;     //Bezier coefficients of the modulator function and a vector of corresponding parameters
  int *Pdec;
  
  double (*Carrier)(double, double*); //a pointer to the carrier function. Points to function DefCarrier by default. 
  bool ModulatorSet = false;

public:
  
  metamorph(int Nmin, const double Xsin[], double Smin[], double Scin[], double xPowerIn = 0.5, double (*CarrierIn)(double, double *)=&DefCarrier)
    // Constructor: construct a metamorph class by reading Nm values from an 
    // input array xS and setting control point parameters to point to an array of external variables Sm.
    // Also provide a pointer to the array Sc containing the parameters for the carrier function. DefCarrier is the 
    // default carrier function. An optional input parameter is a pointer to an alternative carrier function.   
    {  
      pSc = Scin;
      Carrier=CarrierIn; //set the pointer to the carrier function, given by DefCarrier unless specified otherwise;
      Nm = Nmin;
      xPower = xPowerIn;
    
      for (int i = 0; i < Nm+1; i++)
	Xs.push_back(Xsin[i]);

      // lk22 Added flag check to set control point value to Carrier function
      for (int i = 0; i < Nm+1; i++)
	if (Smin[i] == -9999)
	  //lk22 Changed Sm from metamorph value to Modulator value
	  Smin[i] = 0;

      //lk23 changed Xs[i] to use xstretch from Pavel
      double xstrmin = 1e-3; double xstrmax=0.85;
      double XsPow[Nm+1];
      double innerPower = 1.0 / 6.0;
      for (int i = 0; i < Nm+1; i++)
      {
	double base = 1.0 / (1.0 / (pow(Xs[i], 6.0) + pow(xstrmin, 6.0)) + (1.0 - pow(xstrmax, 6.0)) / pow(xstrmax, 6.0));
	double intermediateResult = pow(base, innerPower);
	double finalResult = pow(intermediateResult, xPower);
	XsPow[i] = finalResult;
      }
    
      for (int icp = 0; icp < Nm+1; icp++)
	//lk22 Changed Sm from metamorph value to Modulator value
	CP.push_back(ControlPoint(XsPow[icp],Smin[icp]));
        
      //factorial and binomial coefficeint calculation

      //matrix T, M
      M = new cl2DArray<double>(Nm+1,Nm+1); 
      InvM = new cl2DArray<double>(Nm+1,Nm+1);
      T = new cl2DArray<double>(Nm+1,Nm+1); 
      InvT = new cl2DArray<double> (Nm+1,Nm+1); 
      multi= new cl2DArray <double> (Nm+1,Nm+1);
    
      for (int i= 0; i<Nm+1; i++)
	for (int j=0; j<Nm+1; j++)
	  {
	    (*T)(i,j) = pow(XsPow[i],j);
	    if (i<=j)
	      (*M)(j,i) = pow(-1, j-i)*bic(Nm,i)*bic(Nm-i, Nm-j);
	    else
	      (*M)(j,i) = 0.0;
	  }//for (int j=0...

      C = new double[Nm+1];
      P = new double[Nm+1];
      Pdec = new int[Nm+2];
      LUPDecompose(M, Nm+1, 1.0e-10, Pdec);
      LUPInvert(M, Pdec, Nm+1, InvM);//Calculate Inverse of M

      LUPDecompose(T, Nm+1, 1.0e-10, Pdec);
      LUPInvert(T, Pdec, Nm+1, InvT);//Calculate Inverse of T
      
    } // constructor metamorph::metamorph  -> 

  int SetBoundary(int MappingModeIn, double fmin[], double fpin[])
  {
    int j=0;
    for (std::vector<ControlPoint>::iterator it = CP.begin() ; it != CP.end(); it++)
      {
	it->SetBoundary(MappingModeIn, fmin[j], fpin[j]);
	j++;
      }

    return 1;
  }//metamorph::SetBoundary->

  void UpdateModulator()                    
    //Compute C, given the carrier function Fc, InvM and InvT. This computation is done every time 
    // the control points are updated, and before the metamorph value f is computed
    // for varied x values. We write the PDF function as f(x_i)=Fc(x_i)*Fm(x_i), where Fc is the carrier,
    // Fm is the modulator.
    // A control point returns f_i with f_-i < = f_i < = f_+i. Then we have f_i = Fc_i * Fm_i. 
    // The vector of Bezier coefficients C is computed as C=InvM.InvT.P, where P is the vector of P_i = Fm(x_i).
  {
    double Ci;
    //The value of each vector P element is the f() value of each element of the CP vector divided by
    // the carrier function at the x() value
    for (int ix = 0; ix < Nm+1; ix++)
      {
	double Car[Nm+1];
	double modtmp[Nm+1];
	Car[ix] = (*Carrier)(Xs[ix], pSc);
	// lk22 added if statement to set CP.f() = Carrier when calling for metamorph::UpdateModulator() 
	// since Sm will default back to -9999 when function is called for in each iteration in xFitter
	//lk22 Changed Sm from metamorph value to Modulator value
	if (CP[ix].f() == -9999)
	  modtmp[ix] = 0;
	else
	  modtmp[ix] = CP[ix].f();
	P[ix]=modtmp[ix];
      }
  
    for (int i = 0; i < Nm+1; i++)
      for (int j = 0; j < Nm+1; j++)
	{
	  (*multi)(i,j) = 0.0;
	  for (int k = 0; k < Nm+1; k++)
	    (*multi)(i,j) += (*InvM)(i,k)*(*InvT)(k,j);
	}//InvM.InvT ->
      
    for (int i = 0; i < Nm+1; i++)
      {
	Ci = 0.0;
	for (int k = 0; k < Nm+1; k++)
	  Ci += (*multi)(i,k) * P[k];
	C[i]=Ci;
      }//C=InvM.InvT.P->

    ModulatorSet = true;

  }//UpdateModulator->            
 
  double Cs (int i)
    // Return the value for the ith Bezier coefficient
  {
    double Ci;
    Ci = C[i];
    return Ci;
  }//double C ->
 
  double Modulator(double x)
    // Return the value of the Modulator function for the momentum fraction x
  {
    // lk22 changed modulator function from B_(n,l)(x) to 1+B_(n,l)(x) with B=0 for Nm=0 
    double mod = 1.0;
    //lk23 implemented xstretching into modulator function.
    double xstrmin = 1e-3; double xstrmax=0.85;
    double base = 1.0 / (1.0 / (pow(x, 6.0) + pow(xstrmin, 6.0)) + (1.0 - pow(xstrmax, 6.0)) / pow(xstrmax, 6.0));
    double innerPower = 1.0 / 6.0;
    double intermediatexstretch = pow(base, innerPower);
    double finalxstretch = pow(intermediatexstretch, xPower);
    if (Nm != 0)
    {
      for (int im = 0; im < Nm+1; im++)
	mod += C[im]*bic(Nm,im)*pow(finalxstretch,im)*pow(1-finalxstretch,Nm-im);
    }
    if (Nm == 0)
    {
    }
    return mod;
  }//double Modulator->
      
  double f(double x)
    // Return the value of the metamorph for the momentum fraction x
  { 
    double ftmp;
    
    /*if (!ModulatorSet)
      {
	std::cout << "Modulator not set" << std::endl;
	exit(3);
      }
    */
    double fp = 100;
    double fm = 0;
    double smod = Modulator(x);
    double modtmp = smod;
    //double modtmp = (fp+fm)/2.0 + (fp-fm)*smod/(1.0+fabs(smod))/2.0;
    //double modtmp = exp(smod);
    ftmp= (*Carrier)(x,pSc)*modtmp;
    return ftmp;
  }//f->

  /*static metamorph *CurrentMetamorph=NULL; // metamorph pointer  to use in external functions within metamorph.h

  static double CurrentF(double x)
  {
    if (CurrentMetamorph == NULL)
      return 0.0;
    else
      return CurrentMetamorph->f(x);
  } // metamorph::CurrentF
  */
  //tbd void SetModulatorXPower(double xPowerIn); //Set xPower, recompute T if necessary
  //tbd  SetCustomCarrier(double *CarrierIn); //Set a pointer to a custom carrier function
  //tbd double GetModulatorXPower();    //Get the value of xPower

  double GetMellinMoment(int MellinPower,int npts = 10000)
  // metamorph::GetMellinMoment() uses the adxmoment function by Jon Pumplin. Preforms the
  // integral of x^a * f(x) * dx over 0 < x < 1, for the sort of integrals 
  //needed for momentum and number sum rules at Q0.
  //
  //uses mapping z = (x + c*x**p)/(1+c); and simple integration method in z.
  {
    //CurrentMetamorph = this;
    //return adxmoment(&(metamorph::CurrentF),MellinPower,npts);
    int maxpts = 20000;
    double c = 0.2;
    double p = 0.2;
    int nold = 0;
    double one = 1;
    double x0,z0,u,z,wt,x,y,ypri,sum;
    double xvec[maxpts], wvec[maxpts];
    if (MellinPower < -1)
    {
      std::cout << "STOP: adxmoment only works for non-negative powers of x" << "\n";
      std::cout << "MellinPower = " << MellinPower << "\n";
      exit(3);
    }
    
    //compute the points and weights on first call, or if npts has changed...
    if(npts != nold)
    {
      if(npts < 10 || npts > maxpts)
      {
	std::cout << " adxmoment:  fatal npts= " << npts << std::endl;
	exit(3);
      }
      
      nold = npts;
      
      //find z0 as point where x and c*x**p are equal...
      x0 = pow(c,(one/(one-p)));
      z0 = (x0 + c*pow(x0,p))/(one + c);
      
      for (int i = 1; i<=npts; i++)
      //formerly used equal spacing in z...
      //            z = (i - 0.5d0)/float(npts)
      //            wt = one/float(npts)
      //changed to equal spacing in u = sqrt(1-z), which should allow 
      //mild singularity at z->1, i.e., at x->1. (jcp 12/02)
      {
	u = (i - 0.5)/(double)npts;
	z = 1 - pow(u,2);
	wt = 2*u/(double)npts;
      
	//get starting estimate by asymptotic forms...
	if(z < z0)
	{
	  x = pow((z*(one+c)/c),(one/p));
	}
	else
	{
	  x = one - (one-z)*(one+c)/(one+p*c);
	}
	    
	//solve z = (x + c*x**p)/(1 + c) for x by Newton's method...
	for (int iter = 1; iter <= 9; iter++)
	{
	  y = x + c*pow(x,p) - (one+c)*z;
	  ypri = one + c*p*pow(x,(p-one));
	  x = x - y/ypri;
	  if((iter > 5) && (abs(y) < 1.e-10))
	  {
	    goto label;
	  }   
	}
	
	std::cout << " " << "adxmoment: fatal convergence " << y << " " << z << " " << x << std::endl;
	exit(3);
	
      label:
	         
	//**** FOR TESTING ****
	//**      test = (x + c*x**p)/(one + c) - z
	//**      write(nout,210) iter, test, z, z0
	//**210      format(1x,'iter=',i2,' error=',e15.6,' z=',f9.6,
	//**     &                ' z0=',f9.6)
	
	xvec[i] = x;
	wvec[i] = wt * (one + c)/(one + c*p*pow(x,(p-one)));
	
      }
    }

    //do the integral...
    sum = 0;
    for (int i = 1; i <= npts; i++)
    {
      x = xvec[i];
      sum = sum + pow(x,MellinPower) * f(x)*wvec[i];
    }
    
    return sum;
  } // metamorph::GetMellinMoment

  //lk23 Added in a function to return the condition number of matrix T.
  double GetConditionNum()
  // Returns the condition number of the matrix T and T^{-1} using the Frobenius-norm.
  // Frobenius-norm, ||T||, is the square root of the sum of absolute squares of the elements.
  // The condition number is calculated as ||T|| * ||T^{-1}||. 
  {
    double abst = 0;
    double absInvt = 0;
    double T2 = 0;
    double InvT2 = 0;
    double Tnorm = 0;
    double InvTnorm = 0;
    double CondNum = 0;
    
    for (int i = 0; i < Nm+1; i++)
      for (int j = 0; j < Nm+1; j++)
      {
	abst = abs((*T)(i,j));
	absInvt = abs((*InvT)(i,j));
	T2 += pow(abst,2);
	InvT2 += pow(absInvt,2);
      }

    Tnorm = sqrt(T2);
    InvTnorm = sqrt(InvT2);

    CondNum = Tnorm * InvTnorm;

    return CondNum;
  }

  // tbd void SetNormalization(double MellinMoment); 
  //Given a Mellin Moment of the metamorph, re-compute the normalization of the metamorph

  ~metamorph()
    {
      std::cout << "Destructing metamorph:\n";
      delete[] P;
      std::cout << "Deleted P in metamorph:\n";
      delete[] C;
      std::cout << "Deleted C in metamorph:\n"; 
      delete[] Pdec;
      std::cout << "Deleted Pdec in metamorph:\n";
  
      delete M;
      std::cout << "Deleted M in metamorph:\n";
      delete InvM;
      std::cout << "Deleted InvM in metamorph:\n";
      delete T;
      std::cout << "Deleted T in metamorph:\n";
      delete InvT;
      std::cout << "Deleted InvT in metamorph:\n";
      delete multi;
      std::cout << "Deleted multi in metamorph:\n";

    }//~metamorph
  
};//class metamorph -> 


#endif //METAMORPH_H
