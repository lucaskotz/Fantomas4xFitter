#ifndef FANTOMAS_H
#define FANTOMAS_H

void readfantosteer();
void writefantosteer();
void updatefantopars(int &flavor,double *pars);
double fantopara(int &flavor, double &x);
double fantoMellinMoment(int &flavor, int &MellinPower, int npts=10000);

#endif
