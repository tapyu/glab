      program kalman
      implicit double precision (a-h,o-z)
      double precision fi_x,fi_y,fi_z,fi_t
      parameter (nmax=10)
      dimension P((nmax**2+nmax)/2),xfi(nmax),Q(nmax),
     * a(nmax),y(nmax),x(nmax)
      namelist /parameters/fi_x,fi_y,fi_z,fi_t,
     *  Pxx,Pyy,Pzz,Ptt,Qxx,Qyy,Qzz,Qtt
c ==============================================================
c    
c    cat file.dat --> |kalman| --->  time dx dy dz dt 
c                        ^
c           kalman.nml___|
c
c   -------------------------------------------------------------    
c   It applies to the linear system:  Y= A x, that is to say:
c
c
c    [  ]   [                                  ] [dx ]
c    [yi] = [(x0-xs)/ro (y0-ys)/ro (z0-zs)/ro 1] [dy ]
c    [  ]   [                                  ] [dz ]
c    [  ]   [                                  ] [cdt]      
c
c    being:
c                 [1/(sigma_y1)^2                       ]
c                 [                                     ]
c              W= [        1/(sigma_yi)^2               ]
c                 [                                     ]
c                 [                      1/(sigma_yn)^2 ]
c
c              
c    [Pxx         ]      [Qxx         ]      [fi_x            ]
c P0=[   Pyy      ]    Q=[   Qyy      ]   fi=[    fi_y        ]
c    [      Pzz   ]      [      Qzz   ]      [        fi_z    ]
c    [         Ptt]      [         Qtt]      [            fi_t]
c
c    (See filter equations in chapter 6) 
c  .............................................................
c   The values of [y(n),(x0-xs)/ro,(y0-ys)/ro,(z0-zs)/ro] 
c   are obtained from the file "file.dat":
c
c   sigma_y1 is taken as sigma_y1=1.d0
c 
c
c   Example of file: file.dat
c  -------------------------------------------------------------
c   [time    y(n)   (x0-xs)/ro (y0-ys)/ro (z0-zs)/ro 1 ]
c                            (meters)
c                    .....................
c     900  5934.730 -0.557881  0.398805 -0.727820  1.0
c     900  5939.028  0.058012  0.613973 -0.787191  1.0
c    1800  5933.606 -0.657670  0.369129 -0.656667  1.0
c                    .....................
c
c  The values of Pxx, Pyy, Pzz, Ptt, Qxx, Qyy, Qzz, Qtt,
c   fi_x, fi_y, fi_z, fi_t, are established through the namelist
c   kalman.nml:
c
c
c  ... kalman.nml ...
c  $parameters
c    Pxx=1.d+8    
c    Pyy=1.d+8    (m2)
c    Pzz=1.d+8
c    Ptt=9.d+16
c    fi_x=1.d0     ctt ==> fi=1; Q=0
c    fi_y=1.d0     wn  ==> fi=0; Q=sigma**2  
c    fi_z=1.d0     rw  ==> fi=1; Q=sigma**2 * dt
c    fi_t=0.d0            
c    Qxx=0.d0
c    Qyy=0.d0     (m2)
c    Qzz=0.d0
c    Qtt=9.d+16  
c  $end   
c  .................  
c
c      @gAGE (Research group of Astronomy and GEomatics). UPC    
c ==============================================================





c   Initialization values..................     
          nobs=0
          do i=1,nmax
           a(i)=0.d0
           x(i)=0.d0      
           y(i)=0.d0      
           xfi(i)=0.d0
           Q(i)=0.d0
          enddo
          do i=1,(nmax**2+nmax)/2
           P(i)=0.d0    
          enddo      
c   .......................................

        open (10,file="kalman.nml")          
        read (10,nml=parameters)    
        close(10)      

c   Kalman FILTER declaration matrix ...... 
c      State transition matrix.....
          xfi(1)=fi_x
          xfi(2)=fi_y        
          xfi(3)=fi_z
          xfi(4)=fi_t   
c      A priori covariance values (in meters)...
c      (sig_dx_i=1.d3m; sig_dt=1.d4m)
          P(1)=Pxx
          P(3)=Pyy
          P(6)=Pzz
          P(10)=Ptt                                
c      Process noises matrix (in meters).......
          Q(1)=Qxx
          Q(2)=Qyy 
          Q(3)=Qzz 
          Q(4)=Qtt 
c   ...........................................

        nvar=4       
        sigma_y=1.d0

c    ================================================
c    BEGIN fordware propagation (of a priories):  
c       Computing the prediction from the a priori values
c       x^_(1)=xfi*x^(0); P_(1)=xfi*P(0)*xfi'+Q
c      
c       NOTE:  
c       1) x^(0)=0 ==> x^_(1)=0.  
c     
c          Let's: x:= x^_(1)=0  (x was initialized as "0")
c                                   
c                     
c       2) The matrix "xfi" and "Q" are assumed to be 
c           diagonal, and stored as a n-dim vectors..
 
        do i=1,nvar
          P(i*(i+1)/2)= P(i*(i+1)/2)*xfi(i)+Q(i)
        enddo

c    END of fordware propagation (of a priories).
c    ================================================     


c         P:=inv[P_(n)] ............
           call invsp(P,nvar,ier)
c        ..........................                    


c    BEGIN MAIN LOOP +++++++++++++++++++++++++++++++++++++++++++

c    :::Begin data loop :::::::::::::::::::::::::::::::::::::::::::
        nf=0
10      read (*,*,end=900) tt,yy,(a(j),j=1,nvar)    
        nf=nf+1   
        if (nf.eq.1) tt0=tt
        if (tt .gt. tt0) goto 200
25      continue     


c       -------------------------------------------
c       PREPARING  matrix and vector for ESTIMATION
c       Building the vector and matrix: ....... 
c             y:=A'(n)*W*Y(n)
c             P:=inv(P_(n))+A'(n)*W*A(n) 
c             (where W <--> 1/sigma_y**2)
c       .......................................
         do j=1,nvar
          y(j)=y(j)+a(j)*yy/sigma_y**2
          do i=1,j
            P(j*(j-1)/2+i)=P(j*(j-1)/2+i)+
     *      a(i)*a(j)/sigma_y**2
          enddo
         enddo
c       -------------------------------------------

        nobs=nobs+1
        tt0=tt
        goto 10 

c   :::::::::::::::::::::::::::::::::::::::::::::End Data loop :::
200     continue       

c    ESTIMATION ==============================================
  
c       P:=  P(n)=inv[inv(P_(n))+A'(n)*W*A(n)]..........
        call invsp(P,nvar,ier0) 
c       ...............................................

c       x:= x^(n)=P(n)*[inv(P_(n))*x^_(n)+A'(n)*W*Y(n)]  
        do i=1,nvar
          x(i)=0.d0
          do k=1,nvar
             if (k.lt.i) ik=k+i*(i-1)/2
             if (k.ge.i) ik=i+k*(k-1)/2
             x(i)=x(i)+P(ik)*y(k)
          enddo
        enddo
c       ..................................                        
c    End estimation 
c    ========================================================


c    ...PRINT THE KALMAN ESTIMATION...........................
        write(*,'(f8.2,4(1x,f10.5))') tt0,(x(i),i=1,4)              
c    ========================================================
c    BEGIN fordware propagation: 

c       x:= x^_(n+1)=fi*x^(n) ...........
         do i=1,nvar
          x(i)=x(i)*xfi(i)
         enddo
c       .................................
                               
c       P:= P_(n+1)=fi*P(n)*(fi)'+Q ................
         do i=1,nvar
          P(i*(i+1)/2)= P(i*(i+1)/2)*xfi(i)+Q(i)
         enddo
c       ............................................
c    END of fordware propagation. 
c    ========================================================          

c       PREPARING  matrix and vector for ESTIMATION ---------              
c       P:=inv[P_(n+1)] ............
         call invsp(P,nvar,ier)
c       ..........................
                                                         
c       y:=inv(P_(n+1))*x^_(n+1) ...........
         do i=1,nvar
          y(i)=0.d0
          do k=1,nvar
             if (k.lt.i) ik=k+i*(i-1)/2
             if (k.ge.i) ik=i+k*(k-1)/2
             y(i)=y(i)+P(ik)*x(k)
          enddo
         enddo
c       -------------------------------------------------------

        tt0=tt
        goto 25
c  +++++++++++++++++++++++++++++++++++++++++++++++ END of Main LOOP
900     continue
        end

c -------------------------------------------------------------------
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

c       CHOLESKY decomposition  (A=T'*T)

        call chol(A,n,ier)
c       print *, "CHOLESKY", (a(i),i=1,20)

c       Inverse of the triangular matrix of Cholesky  {inv(T)}
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


c       Inverse of the matrix A   {inv(A)=inv(T)*inv(T)'}
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

c ------------------------------------------------------------

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

c       f77 -o kalman kalman.f

