// Program to test the MetamorphCollection functions as a standalone.

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

int main()
{
  double test[3] = {0}; // create an empty array that will be treated as the minuit input parameter for the three metamorphs.
  readfantosteer();     // read the test fantomas card file inside the directory.
  int gfl = 0;          // define the ID for each flavor.
  int sfl = 4;
  int vfl = 10;
  updatefantopars(gfl,test);  // execute the "UpdateModulator" function inside metamorph so it calculates the matrices needed to create the full metamorph.
  updatefantopars(sfl,test);
  updatefantopars(vfl,test);

  std::cout << "Finished updating MetamorphCollections for first time.\nNow Printing out metamorph values.\n";

  double a = 0.1;

  std::cout << "gluon at x = " << a << ": " << fantopara(gfl,a) << "\n";  // Print out the metamorph value at the test point "a".
  std::cout << "sea at x = " << a << ": " << fantopara(sfl,a) << "\n";
  std::cout << "valence at x = " << a << ": " << fantopara(vfl,a) << "\n";

  return 0;
}
