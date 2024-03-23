        subroutine sub_orbit(iyear,idoy,sec,a,x,y,z,Ek)
        implicit double precision (a-h,o-z)
        dimension a(38)

c  -------------------------------------------------------------
c       This subroutine calculates the coordinates (WGS84) of a 
c       GPS satellite for a given epoch (iyear,idoy,sec 
c       --GPS-time--), from the navigation message parameters.
c 
c       INPUT:
c       -----
c        - epoch for which the coordinates must be calculated.
c            iyear: year
c            idoy:  day of year
c            sec:   seconds in the day
c        - Navigation message (broadcast data)
c          (according to RINEX format)
c                                                                 
c            [sat, year,mon,day,h,m,sec, a0,a1,a2     ]                            
c            [                    IODE,Crs,dn,xMo,    ]
c            [                    Cuc, e, Cus,a12,    ]
c            [                    toe,Cic,Omgg,Cis,   ]
c            [                    xIo,Crc,omgp,Omgd   ]
c            [                    xIDOT,xx,GPS_Week,xx] 
c            [                    SVac,SVh,TGD,IODC   ]               
c            [                    xx, xx , xx ,xx     ]
c
c      OUTPUT:
c      ------
c             Satellite coordinates of the satellite in the reference 
c             system tied to the Earth WGS-84
c             (x,y,z): in metres
c             Ek: eccentric anomaly (rad)
c
c      @gAGE (Research group of Astronomy and GEomatics). UPC
c  -------------------------------------------------------------                     



c       Parameters declaration .....
c       Light speed (m/s)
        c=299792458.d0
c       WGS-84 Earth Univ. Grav. parameter (m3/s2)
        xmu=3.986005d+14
c       WGS-84 Earth rotation rate (rad/s)  
        om_e=7.2921151467d-5
        pi=3.1415926535898d0
c       ............................
c       GPS Navigation message parameters:
        xIODE=a(11)
        Crs=a(12)
        dn=a(13)
        xMo=a(14)
        Cuc=a(15)
        e=a(16)
        Cus=a(17)
        a12=a(18)
        toe=a(19)
        Cic=a(20)
        Omgg=a(21)
        Cis=a(22)
        xIo=a(23)
        Crc=a(24)
        omgp=a(25)
        Omgd=a(26)
        xId=a(27)
        iGPSweek=int(a(29))
c       ........................................                                
c       Computing the GPS_week (nw) and second (sW) in the week
        xy=dble(iyear)       
c       In RINEX format year is given with only two digits
        if (xy.lt.100.d0) then
          if (xy.lt.80.d0) then
            xy=xy+2000.d0
           else
            xy=xy+1900.d0
          endif     
        endif                   

c       GPS day: (1980jan6.0 => JD=2444244.5 => id_GPS=1.0)
        id_GPS=int(365.25d0*(xy-1.d0))+idoy-722835
c       Day of week:
        idw=mod(id_GPS,7)
c       Number of GPS week:
        nw=(id_GPS-idw)/7
c       seconds in the week:
        sw=dble(idw)*86400.d0+sec
 
c       Control of GPS WEEK
        if (nw.ne.iGPSweek) print *,"ERROR: week",iGPSweek,nw

c       Time from current ephemeris epoch
        tk=sw-toe
        if(tk.gt.302400.d0)  tk=tk-604800.d0
        if(tk.lt.-302400.d0) tk=tk+604800.d0      
c       Control of age of this orbits
        if (tk.gt.7200.d0) print *,"WARNING tk=", tk," > 7200sec" 

c       True anomaly fk:
        xMk=xMo+(dsqrt(xmu)/(a12**3)+dn)*tk
        call sub_nsteffensen(xMk,e,Ek)
        fk=datan2(dsqrt(1.d0-e**2)*dsin(Ek),dcos(Ek)-e)
       
c       Arg. of Latitude uk,radius rk, inclination ik:
        uk=omgp+fk+Cuc*dcos(2.d0*(omgp+fk))+
     *       Cus*dsin(2.d0*(omgp+fk))
        rk=(a12**2)*(1.d0-e*dcos(Ek))+Crc*dcos(2.d0*(omgp+fk))+
     *     Crs*dsin(2.d0*(omgp+fk))
        xIk=xIo+xId*tk+Cic*dcos(2.d0*(omgp+fk))+
     *      Cis*dsin(2.d0*(omgp+fk))                      

c       Positions in orbital plane 
        xp=rk*dcos(uk)
        yp=rk*dsin(uk)                            

c       Longitude of ascending node xlmk:
        xlmk=Omgg+(Omgd-om_e)*tk-om_e*toe



c       CT-System coordinates
        x=xp*dcos(xlmk)-yp*dcos(xIk)*dsin(xlmk)
        y=xp*dsin(xlmk)+yp*dcos(xIk)*dcos(xlmk)
        z=yp*dsin(xIk)

        return
        end


c       -----------------------------------------------------------

       subroutine sub_nsteffensen(xm,e,ex)
       implicit double precision (a-h,o-z)

c      Method for accelerating the convergence of the Method
c      of Newton-Rapson.
c      Equations of this kind p=g(p)   (==> E=M+e*sin(E))
c      The method requires that g'(p)<>1  (==> p single root)

        tol=1.d-15

        xm=datan2(dsin(xm),dcos(xm))
        p=xm

10      continue
        p0=p
        p1=xm+e*dsin(p0)
        p2=xm+e*dsin(p1)
        dd=dabs(p2-2.d0*p1+p0) 
        if(dd.lt.tol) goto 100    
        p=p0-(p1-p0)**2/(p2-2.d0*p1+p0)
        if(dabs(p-p0).gt.tol) goto 10

100     continue
        ex=p

       return
       end

c       -----------------------------------------------------------


c      f77 -c sub_orbit.f
