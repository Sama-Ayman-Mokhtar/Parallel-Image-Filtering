#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Image.hpp"

using namespace std;


int main(){
   
   cout << "reading" << endl;
   Image i("horse.ppm");

    vector<vector<int>> img_blue;
    for(int j = 0; j < i.height; j++){
        vector<int> vec;
        img_blue.push_back(vec);
    }

    vector<vector<int>> img_blur;
    for(int j = 0; j < i.height; j++){
        vector<int> vec;
        img_blur.push_back(vec);
    }

    cout << "processing" <<endl;
    cout << "   blue filter" <<endl;
    i.blueFilter(img_blue);
    cout << "   blur filter" <<endl;
    i.blurFilter(img_blur,21);

    cout << "writing" << endl;
    cout << "   blue filter" <<endl;
    i.writeImage("blueFilter.ppm",img_blue);
    cout << "   blur filter" <<endl;
    i.writeImage("blurFilter.ppm",img_blur);

    return 0;
}