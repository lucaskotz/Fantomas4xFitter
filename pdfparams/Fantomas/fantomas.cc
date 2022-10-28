// ==============================================
//
//      File Name: fantomas.cc
//
//      Description: Calculates PDFs using 
//                   metamorph.h to be called
//                   by xfitter
//
//      Date created: 01/28/2022
// ==============================================
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <map>
#include <string>
#include <cstring>
#include "MetamorphCollection.h"
#include "fantomas.h"

// Declaration of global variables inside fantomas.cc
MetamorphCollection *metacol;   
bool xFitterFantomas = false;

void readfantosteer()
// function that reads fantomas input steering card
// readfantosteer() will be called by xFitter in Fantomas_PdfParam::atStart().
// before PDFs are calculated.
{
  metacol=new MetamorphCollection();

  metacol->ReadCard();

  xFitterFantomas = true;
}

void writefantosteer()
// function that writes fantomas output steering card.
// writefantosteer_() will be called by xFitter in maind.f
// after PDFs are calculated to return updated fantomas
// parameters.
{
  if (xFitterFantomas == true)
    metacol->WriteCard();
}

void updatefantopars(int &flavor, double *pars)
// the array a[] will be passed from xFitter into the MetamorphCollection metacol->
// a[] will be the difference between the initial value and the new updated value
// for all Sc and Sm parameters. The called function will update all metamorph
// objects inside of metacol-> updatefantopars() will be called each time
// xFitter updates the minuit input values inside of Fantomas_PdfParam::atStart()
{
  metacol->UpdateParameters(flavor,pars);
}

double fantopara(int &flavor, double &x)
// function to be called that returns PDF value at a specified x-value for a given flavor.
// fantomaspara() will be called inside of Fantomas_PdfParam::operator()(double x) when 
// xFitter calculates the PDF for each flavor.
{
  double ftmp;
  ftmp = metacol->f(flavor,x);
  //std::cout << "f(" << x << ") inside fantomas.cc: " << ftmp << std::endl;
  return ftmp;
}

double fantoMellinMoment(int &flavor, int &MellinPower, int npts)
{
  double fantomoment;
  double momenttmp = metacol->MellinMoment(flavor,MellinPower,npts);
  return momenttmp;
}
