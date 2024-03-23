c234567
        program GPSxyz
        implicit double precision (a-h,o-z)
        dimension a(38)

c -----------------------------------------------------------------------------
c This program computes the satellite coordinates at a given time 
c [YEAR, DoY, sec_of_day] from the GPS broadcast message "eph.dat"
c
c  
c -----------------------------------------------------------------------------
c
c Execution example:
c
c  1.- Data file containing the epoch to compute the coordinates
c
c .................. time.dat [YEAR, DoY, sec_of_day] .........................
c                         2005 149 300 
c .............................................................................
c
c 
c  2.- Data file containing the Broadcast ephemeris block (form RINEX file)
c      IMPORTANT: All data in a single line, with fields separated by spaces.
c ............................. eph.dat .......................................
c 25 5  5 29  2  0  0.0 9.401096031070E-05 9.094947017729E-13 0.000000000000E+00
c 8.400000000000E+01 -1.061875000000E+02  4.825915304457E-09 -2.255215633503E+00
c-5.284324288368E-06  1.204112719279E-02  5.686655640602E-06  5.153704689026E+03
c 7.200000000000E+03  2.011656761169E-07 -2.689273653419E+00  1.396983861923E-07
c 9.492799505545E-01  2.625625000000E+02 -1.460408709553E+00 -8.100337411567E-09
c-3.643008888800E-11  1.000000000000E+00  1.325000000000E+03  0.000000000000E+00
c 2.800000000000E+00  0.000000000000E+00 -7.450580596924E-09  8.520000000000E+02
c 1.800000000000E+01  0.000000000000E+00  1.000000000000E+00  0.000000000000E+00
c .............................................................................
c
c b) Run:
c
c       cat time.dat eph.dat | GPSxyz
c
c ------------------------------------------------------------------------------
c ==============================================================================


      read(*,*,end=10) iyear,idoy,sec,a
10    continue
      
      call sub_orbit(iyear,idoy,sec,a,x,y,z,Ek)
     
      write(*,'(f4.0,1x,f18.8,1x,f17.6,1x,f17.6,f17.6,1x,f12.6)'),
     *  a(1),sec,x,y,z,Ek

      end

c ------------------------------------------------------------------------------

c Note: compilation:

c  f77 -c  sub_orbit.f
c  f77 -o  GPSxyz GPSxyz.f  sub_orbit.o

