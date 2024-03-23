C23456789012345678901234567890123456789012345678901234567890123456789012

      program iono
      implicit double precision (a-h,o-z)        

c ----------------------------------------------------------------------------
c a) Create a file "data_iono" with the following data ("see klob.f")
c    arranged in one single line (fields must be separated with a blank
c    space!!):
c
c    ................. iono.dat .....................
c     300 4789032.6277    176595.0498   4195013.2503 
c         6364789.0249 -14298268.4928  21851197.9406   
c     1.0245E-08  2.2352E-08 -5.9605E-08 -1.1921E-07
c     9.6256E+04  1.3107E+05 -6.5536E+04 -5.8982E+05            
c    ................................................        
c
c b) Execute:
c
c       cat iono.dat | iono      
c ----------------------------------------------------------------------------


      read(*,*,end=10) t,x_sta,y_sta,z_sta,x_sat,y_sat,z_sat,
     *                 alpha0,alpha1,alpha2,alpha3,
     *                 beta0,beta1,beta2,beta3,Tiono


10    continue

      call sub_klob(t,x_sta,y_sta,z_sta,x_sat,y_sat,z_sat,
     *            alpha0,alpha1,alpha2,alpha3,
     *            beta0,beta1,beta2,beta3,Tiono)

      print *, t,Tiono

      end

c     ------ compilation ------------------
c      f77 -c sub_klob.f
c      f77 -o iono iono.f sub_klob.o     
c     -------------------------------------                                      
