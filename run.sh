#!/bin/bash
g++ main.cpp Image.cpp Image.hpp -I /usr/local/include/opencv4 -lopencv_core -lopencv_imgcodecs -fopenmp
./a.out
rm img.ppm sharpenFilter.ppm sharpenFilterOMP.ppm a.out