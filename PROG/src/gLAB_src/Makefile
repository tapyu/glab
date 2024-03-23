CC = gcc
CXXFLAGS += -O3 
#CXXFLAGS += -pedantic
#CXXFLAGS += -Wall
#CXXFLAGS += -std=gnu99
#CXXFLAGS += -Wno-unknown-pragmas
#CXXFLAGS += -fopenmp


all: gLAB

gLAB: source/core/gLAB.c source/core/dataHandling.c source/core/filter.c source/core/input.c source/core/model.c source/core/preprocessing.c source/core/output.c
	 ${CC} ${CXXFLAGS} -o gLAB_linux source/core/gLAB.c source/core/dataHandling.c source/core/filter.c source/core/input.c source/core/model.c source/core/preprocessing.c source/core/output.c -lm

