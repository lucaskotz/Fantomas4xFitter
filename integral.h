/*
                          LEGACY
        Program to generate grids for the resummation
               in vector boson production
                             C++ version 2.4.2
                     Unit: integral.h

            Developed by the High Energy Physics Theory Group
                  at the Michigan State University.


Description: A library of integration-related classes

Authors: P. Nadolsky

Contents: clIntegral
*/
//=========================================================================
#ifndef INTEGRAL_H
#define INTEGRAL_H

#include "misc.h"
extern clWarn wrn1;

// Declarations =================================================================
// Below is a class clIntegral which was introduced to speed up
// the calculation of embedded integrals with the help of the
// integration routine adzint.
// The class contains the integration method adzint(), private methods
// which are called by adzint, and a private memory area used to pass
// variables between the various methods of the class.
//
// As a first step, an object of the clIntegral must be constructed
// in the beginning of the program in order to designate the memory area
// for private variables. The integration is done with the help of the
// method adzint. The inputs for adzint are described in the method itself.
//
// After the call of adzint, the result , the error estimate,
// and the error code of the integration can be retrieved from the fields
// val, errest and ier.

class clIntegral
{
private:
  static const int maxint=1000;
  double (*f)(double);
  double a,b,aerr, rerr;
  int iacta, iactb;

  double ers, res, fa, fb;
  int    numint, ib;
  bool Active; //a flag to avoid recursive calls of the same object
                                  // Work space (former common block adzwrk):
  clArray <double> u,  v, fu, fv, fw, err, result;

  double privint(void);

  void privcal (int i);

  void privspl (int i, int *p_ier);

  static void  sglint (int iact, double f1, double f2, double f3, double dx,
		       double *fint, double *ester);

  static void totalz(clIntegral *p);

public:
  double val, errest;
  int ier;

  clIntegral(): 
    u(maxint,1), v(maxint, 1), fu(maxint,1), fv(maxint,1),
    fw(maxint, 1), err(maxint, 1), result(maxint,1)
    { 
      f=NULL; a=b=aerr=rerr=val=errest=0.;
      ier=iacta=iactb=0;
      Active=false;
    }//constructor ->

  double  adzint(double (*f_in)(double), double a_in, double b_in,
		 double aerr_in, double rerr_in, int iacta_in, int iactb_in)
    {
      if (Active) 
	wrn1.exit(1,
"Exit in adzint: recursive calls of the same object of the class clIntegral \
are not allowed \n");

      Active = true;
      double sign1=1., tmp1;
      f = f_in;
      a = a_in; b = b_in; 

      if (a > b)
	{ tmp1=b; b = a; a = tmp1; sign1 = -1;}

      aerr = aerr_in; rerr = rerr_in;
      iacta = iacta_in; iactb = iactb_in;
      //
      val = privint();

      Active = false;
      return val*sign1;
    } //adzint->

};//class clIntegral ->

//==========================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//============================================================== Definitions

#ifdef MAIN_MODULE
//================================================================  clIntegral

double clIntegral::privint(void)
{
//                                  Authors: Wu-Ki Tung and John C. Collins
//        PN. Used the Fortran version dated 97/12/21  21:19:04 as an input
//     Adaptive integration routine which allows the integrand to be
//     indeterminant at the lower and/or the upper ends of integration.

//     Can self-adjust to any integrable singularity at the ends and compute
//     the closest approximant, hence achieve the required accuracy efficiently
//     (provided the switch(s) iacta (iactb) are set to 2).

//     Input switches for end-treatment:
//        iacta = 0 :   Use closed lower-end algorithm
//                1 :   Open lower-end -- use open quadratic approximant
//                2 :   Open lower-end -- use adaptive singular approximant

//        iactb = 0, 1, 2   (same as above, for the upper end)

//                Integral of f(x) from a to b, with error
//                less than fabs(aerr) + fabs(rerr*integral)
//                Best estimate of error returned in *p_errest.
//  The function returns the following error code ier:
//                0 :  o.k.
//                1 :  maximum calls to function reached before the
//                     error criteria are met;
//                2 :  iacta out of range, set to 1;
//                3 :  iactb out of range, set to 1.
//                4 :  Flag the situation b<=a (which is not an error anymore)
//                5 :  Range of integration dx zero or close to roundoff
//                     returns dx * f(a+dx/2)
//PN A modification is made to handle correctly the case b <=a

  double smll =1e-20, sml =1e-12;
  double tmp1, target;
  int numold;

  ier = 0;
  if (aerr <=smll && rerr <= smll)
    wrn1.exit(3,"Both aerr and rerr are zero in privint!");

  if (iacta < 0 || iacta > 2)
    {
      wrn1.warning(
" Illegal value of iact in privint, iacta =%i\n \
iacta set for regular open-end option.\n",iacta);
      iacta = 1;
      ier = 2;
    }

  if (iactb < 0 || iactb > 2)
    {
      wrn1.warning(
" Illegal value of iact in privint, iactb =%i\n \
iactb set for regular open-end option.\n", iactb);
      iactb = 1;
      ier = 3;
    }

  double ddx = b - a;
  if (ddx==0.)
    { ier = 4;
      return 0.0;
    }

  if (ddx <= sml)
    { ier=5;
    return (*f)(a + ddx/2) * ddx;
    }

  numint = 3;
  double dx = ddx/ (double)numint;

  for(int i = 1; i <= numint; i++)
    {
      if (i == 1)
	{
	  u[1] = a;
	  if (iacta == 0)
	    fu[1] = (*f)(a);
	  else                  //For the indeterminant end point, use the
	    //midpoint as a substitue for the endpoint.
	    fa = (*f)(a+dx/2.);
	}
      else //i != 1
	{
	  u[i] = v[i-1];
	  fu[i] = fv[i-1];
	}

      if (i == numint)
	{
	  v[numint] = b;
	  if (iactb == 0)
	    fv[numint] = (*f)(b);
	  else
	    {
	      ib = i;
	      fb = (*f)(b-dx/2.) ;
	    }
	}
      else //i != numint
	{
	  v[i] = a + dx * i;
	  fv[i] = (*f)(v[i]);
	}
      privcal(i);
    }

  totalz(this);
  //                                                   adaptive procedure:
  //below revised by Lai to ensure the accuracy requested and improve the speed
  target = fabs(aerr) + fabs(rerr * res);
  double const fac0=2.0, facMax=fac0*maxint;
  bool numltmax=true;
  while (ier == 0 && ers>target && numltmax)
    {
      numold = numint; double facnum=sqrt((double)numold*fac0);
      do{
	for(int i = 1; i <= numold; i++)
	    if (err[i]*facnum > target) privspl(i,&ier);
	if(facnum>facMax) {numltmax=false;break;}
      }while(numold==numint && (facnum*=fac0));
      target = fabs(aerr) + fabs(rerr * res);
    }

  errest = ers;
  return res;

}//clIntegral::privint ->

//--------------------------------------------------------------------------
void clIntegral::privcal(int i)
// Fill in details of interval i for given endpoints
{
  double tem, dx, w, er;

      dx =  v[i] - u[i];
      w  = (u[i] + v[i]) / 2.;

      if (i == 1 && iacta > 0)                              //  open left end
        {
          fw[i] = fa;
          fa = (*f)(u[i] + dx / 4.);
          sglint (iacta, fa, fw[i], fv[i], dx, &tem, &er);
        }
      else if (i == ib && iactb > 0)                       //  open right end
        {
          fw[i] = fb;
          fb = (*f) (v[i] - dx / 4.);
          sglint (iactb, fb, fw[i], fu[i], dx, &tem, &er);
         }
      else                                                     // closed ends
         {
           fw[i] = (*f)(w);
           tem = dx * (fu[i] + 4. * fw[i] + fv[i]) / 6.;
                                   // preliminary error Simpson - trapezoidal:
            er  = dx * (fu[i] - 2. * fw[i] + fv[i]) / 12.;
         }

      result[i] = tem;
      err   [i] = fabs (er);

}//clIntegral::privcal ->

//--------------------------------------------------------------------------

void clIntegral::privspl (int i, int *p_ier)
// Split interval i and update result & err
{
  double tiny=1e-20, oldres, olderr, delres, goderr, sumerr,fac;

  if (numint >= maxint)
    {
      *p_ier=1;
      return;
    }
//                                                        new interval numint
  numint++;
  if (i == ib) ib = numint;
  u[numint]= (u[i] + v[i]) / 2.;
  v[numint] = v[i];

  fu[numint] = fw[i];
  fv[numint] = fv[i];
//                                                             new interval i
  v[i] =  u[numint];
  fv[i] = fu[numint];
//                                                   save old result and error
  oldres = result[i];
  olderr = err[i];

  privcal(i);
  privcal(numint);
//                                                              update result
  delres = result[i] + result[numint] - oldres;
  res += delres;
//                               good error estimate based on Simpson formula
  goderr = fabs(delres);
//                                                          update new global
  ers += goderr - olderr;
//                               improve local error estimates proportionally
  sumerr = err[i] + err[numint];
  if (sumerr > tiny)
    fac = goderr / sumerr;
  else
    fac = 1.;

  err[i] *= fac;
  err[numint] *= fac;

}//clIntegral::privspl->


//--------------------------------------------------------------------------
void  clIntegral::sglint (int iact, double f1, double f2, double f3,
                          double dx, double *fint, double *ester)
//   Calculate end-interval using open-end algorithm based on function values
//   at three points at (1/4, 1/2, 1)DX from the indeterminant endpoint (0).
{
  double tem, tmp, er;
  double huge =1.e20 ;
//                                                      Use quadratic formula
  tem = dx * (4.*f1 + 3.*f2 + 2.*f3) / 9.;
//               Error est based on diff between quadratic and linear integrals
  er  = dx * (4.*f1 - 6.*f2 + 2.*f3) / 9.;

//                 Invoke adaptive singular parametrization if iact = 2
//                 algorithm is based on the formula f(x) = aa + bb * x **cc
//             where aa, bb & cc are determined from f(dx/4), f(dx/2) & f(dx)

  if (iact == 2)
    {
      double  t1 = f2 - f1;
      double  t2 = f3 - f2;
      if (t1*t2 <= 0.) goto l_end;
      double t3  = t2 - t1;
      double t12 =t1*t1;
      if ( fabs(t3)*huge < t12 ) goto l_end;
      double cc  = log (t2/t1) / log(2.);
      if (cc <= -1.)  goto l_end;
      double  bb  = t12 / t3;
      double  aa  = (f1*f3 - f2*f2) / t3;
//                                        estimated integral based on a+bx**c
      double tmp = dx * (aa + bb* pow(4.,cc) / (cc + 1.));
//                                      error estimate based on the difference
      er = tem - tmp;
//                                             use the improved integral value
      tem= tmp;
      } //if (iact==2)

 l_end:
  *fint = tem;
  *ester= er;
}//clIntegral::sglint->
//--------------------------------------------------------------------------

inline void clIntegral::totalz(clIntegral *p)
{
  p->res = p->ers = 0.;

  for (int i=1; i <= p->numint; i++)
    {
      p->res += p->result[i];
      p->ers += p->err[i];
    }
}//clIntegral::totalz->

#endif //MAIN_MODULE
#endif//INTEGRAL_H
