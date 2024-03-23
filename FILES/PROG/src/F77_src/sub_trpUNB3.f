      subroutine sub_trpUNB3(doy,x_sta,y_sta,z_sta,
     *                        x_sat,y_sat,z_sat,TC,sigma2_trop)


      implicit double precision (a-h,o-z)
      dimension avr(5,5),svr(5,5),xfi0(5),avr0(5),svr0(5),xi(5)


c -------------------------------------------------------------              
c  MOPS tropospheric model (appendix A.4.2.4)
c
c  INPUT:
c        doy : Day-Of-Year  (real number)
c        (x_sta,y_sta,z_sta): receiver coordinates (WGS84) metres
c        (x_sat,y_sat,z_sat): satellite coordinates (WGS84) metres
c  
c  OUTPUTS: TC,sigma2_trop      
c
c  H= height above the mean sea-level (metres)
c  xfi= receiver latitude (rad)
c  elev=satellite elevation from receiver (rad)    
c
c  TC= tropospheric correction (metres of delay)
c  sigma2_trop= residual error for tropospheric delay (metres**2)
c --------------------------------------------------------------
c
c
c       @gAGE/UPC (group of Astronomy and GEomatics)
c --------------------------------------------------------------   


c       Constants declaration ............
        pi=3.1415926535898d0
        xk1=77.604d0
        xk2=382000.d0
        Rd=287.054d0
        g=9.80665d0
        gm=9.784d0

c       .................Average....................
        data (avr(1,j),j=1,5) /
     *   1013.25d0,299.65d0,26.31d0,6.30d-3,2.77d0 /
        data (avr(2,j),j=1,5) /
     *   1017.25d0,294.15d0,21.79d0,6.05d-3,3.15d0 /
        data (avr(3,j),j=1,5) /
     *   1015.75d0,283.15d0,11.66d0,5.58d-3,2.57d0 /
        data (avr(4,j),j=1,5) /
     *   1011.75d0,272.15d0, 6.78d0,5.39d-3,1.81d0 /
        data (avr(5,j),j=1,5) /
     *   1013.00d0,263.65d0, 4.11d0,4.53d-3,1.55d0 /
c       ..........Seasonal Variation................     
        data (svr(1,j),j=1,5) /
     *    0.00d0, 0.00d0,0.00d0,0.00d-3,0.00d0 /
        data (svr(2,j),j=1,5) /
     *   -3.75d0, 7.00d0,8.85d0,0.25d-3,0.33d0 /
        data (svr(3,j),j=1,5) /
     *   -2.25d0,11.00d0,7.24d0,0.32d-3,0.46d0 /
        data (svr(4,j),j=1,5) /
     *   -1.75d0,15.00d0,5.36d0,0.81d-3,0.74d0 /
        data (svr(5,j),j=1,5) /
     *   -0.50d0,14.50d0,3.39d0,0.62d-3,0.30d0 /
c       .............Latitude bands.................                              
        data (xfi0(i),i=1,5) /15.d0,30.d0,45.d0,60.d0,75.d0/
c       ............................................

c  ============================================================

c  Calculate the geodetic user longitude and latitude
        call sub_car2geo(x_sta,y_sta,z_sta,ulat,ulon,H)

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

c  H= height above the mean sea-level (metres)
c  [Height above the ellipsoid is used instead of the mean sea-level]
c  xfi= receiver latitude (rad)
c  elev=satellite elevation from receiver (rad)


c      from radians to degrees
       xfi=ulat*180.d0/pi
       elev=elev*180.d0/pi
c      ........................


      if (xfi.ge.0.d0) then
          dmin=28.d0
         else
          dmin=211.d0
        endif
        dd=doy-dmin
        xfact=2.d0*pi*dd/365.25d0

        elevr=elev*pi/180.d0
        axfi=dabs(xfi)

        if  (axfi.le.15.d0) index=1
        if ((axfi.gt.15.d0).and.(axfi.le.30.d0)) index=2
        if ((axfi.gt.30.d0).and.(axfi.le.45.d0)) index=3
        if ((axfi.gt.45.d0).and.(axfi.le.60.d0)) index=4
        if ((axfi.gt.60.d0).and.(axfi.lt.75.d0)) index=5
        if (axfi.ge.75.d0) index=6

        do j=1,5
         if (index.eq.1) then
            avr0(j)=avr(index,j)
            svr0(j)=svr(index,j)
           else
            if (index.lt.6) then
              avr0(j)=avr(index-1,j)+(avr(index,j)-avr(index-1,j))*
     *            (axfi-xfi0(index-1))/(xfi0(index)-xfi0(index-1))
              svr0(j)=svr(index-1,j)+(svr(index,j)-svr(index-1,j))*
     *            (axfi-xfi0(index-1))/(xfi0(index)-xfi0(index-1))
             else
              avr0(j)=avr(index-1,j)
              svr0(j)=svr(index-1,j)
            endif
         endif
         xi(j)=avr0(j)-svr0(j)*dcos(xfact)
        enddo

        P=xi(1)
        T=xi(2)
        e=xi(3)
        beta=xi(4)
        xlambda=xi(5)

c       Zero-altitude zenith delay terms:

        z_hyd=1.d-6*xk1*Rd*P/gm 
        z_wet=1.d-6*xk2*Rd/(gm*(xlambda+1.d0)-beta*Rd)*e/T

c       zenith delay terms at H metres of height above mean sea-level

        exp1=g/Rd/beta
        d_hyd=z_hyd*(1.d0-beta*H/T)**exp1

        exp2=((xlambda+1.d0)*g/Rd/beta)-1.d0
        d_wet=z_wet*(1.d0-beta*H/T)**exp2

c       Tropospheric mapping function:
        xmap=dsqrt(0.002001d0+(dsin(elevr))**2)
        xmap=1.001d0/xmap

c       Tropospheric correction
        TC=(d_hyd+d_wet)*xmap

c       residual error for tropospheric delay
        sigma2_trop=(0.12d0*xmap)**2

        return
        end

c ======================================================================
c234567890

        subroutine sub_car2geo(x,y,z,xlat,xlon,h)
        implicit double precision (a-h,o-z)

c -----------------------------------------------------------
c       Conversion from Cartesian coordinates (x,y,z)
c       to Ellipsoidal (fi,lambda,h) for WGS84
c
c       sta x y z ---> |car2geo| ---> xlat,xlon,h
c
c
c       xlat: geodetic latitude
c       xlat: geodetic latitude
c       h: height above the ellipsoid
c
c
c      @gAGE (Research group of Astronomy and GEomatics). UPC
c -----------------------------------------------------------

c       ....value declaration........................
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

c       f77 -c sub_trpUNB3.f
