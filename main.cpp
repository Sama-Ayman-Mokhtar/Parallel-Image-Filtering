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

    vector<vector<int>> img_sharpen;
    for(int j = 0; j < i.height; j++){
        vector<int> vec;
        img_sharpen.push_back(vec);
    }

    vector<vector<int>> img_grey;
    for(int j = 0; j < i.height; j++){
        vector<int> vec;
        img_grey.push_back(vec);
    }


    cout << "processing" <<endl;
    cout << "   blue filter" <<endl;
    i.blueFilter(img_blue);
    cout << "   blur filter" <<endl;
    i.blurFilter(img_blur,13);
    cout << "   shapen filter" << endl;
    i.sharpenFilter(img_sharpen);
    cout << "   grey filter" << endl;
    i.greyFilter(img_grey);

    cout << "writing" << endl;
    cout << "   blue filter" <<endl;
    i.writeImage("blueFilter.ppm",img_blue);
    cout << "   blur filter" <<endl;
     i.writeImage("blurFilter.ppm",img_blur);
    cout << "   sharpen filter" <<endl;
    i.writeImage("sharpenFilter.ppm",img_sharpen);
     cout << "   grey filter" <<endl;
    i.writeImage("greyFilter.ppm",img_grey);

    return 0;
}