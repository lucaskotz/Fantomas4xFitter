*
* $Id: dfeqn.F,v 1.1.1.1 1996/02/15 17:49:03 mclareni Exp $
*
* $Log: dfeqn.F,v $
* Revision 1.1.1.1  1996/02/15 17:49:03  mclareni
* Kernlib
*
* Adopted from CERNLIB by V. Kolesnikov and A. Sapronov (24.07.2014)
*
          SUBROUTINE          DFEQN(N,A,IDIM,IR,K,B)
          INTEGER             IR(*)
          DOUBLE PRECISION    A(IDIM,*),B(IDIM,*),X,Y,TE
          DOUBLE PRECISION    S21, S22, DOTF
          CHARACTER*6         HNAME
          DOTF(X,Y,S21)  =  X*Y + S21
          DATA      HNAME               /  ' DFEQN'  /
#include "feqn.inc"
          RETURN
          END
