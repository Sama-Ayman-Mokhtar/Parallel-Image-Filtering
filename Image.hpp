#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <time.h>

using namespace std;

class Image{
    public:
        string type;
        int height;
        int width;
        int rgb;
        //int** mat; Segmentation fault
        vector<vector<int>> mat;
        vector<vector<int>> tempMat;
        vector<vector<int>> resImg;

    private:
        vector<vector<double>> kernel;
        
    public:
        Image(string old_image_name);
        void writeImage(string new_image_name);
        void blueFilter();
        void greyFilter();
        void blurFilter(int kernel_size);
        void gaussianBlurFilter(int kernel_size);
        void sharpenFilter(int kernel_size);
        void verticalSharpenFilter(int kernel_size);
        void horizontalSharpenFilter(int kernel_size);
        ~Image(){};

    private:
        void padding(int num);
        void initTempMat();
        void clone();
        void fillGaussianKernel();
        void applyKernel();

};