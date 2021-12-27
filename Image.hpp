#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <time.h>

#define THREADS_NUM 16 //powers of two {4,9,16,..}
#define ROOT_THREADS_NUM 4 

using namespace std;



class Image{
    public:
        string type;
        int height;
        int width;
        int rgb;
        //int** mat; Segmentation fault
        vector<vector<int>> mat;
        //vector<vector<double>> kernel;
        //vector<vector<int>> tempMat;
        //vector<vector<int>> resImg;

        
    public:
        Image(string old_image_name);
        void writeImage(string new_image_name);
        void blueFilter();
        void greyFilter();
        void blurFilter(int kernel_size, bool useThreads);
        void gaussianBlurFilter(int kernel_size, bool useThreads);
        void sharpenFilter(int kernel_size, bool useThreads);
        void verticalSharpenFilter(int kernel_sizem, bool useThreads);
        void horizontalSharpenFilter(int kernel_size, bool useThreads);
        ~Image(){};

    private:
        void padding(int num);
        void initTempMat();
        void clone();
        void fillGaussianKernel();
        void applyKernel(bool useThreads);
        void sequentialApplyKernel();
        static void* parallelApplyKernel(void * thread_id);

};