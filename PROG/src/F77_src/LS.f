c234567890

        program LS

        implicit double precision (a-h,o-z)
        parameter (nmc=100)
        dimension a(nmc),ay(nmc),aa((nmc**2+nmc)/2),x(nmc)

c -----------------------------------------------------------
c       Given the system  Y=AX with covariances (data noise)
c                         P=diag(sig(Y1)**2,...,sig(Yk)**2)
c       it calculates the minimum variance solutioni for each
c                         measurement epoch:
c                         X^=inv[A'*inv(P)*A]*[A'*inv(P)*Y]
c
c       Note: in this version we take: sig(Yk):1.d0
c ............................................................
c
c
c       The data file must have the following format
c
c
c       time y(1) a(1,1).....a(1,n) 
c         :          :     :      :
c         :          :     :      :
c       time y(k) a(k,1).....a(k,n) 
c         :          :     :      :
c                                   <----- row number can be
c                                          any one
c
c      @gAGE (Research group of Astronomy and GEomatics). UPC
c ............................................................
c
c   Execute:   cat file.dat | ./LS
c
c   Updated: 15/04/2013
c ------------------------------------------------------------



c       ****************
        n=3
        sig=1.d0
c       ****************


        tp=-1.d0
        do i=1,nmc
           ay(i)=0.d0
        enddo
        do i=1,(nmc**2+nmc)/2
           aa(i)=0.d0
        enddo


10      continue
        read(*,*,end=1000) t,y,(a(i),i=1,n)
        if ((tp.gt.0.d0).and.(t.ne.tp)) then
          tp=t
          goto 100
        endif
        tp=t
15      continue
        do 20 i=1,n
        ay(i)=ay(i)+a(i)*y/(sig**2)
        aa(i*(i+1)/2)=aa(i*(i+1)/2)+a(i)*a(i)/(sig**2)
        do 30 j=i+1,n
        aa(j*(j-1)/2+i)=aa(j*(j-1)/2+i)+a(i)*a(j)/(sig**2)
30      continue
20      continue
        goto 10


100     continue

        call invsp(aa,n,ier)
        if (ier.eq.1) print *, "Warning: sigular matrix"

        do i=1,n
          x(i)=0.d0
          do k=1,n
             if (k.lt.i) ik=k+i*(i-1)/2
             if (k.ge.i) ik=i+k*(k-1)/2
             x(i)=x(i)+aa(ik)*ay(k)
          enddo
        enddo

        write(*,'(f8.2,3(1x,f10.4))') t,(x(i),i=1,n)
        do i=1,nmc
           ay(i)=0.d0
        enddo
        do i=1,(nmc**2+nmc)/2
           aa(i)=0.d0
        enddo
        goto 15
1000    continue
        end                                                         

c --------------------------------------------------------------------------
        subroutine invsp(A,n,ier)

c -----------------------------------------------------------
c       It calculates the INVERSE of a MATRIX nxn SIMETRIC
c       AND is POSITIVE DEFINED (the matrix must be vectorized
c       -as simetric- by columns) If the matrix is not positive
c       defined, the calculation  stops and gives an error
c       output: ier=1.
c       NOTE: the matrix A is replaced by its inverse.
c
c       NOTICE that
c        the inverse of a generic matrix can be calculated by:
c        inv(A)=inv(A'*A)*A' (where A'*A is sim. and pos. def.)
c
c      @gAGE (Research group of Astronomy and GEomatics). UPC
c ------------------------------------------------------------


        IMPLICIT DOUBLE PRECISION (A-H,O-Z)
        DIMENSION a(*)


c       Descomposicion de CHOLESKY  (A=T'*T)

        call chol(A,n,ier)
c       print *, "CHOLESKY", (a(i),i=1,20)

c       Inversa de la matriz tringular de Cholesky  {inv(T)}
        do 100 l=1,n
        i=n-l+1
        a(i+i*(i-1)/2)=1.d0/a(i+i*(i-1)/2)
        do 110 ll=i+1,n
        j=n-ll+i+1
        s=0.d0
        do 120 k=i+1,j
        s=s+a(i+k*(k-1)/2)*a(k+j*(j-1)/2)
120     continue
        a(i+j*(j-1)/2)=-s*a(i+i*(i-1)/2)
110     continue
100     continue

c       Inversa de la matriz A   {inv(A)=inv(T)*inv(T)'}
        do 200 i=1,n
        do 210 j=i,n
        s=0.d0
        do 220 k=j,n
        s=s+a(i+k*(k-1)/2)*a(j+k*(k-1)/2)
220     continue   
        a(i+j*(j-1)/2)=s
210     continue
200     continue

        return
        end
c -------------------------------------------------------------------------
        subroutine chol(A,n,ier)

        IMPLICIT DOUBLE PRECISION (A-H,O-Z)
        DIMENSION a(*)

c -----------------------------------------------------------
c       It calculates the CHOLESKY decomposition of a matrix
c       A nxn simetric and positively defined: (A=T'*T)
c       --In the output, A is replaced by T-- (the matrix must
c       be vectorized --as simetric-- by columns). If the
c       matrix is not positively defined, the calculation stops
c       and an error output is produced: ier=1 (or  ier=2 if
c       its determinat is null).
c
c
c      @gAGE (Research group of Astronomy and GEomatics). UPC
c ------------------------------------------------------------

        ier=0

        do 30 i=1,n
        do 20 j=i,n
        sum=a(i+j*(j-1)/2)
        do 10 k=i-1,1,-1
        sum=sum-a(k+i*(i-1)/2)*a(k+j*(j-1)/2)
10      continue
        if (i.eq.j) then
          if(sum.le.0.d0) then
                ier=1
                if (sum.eq.0) ier=2
                goto 100
          endif
          a(i+i*(i-1)/2)=dsqrt(sum)
          else
          a(i+j*(j-1)/2)=sum/a(i+i*(i-1)/2)
        endif
20      continue
30      continue


100     return
        end
c ------------------------------------------------------------

       subroutine prod(A,m,l,B,ll,n,C)
       implicit DOUBLE PRECISION (A-H,O-Z)
       dimension A(*),B(*),C(*)

c ------------------------------------------------------------
c      It computes the product of a mxl matrix A and a llxn
c      matrix B. The result is the mxn matrix C. The matrix
c      must be general matrix, Fortran vectored (by collumns).
c
c
c      @gAGE (Research group of Astronomy and GEomatics). UPC
c ------------------------------------------------------------

       do i=1,m*n
          C(i)=0.d0
       enddo

       if (l.ne.ll) then
          print *, "ERROR: dimension matrix"
        goto 100
       endif

        do 10 i=1,m
          do 20 j=1,n
            C(i+m*(j-1))=0.d0
            do 30 k=1,l
              C(i+m*(j-1))=C(i+m*(j-1))+A(i+m*(k-1))*B(k+l*(j-1))
30          enddo
20        enddo
10      enddo

100    continue
       return
       end
c ------------------------------------------------------------


c      f77 -o LS LS.f
