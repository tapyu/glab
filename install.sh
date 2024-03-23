#!/bin/bash

# install dependencies
sudo apt-get install python python-matplotlib python-tk python-mpltoolkits.basemap python-mpltoolkits.basemap-data python-numpy

# fix missing gcc flag in Makefile
awk -i inplace '{ print ($0 ~ /^CXXFLAGS \+= -O3/) ? "CXXFLAGS += -O3 -fno-stack-protector -fcommon" : $0 }' Makefile
