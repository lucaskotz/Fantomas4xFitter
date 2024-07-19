#ifndef ADXMOMENT_H
#define ADXMOMENT_H

#include <iostream>
#include <math.h>
	
#define maxpts 20000

//===================================
//parameters that control the mapping
//===================================
double c = 0.2;
double p = 0.2;
int nold = 0;
double one = 1;
  
//--------------------------------------------------------------------------
double adxmoment(double (*F)(double x), int am, int npts=10000)
//replacement for adzint for number and momentum sum rule integrals
//--------------------------------------------------------------------------
//does integral of x**a *f(x)*dx over 0 < x < 1, for the sort of integrals 
//needed for momentum and number sum rules at Q0.  (jcp 6/24/01)
//
//uses mapping z = (x + c*x**p)/(1+c); and simple integration method in z. 
{
  double x0,z0,u,z,wt,x,y,ypri,sum;
  double xvec[maxpts], wvec[maxpts];
  if (am < 0)
  {
    std::cout << "STOP: adxmoment only works for non-negative powers of x" << "\n";
    std::cout << "am = " << am << "\n";
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
//**	      test = (x + c*x**p)/(one + c) - z
//**	      write(nout,210) iter, test, z, z0
//**210	      format(1x,'iter=',i2,' error=',e15.6,' z=',f9.6,
//**     &	                ' z0=',f9.6)

      xvec[i] = x;
      wvec[i] = wt * (one + c)/(one + c*p*pow(x,(p-one)));
	      
    }
  }

  //do the integral...
  sum = 0;
  for (int i = 1; i <= npts; i++)
  {
    x = xvec[i];
    sum = sum + pow(x,am) * F(x)*wvec[i];
  }
	
  return sum;
}

#endif	// ADXMOMENT_H
