C23456789012345678901234567890123456789012345678901234567890123456789012

      program nwsw2cal
      implicit double precision (a-h,o-z)        

c     ------------------------------------------------------------------
c     This program computes:
c         the DOY, GPS_WEEK SEC_WEEK from YEAR MONTH DAY sec_of_day
c
c      nw, sw  -->|sub_nwsw2cal|--> iyear,imonth, iday, ihh, imm, sec
c                             idoy, secd, nweek, sweek, xjd, xmjd
c
c
c
c      @gAGE (Research group of Astronomy and GEomatics). UPC
c    -------------------------------------------------------------------


      read(*,*) nw,sw

       call sub_nwsw2cal(nw,sw,iyear,imonth,iday,ihh,imm,xss,
     *        idoy,secd,nweek,sweek,xjd,xmjd)

        write(*,'(i4,4(1x,i2),1x,f18.8,2(1x,i4,1x,f15.7),1x,
     *      f15.7,1x,f15.7)') iyear,imonth,iday,ihh,imm,xss,
     *                        idoy,secd,nweek,sweek,xjd,xmjd

      end



c -----------------------------------------------------------------------
         subroutine sub_nwsw2cal(nw,sw,iyear,imonth,iday,ihh,imm,xss,
     *        idoy,secd,nweek,sweek,xjd,xmjd)
         implicit double precision (a-h,o-z)

c        --------------------------------------------------------
c        Compute the DOY, GPS_WEEK SEC_WEEK from YEAR MONTH DAY sec_of_day
c
c         nw, sw -->|nwws2cal|--> iyear,imonth, iday, ihh, imm, sec
c                                     idoy, secd, nweek, sweek, xjd, xmjd
c
c
c
c        1) Until February 28th of 2100 it calculates consistent days.
c           Outside this range there will be a discrepancy which
c           increases by one day for every non-leap century year.
c        2) If the year is given with only two digits, the range is
c           between 1980 and 2079.
c
c
c        @gAGE (Research group of Astronomy and GEomatics). UPC
c        --------------------------------------------------------


c        ..... seconds of day ......................................
         secd=dmod(sw,86400.d0)
c        ...........................................................

c        ..... GPS day: (1980jan6.0 => JD=2444244.5 => id_GPS=1.0)...

         xjd=dble(nw)*7.d0+sw/86400.d0+2444244.5d0
         xmjd=xjd-2400000.5d0
c        ............................................................

c        ---------- Julian Day to GPS WEEK (nweek, secw) ----------
c        GPS day: (1980jan6.0 => JD=2444244.5 => id_GPS=1.0 )
         d_GPS=xjd-2444244.5d0
         id_GPS=int(d_GPS)
c        Day of week:
         idw=mod(id_GPS,7)
c        Number of GPS week:
         nweek=(id_GPS-idw)/7
c        seconds into the week:
         sweek=dble(idw)*86400.d0+secd
c        ----------------------------------------------------------

c        ----------- Julian Day to Cal (YYY, MM, DD, hh, mm, sec)---

         a=xjd+0.5d0
         ia=int(a)
         ib=ia+1537
         c=(dble(ib)-122.1d0)/365.25d0
         ic=int(c)
         c=dble(ic)
         d=365.25d0*c
         id=int(d)
         e=dble(ib-id)/30.6001d0
         ie=int(e)
         xe=30.6001d0*dble(ie)
         iday=ib-id-int(xe)
         ye=dble(ie)/14.d0
         imonth=ie-1-12*int(ye)
         ym=dble(7+imonth)/10.d0
         iyear=ic-4715-int(ym)

c        hh, mm, sec ...................
         hh=secd/3600.d0
         ihh=int(hh+1.d-10)
         xmm=(hh-dble(ihh))*60.d0
         imm=int(xmm+1.d-10)
         xss=(xmm-dble(imm))*60.d0

c       ------------ Cal 2 Doy -------------------------------------
        xy=dble(iyear)
        if (imonth.le.2) then
           xy=xy-1.d0
        endif

        idoy=int(xmjd)-int(365.25d0*(xy-1.d0))+678591
c       print *, idoy
c       -----------------------------------------------------------

c        write(*,'(i4,4(1x,i2),1x,f18.8,2(1x,i4,1x,f15.7),1x,
c     *      f15.7,1x,f15.7)') iyear,imonth,iday,ihh,imm,xss,
c     *                        idoy,secd,nweek,sweek,xjd,xmjd


         return
         end

c  ----------------------------------------------------------------------

c      f77 -o nwsw2cal nwsw2cal.f
