C23456789012345678901234567890123456789012345678901234567890123456789012

      program tropo
      implicit double precision (a-h,o-z)        

c ----------------------------------------------------------------------------
c a) Create a file "tropo.dat" with the following data arranged 
c    in one single line (fields must be separated with a blank
c    space!!):
c
c    .................. tropo.dat .....................
c     149.00 4789032.6277    176595.0498   4195013.2503 
c            6364789.0249 -14298268.4928  21851197.9406   
c    .................................................        
c
c b) Execute:
c
c       cat tropo.dat | tropo
c ----------------------------------------------------------------------------


      read(*,*,end=10) doy,x_sta,y_sta,z_sta,x_sat,y_sat,z_sat

10    continue

      call sub_trpUNB3(doy,x_sta,y_sta,z_sta,
     *                   x_sat,y_sat,z_sat,TC,sigma2_trop)


      print *, doy,TC

      end

c     ------ compilation ------------------
c      f77 -c sub_trpUNB3.f 
c      f77 -o tropo tropo.f sub_trpUNB3.o 
c     -------------------------------------                                      
