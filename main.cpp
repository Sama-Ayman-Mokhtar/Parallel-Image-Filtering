#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Image.hpp"

using namespace std;


int main(){
   
   cout << "reading" << endl;
   Image i("horse.ppm");

  /*  vector<vector<int>> img_blue;
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

    vector<vector<int>> img_horizontalSharpen;
    for(int j = 0; j < i.height; j++){
        vector<int> vec;
        img_horizontalSharpen.push_back(vec);
    }

    vector<vector<int>> img_verticalSharpen;
    for(int j = 0; j < i.height; j++){
        vector<int> vec;
        img_verticalSharpen.push_back(vec);
    }*/
    vector<vector<int>> img_gaussianBlur;
    for(int j = 0; j < i.height; j++){
        vector<int> vec;
        img_gaussianBlur.push_back(vec);
    }
   


   /* cout << "processing" <<endl;
    cout << "   blue filter" <<endl;
    i.blueFilter(img_blue);
    cout << "   blur filter" <<endl;
    i.blurFilter(img_blur,13);
    cout << "   shapen filter" << endl;
    i.sharpenFilter(img_sharpen, 5);
    cout << "   grey filter" << endl;
    i.greyFilter(img_grey);
    cout << "   horizontal sharpen filter" << endl;
    i.horizontalSharpenFilter(img_horizontalSharpen, 3);
     cout << "   vertical sharpen filter" << endl;
    i.verticalSharpenFilter(img_verticalSharpen, 3);*/
    cout << "   guassian blur filter" <<endl;
    i.blurFilter(img_gaussianBlur,13);
    

    /*cout << "writing" << endl;
    cout << "   blue filter" <<endl;
    i.writeImage("blueFilter.ppm",img_blue);
    cout << "   blur filter" <<endl;
     i.writeImage("blurFilter.ppm",img_blur);
    cout << "   sharpen filter" <<endl;
    i.writeImage("sharpenFilter.ppm",img_sharpen);
    cout << "   grey filter" <<endl;
    i.writeImage("greyFilter.ppm",img_grey);
    cout << "   horizontal sharpen filter" <<endl;
    i.writeImage("horizontalSharpenFilter.ppm",img_horizontalSharpen);
      cout << "   vertical sharpen filter" <<endl;
    i.writeImage("verticalSharpenFilter.ppm",img_verticalSharpen);*/
    cout << "   guassian blur filter" <<endl;
    i.writeImage("guassianBlurFilter.ppm",img_gaussianBlur);

    return 0;
}