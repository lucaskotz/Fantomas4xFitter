#include "Chi2scanData.h"
#include "Outdir.h"

#include <fstream>
#include <iostream>

Chi2scanData::Chi2scanData(string dirname, string dirlabel)
{
  if (outdirs[dirlabel].IsMCreplica())
    {
      //loop on MC replica directories
      for (vector <string>::iterator it = outdirs[dirlabel].dirlist.begin(); it != outdirs[dirlabel].dirlist.end(); it++)
        {
          string fname = (*it) + "/chi2scan.txt";
	  ifstream f(fname.c_str());
          if (!f.good()) //Not a chi2scan MC replica set of dir
	    continue;
	  
	  getline(f,label);
	  string dummy;
	  double min2, delta2, chi2min2;
	  double a, b, c;
	  double min3, deltap3, deltam3, chi2min3;
	  double A, B, C, D;
	  double min4, deltap4, deltam4, chi2min4;
	  double a4, b4, c4, d4, e4;
	  f >> min2 >> delta2 >> chi2min2;
	  f >> dummy >> a >> b >> c;
	  f >> min3 >> deltap3 >> deltam3 >> chi2min3;
	  f >> dummy >> A >> B >> C >> D;
	  f >> min4 >> deltap4 >> deltam4 >> chi2min4;
	  f >> dummy >> a4 >> b4 >> c4 >> d4 >> e4;

	  double val, c2;
	  while (f >> val >> c2)
	    chi2[val] = c2;
	  
	  min2_mc.push_back(min2);
	  delta2_mc.push_back(delta2);
	  min3_mc.push_back(min2);
	  deltap3_mc.push_back(deltap3);
	  deltam3_mc.push_back(deltam3);
	  min4_mc.push_back(min2);
	  deltap4_mc.push_back(deltap4);
	  deltam4_mc.push_back(deltam4);
	}
    }
  else
    {
      //read central chi2 scan
      string fname = dirname + "/chi2scan.txt";
      ifstream f(fname.c_str());
      if (!f.good())
	return;
      getline(f,label);
      string dummy;
      f >> min2 >> delta2 >> chi2min2;
      f >> dummy >> a >> b >> c;
      f >> min3 >> deltap3 >> deltam3 >> chi2min3;
      f >> dummy >> A >> B >> C >> D;
      f >> min4 >> deltap4 >> deltam4 >> chi2min4;
      f >> dummy >> a4 >> b4 >> c4 >> d4 >> e4;

      double val, c2;
      while (f >> val >> c2)
	chi2[val] = c2;

      //read chi2 scan for PDF variations
      int i = 1;
      while (true)
	{
	  char chi2name[100];
	  sprintf(chi2name, "chi2scan_%d.txt", i);
	  string fname = dirname + "/" + chi2name;
	  ifstream fpdf(fname.c_str());
	  if (!fpdf.good())
	    break;

	  string lab;
	  string dummy;
	  double da, db, dc, dd, de;
	  double pmin2, pdelta2, pchi2min2;
	  getline(fpdf,lab);
	  fpdf >> pmin2 >> pdelta2 >> pchi2min2;
	  pdfmin2[i] = pmin2;
	  pdfdelta2[i] = pdelta2;
	  pdfchi2min2[i] = pchi2min2;
	  fpdf >> dummy >> da >> db >> dc;

	  double pmin3, pdeltap3, pdeltam3, pchi2min3;
	  fpdf >> pmin3 >> pdeltap3 >> pdeltam3 >> pchi2min3;
	  pdfmin3[i] = pmin3;
	  pdfdeltap3[i] = pdeltap3;
	  pdfdeltam3[i] = pdeltam3;
	  pdfchi2min3[i] = pchi2min3;
	  fpdf >> dummy >> da >> db >> dc >> dd;

	  double pmin4, pdeltap4, pdeltam4, pchi2min4;
	  fpdf >> pmin4 >> pdeltap4 >> pdeltam4 >> pchi2min4;
	  pdfmin4[i] = pmin4;
	  pdfdeltap4[i] = pdeltap4;
	  pdfdeltam4[i] = pdeltam4;
	  pdfchi2min4[i] = pchi2min4;
	  fpdf >> dummy >> da >> db >> dc >> dd >> de;
	  //scale to 68cl
	  //      pdfmin[i] = min + (pdfmin[i] - min) / 1.64;

	  double val, c2;
	  while (fpdf >> val >> c2)
	    pdfchi2[i][val] = c2;
	  i++;
	}

      //read uncertainties summary
      string fname_unc = dirname + "/unc_summary.txt";
      ifstream func(fname_unc.c_str());
      if (!func.good())
	return;
      getline(func,dummy);
      func >> dummy >> statp >> statm;
      func >> dummy >> systp >> systm;
      func >> dummy >> pdfp >> pdfm;
      func >> dummy >> dummy >> scalep >> scalem; 
      func >> dummy >> dummy >> totdecp >> totdecm;
      func >> dummy >> dummy >> dummy >> totp >> totm;
    }
}
