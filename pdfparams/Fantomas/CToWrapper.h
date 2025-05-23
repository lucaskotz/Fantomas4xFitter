/*
Description: functions for the standalone implementation
   of the Fantomas parametrizations
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <map>
#include <string>
#include <cstring>
#include "metamorphCollection.h"


#ifndef FANTOMAS_H
#define FANTOMAS_H

extern "C"{
  void readfantosteer_();
  void writefantoout_();
  void updatefantopars_(int &flavor,double *parsin);
  double fantopara_(int &flavor, double &x);
  double fantomellinmoment_(int &flavor, int &MellinPower, int npts=10000);
  //void getfantochi2(double& fantochi2);
}
#endif
