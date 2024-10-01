#ifndef FANTOMAS_H
#define FANTOMAS_H

void readfantosteer();
void writefantosteer();
void updatefantopars(int &flavor,double *parsin);
double fantopara(int &flavor, double &x);
double fantoMellinMoment(int &flavor, int &MellinPower, int npts=10000);
void writefantoc();
void fantoConditionNum(int &flavor);
void getfantochi2(double& fantochi2);
void Writechi2log(double& chi2in);
#endif
