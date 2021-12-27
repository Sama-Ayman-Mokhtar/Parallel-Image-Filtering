#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Image.hpp"

using namespace std;

//if blur filter then use kernel size > 5
int main(){
   
   cout << "reading" << endl;
   Image i("horse.ppm");


    cout << "blue filter" <<endl;
    cout << "   processing" <<endl;
    clock_t begin = clock(); 
    i.blueFilter();
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("    total time: %f sec\n",time_spent);
    cout << "   writing" <<endl;  
    i.writeImage("blueFilter.ppm");

    cout << "blur filter" <<endl;
    cout << "   processing" <<endl;
    begin = clock();   
    i.blurFilter(13);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("    total time: %f sec\n",time_spent);
    cout << "   writing" <<endl;  
    i.writeImage("blurFilter.ppm");

    cout << "sharpen filter" << endl;
    cout << "   processing" <<endl;  
    begin = clock(); 
    i.sharpenFilter(5);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("    total time: %f sec\n",time_spent);
    cout << "   writing" <<endl;  
    i.writeImage("sharpenFilter.ppm");

    cout << "grey filter" << endl;
    cout << "   processing" <<endl;
    begin = clock();   
    i.greyFilter();
     end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("    total time: %f sec\n",time_spent);
    cout << "   writing" <<endl;  
    i.writeImage("greyFilter.ppm");

    cout << "horizontal sharpen filter" << endl;
    cout << "   processing" <<endl;
    begin = clock();   
    i.horizontalSharpenFilter(3);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("    total time: %f sec\n",time_spent);
    cout << "   writing" <<endl;  
    i.writeImage("horizontalSharpenFilter.ppm");

    cout << "vertical sharpen filter" << endl;
    cout << "   processing" <<endl; 
    begin = clock();  
    i.verticalSharpenFilter(3);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("    total time: %f sec\n",time_spent);
    cout << "   writing" <<endl;  
    i.writeImage("verticalSharpenFilter.ppm");

    cout << "gaussian blur filter" <<endl;
    cout << "   processing" <<endl;  
    begin = clock(); 
    i.gaussianBlurFilter(7);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("    total time: %f sec\n",time_spent);
    cout << "   writing" <<endl;  
    i.writeImage("gaussianBlurFilter.ppm");

    return 0;
}
/*
            SEQUENTIAL: output

    reading
    blue filter
    processing
        total time: 0.558490 sec
    writing
    blur filter
    processing
        total time: 40.291353 sec
    writing
    sharpen filter
    processing
        total time: 6.877646 sec
    writing
    grey filter
    processing
        total time: 0.701005 sec
    writing
    horizontal sharpen filter
    processing
        total time: 3.232291 sec
    writing
    vertical sharpen filter
    processing
        total time: 3.224000 sec
    writing
    gaussian blur filter
    processing
        total time: 12.482560 sec
    writing


*/