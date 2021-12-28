#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <time.h>
#include <omp.h>

#define THREADS_NUM 16 //perfect squares {4,9,16,..}
#define ROOT_THREADS_NUM 4 

#define SEQUENTIAL 1
#define PTHREADS 2
#define OPEN_MP 3

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
        void blurFilter(int kernel_size, int processing_type);
        void gaussianBlurFilter(int kernel_size, int processing_type);
        void sharpenFilter(int kernel_size, int processing_type);
        void verticalSharpenFilter(int kernel_size, int processing_type);
        void horizontalSharpenFilter(int kernel_size, int processing_type);
        ~Image(){};

    private:
        void padding(int num);
        void initTempMat();
        void clone();
        void fillGaussianKernel();
        void applyKernel(int processing_type);
        void sequentialApplyKernel();
        void openMP_parallelApplyKernel();
        static void* pthreads_parallelApplyKernel(void * thread_id);

};