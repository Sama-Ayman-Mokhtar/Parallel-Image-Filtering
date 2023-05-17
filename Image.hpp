#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <time.h>
#include <omp.h>
#include <cstdio>

#define SEQUENTIAL 1
#define OPEN_MP 2

using namespace std;

class Image{
    public:
        string type;
        int rgb;
        vector<vector<int>> mat; 
    public:
        Image(string old_image_name, int kernel_size);
        void writeImage(string new_image_name);
        void sharpenFilter(int kernel_size, int processing_type, int num_of_processors);
        ~Image(){};

    private:
        void applyKernel(int processing_type, int kernel_size, int num_of_processors);
        void sequentialApplyKernel(int kernel_size);
        void openMP_parallelApplyKernel(int kernel_size, int num_of_processors);
};