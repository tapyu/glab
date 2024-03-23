        subroutine sub_klob(t,x_sta,y_sta,z_sta,
     *                    x_sat,y_sat,z_sat,
     *                    alpha0,alpha1,alpha2,alpha3,
     *                    beta0,beta1,beta2,beta3,Tiono)       

        implicit double precision (a-h,o-z)

c ------------------------------------------------------------
c  Klobuchar model implementation for the calculation of the
c  ionospheric delay.
c
c  INPUT:
c        t   : observation epoch (seconds in the day)
c        (x_sta,y_sta,z_sta): receiver coordinates (WGS84) metres 
c        (x_sat,y_sat,z_sat): satellite coordinates (WGS84) metres 
c
c        KLobuchar coefficients (file klobuchar.dat):
c           alpha0,alpha1,alpha
c           beta0,beta1,beta2,beta3
c  OUTPUT:
c        Tiono: ionospheric delay (metres L1)
c
c
c      @gAGE (Research group of Astronomy and GEomatics). UPC    
c ------------------------------------------------------------

c   ... parameter declarations ...........
        c=299792458.d0   
        pi=3.1415926535898d0     
        g2r=pi/180.d0  

c       ................................
c       Coordinates of geomagnetic pole:
        xilatP=78.3d0*g2r
        xilonP=291.d0*g2r
c       Earth's Radious (m):
        Re=6378.d3
c       Ionospheric layer height (m):
        hi=350.d3
c   ......................................


c  ============================================================
c  Calculate the geodetic user longitude and latitude
        call sub_car2geo(x_sta,y_sta,z_sta,ulat,ulon,h)  

c  Calculate the elevation and azimuth of receiver-satellite ray
        x1=x_sat-x_sta
        y1=y_sat-y_sta
        z1=z_sat-z_sta
        rho=dsqrt(x1**2+y1**2+z1**2)         
        slat=dsin(ulat)
        slon=dsin(ulon)
        clat=dcos(ulat)
        clon=dcos(ulon)         
        G1=(-slat*clon*x1-slat*slon*y1+clat*z1)/rho
        G2=(-slon*x1+clon*y1)/rho
        G3=( clat*clon*x1+clat*slon*y1+slat*z1)/rho          
        elev=dasin(G3)
        azim=datan2(G2,G1)        
c  ============================================================

c   Calculate the Earth-centred angle fm (in radiants): ........
        fm=pi/2.d0-elev-dasin(Re/(Re+hi)*dcos(elev))

c   Compute the subionospheric latitude, xilat (in radiants): ...
        xilat=dasin(dsin(ulat)*dcos(fm)
     *       +dcos(ulat)*dsin(fm)*dcos(azim))

c   Compute the subionospheric longitude, xilon (in radiants): .. 
        xilon=ulon+fm*dsin(azim)/dcos(xilat)
 
c   Find the Geomagnetic latitude gmlat (in radiants): ...
        gmlat=dasin(dsin(xilat)*dsin(xilatP)
     *       +dcos(xilat)*dcos(xilatP)*dcos(xilon-xilonP))

c   Find the local time at the subionspheric point: tsub (in sec.)
        tsub=4.32d4*xilon/pi+t
        if (tsub .gt. 86400.d0) tsub=tsub-86400.d0
        if (tsub .lt. 0.d0) tsub=tsub+86400.d0   

c   Convert to slant time delay (compute the slant factor F):
        F=1.d0/dsqrt(1.d0-(Re/(Re+hi)*dcos(elev))**2)

c  Compute the ionospheric time delay sTEC (in metres of delay):
        gmlat=gmlat/pi

        alpha=alpha0+alpha1*gmlat+alpha2*gmlat**2+alpha3*gmlat**3
        beta= beta0+beta1*gmlat+beta2*gmlat**2+beta3*gmlat**3
        if (alpha.lt.0.d0) alpha=0.d0
        if (beta.lt.72000.d0) beta=72000.d0

        x=2.d0*pi*(tsub-50400.d0)/beta

        if (dabs(x).le.pi/2.d0) then
           y=alpha*dcos(x)
         else
           y=0.d0
        endif
 
        Tiono=F*(5.d-9+y)*c

        return
        end

c ======================================================================
c234567890

        subroutine sub_car2geo(x,y,z,xlat,xlon,h)
        implicit double precision (a-h,o-z)             

c -----------------------------------------------------------
c       Conversion from Cartesian coordinates (x,y,z) 
c       to ellipsoidal (fi,lambda,h) for WGS84
c
c       sta x y z ---> |car2geo| ---> xlat,xlon,h
c
c       
c       xlat: geodetic latitude
c       xlon: geodetic longitude
c       h: height above the ellipsoid
c
c
c      @gAGE (Research group of Astronomy and GEomatics). UPC
c -----------------------------------------------------------

c       ....values declaration........................
        tol=1.d-9
        pi=3.1415926535898d0 
c         WGS84 parameters (in metres)
          a=6378137.d0
          f=1.d0/298.257223563
          b=a*(1.d0-f)
        e2=(a**2-b**2)/a**2
c       ..............................................


        xl=datan2(y,x)
        p=dsqrt(x**2+y**2)
        fi=datan(z/p/(1.d0-e2))
        fia=fi
20      continue   
        xn=a**2/dsqrt((a*dcos(fi))**2+(b*dsin(fi))**2)
        h=p/dcos(fi)-xn
        fi=datan(z/p/(1.d0-e2*xn/(xn+h)))
        if(dabs(fi-fia).gt.tol) then
           fia=fi
           goto 20
        endif

        xlon=xl
        xlat=fi
         
        return
        end

c        xn=a**2/dsqrt((a*dcos(fi))**2+(b*dsin(fi))**2)
c        x=(xn+h)*dcos(fi)*dcos(xl)
c        y=(xn+h)*dcos(fi)*dsin(xl)
c        z=(b**2/a**2*xn+h)*dsin(fi)
c        write(*,'(a4,3(1x,f15.4))') "ORG", x,y,z

c ----------------------------------------------------------------
c       f77 -c sub_klob.f
