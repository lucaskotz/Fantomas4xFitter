#ifndef Chi2scanData_h
#define Chi2scanData_h

#include <string>
#include <map>
#include <vector>

using namespace std;

class Chi2scanData
{
 public:
  Chi2scanData() {};
  Chi2scanData(string dirname, string dirlabel);
  string label;
  double min2, delta2, chi2min2;
  double a, b, c;
  double min3, deltap3, deltam3, chi2min3;
  double A, B, C, D;
  double min4, deltap4, deltam4, chi2min4;
  double a4, b4, c4, d4, e4;

  double min, delta, deltap, deltam, chi2min;
  map <double, double> chi2;

  map <int, double> pdfmin2;
  map <int, double> pdfdelta2;
  map <int, double> pdfchi2min2;

  map <int, double> pdfmin3;
  map <int, double> pdfdeltap3;
  map <int, double> pdfdeltam3;
  map <int, double> pdfchi2min3;

  map <int, double> pdfmin4;
  map <int, double> pdfdeltap4;
  map <int, double> pdfdeltam4;
  map <int, double> pdfchi2min4;

  map <int, double> pdfmin;
  map <int, map <double, double> > pdfchi2;

  //uncertainty decomposition
  double statp, statm, systp, systm, pdfp, pdfm, scalep, scalem, totdecp, totdecm, totp, totm;

  //MC replicas
  vector <double> min2_mc;
  vector <double> delta2_mc;
  vector <double> min3_mc;
  vector <double> deltap3_mc;
  vector <double> deltam3_mc;
  vector <double> min4_mc;
  vector <double> deltap4_mc;
  vector <double> deltam4_mc;
};
#endif
