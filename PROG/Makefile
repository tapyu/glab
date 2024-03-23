# Compilators
F77 = f77       
CC = gcc
CXXFLAGS += -O3 

# Program Directories
CDIR = ./C
FDIR = ./Fortran

# gLAB installation directory:
ppwwdd = `pwd`


all: gLAB kalman LS GPSxyz iono

# C programs [gLAB]
gLAB: src/gLAB_src/source/core/gLAB.c src/gLAB_src/source/core/dataHandling.c src/gLAB_src/source/core/filter.c src/gLAB_src/source/core/input.c src/gLAB_src/source/core/model.c src/gLAB_src/source/core/preprocessing.c src/gLAB_src/source/core/output.c
	 ${CC} ${CXXFLAGS} -o gLAB_linux src/gLAB_src/source/core/gLAB.c src/gLAB_src/source/core/dataHandling.c src/gLAB_src/source/core/filter.c src/gLAB_src/source/core/input.c src/gLAB_src/source/core/model.c src/gLAB_src/source/core/preprocessing.c src/gLAB_src/source/core/output.c -lm


# FORTRAN programs

kalman: src/F77_src/kalman.f
	 $(F77) -o kalman src/F77_src/kalman.f

LS: src/F77_src/LS.f
	 $(F77) -o LS src/F77_src/LS.f

GPSxyz: src/F77_src/GPSxyz.f
	 $(F77) -c src/F77_src/sub_orbit.f
	 $(F77) -o GPSxyz src/F77_src/GPSxyz.f sub_orbit.o

iono: src/F77_src/iono.f
	 $(F77) -c src/F77_src/sub_klob.f src/F77_src/iono.f
	 $(F77) -o iono src/F77_src/iono.f  sub_klob.o

# INSTALL

install: 
	 cp gLAB_linux src/gLAB_src
	 cp kalman LS GPSxyz iono src/F77_src


clean: 
	 rm -f gLAB_linux *.o src/F77_src/*.o kalman LS GPSxyz iono


