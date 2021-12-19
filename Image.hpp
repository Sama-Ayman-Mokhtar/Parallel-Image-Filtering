

#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class Image{
    public:
        string type;
        int height;
        int width;
        int rgb;
        //int** mat; Segmentation fault
        vector<vector<int>> mat;
        
    public:
        Image(string old_image_name);
        void writeImage(string new_image_name, vector<vector<int>> img);
        void blueFilter(vector<vector<int>> &img);
        void blurFilter(vector<vector<int>> &img,  int kernel_size);
        void sharpenFilter(vector<vector<int>> &img);
        ~Image(){};

    private:
        void padding(vector<vector<int>> &img, int num);
        void clone(vector<vector<int>> &imgDes);

};


