#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Image.hpp"
#include <pthread.h>

using namespace std;

//if blur filter then use kernel size > 5
int main(){
   
   cout << "reading" << endl;
   Image i("horse.ppm");

    time_t begin, end;
    double time_spent;
    
    cout << "blue filter" <<endl;
    cout << "   sequential processing" <<endl;
    time(&begin); 
    i.blueFilter();
    time(&end);
    time_spent = difftime(end, begin);
    printf("    total time: %f sec\n",time_spent);
    cout << "   writing" <<endl;  
    i.writeImage("blueFilter.ppm");

    cout << "blur filter" <<endl;
    cout << "   sequential processing" <<endl;    time(&begin); 
    i.blurFilter(13, false);
    time(&end);
    time_spent = difftime(end, begin);
    printf("    total time: %f sec\n",time_spent);
    cout << "   writing" <<endl;  
    i.writeImage("blurFilter.ppm");
    cout << "   parallel processing" <<endl;    time(&begin); 
    i.blurFilter(13, true);
    time(&end);
    time_spent = difftime(end, begin);
    printf("    total time: %f sec\n",time_spent);
    cout << "   writing" <<endl;  
    i.writeImage("blurFilterParallel.ppm");

    cout << "sharpen filter" << endl;
    cout << "   sequential processing" <<endl;    time(&begin); 
    i.sharpenFilter(7,false);
    time(&end);
    time_spent = difftime(end, begin);
    printf("    total time: %f sec\n",time_spent);
    cout << "   writing" <<endl;  
    i.writeImage("sharpenFilter.ppm");
    cout << "   parallel processing" <<endl;    time(&begin); 
    i.sharpenFilter(7,true);
    time(&end);
    time_spent = difftime(end, begin);
    printf("    total time: %f sec\n",time_spent);
    cout << "   writing" <<endl;  
    i.writeImage("sharpenFilterParallel.ppm");

    cout << "grey filter" << endl;
    cout << "   sequential processing" <<endl;
    time(&begin);   
    i.greyFilter();
    time(&end);
    time_spent = difftime(end, begin);
    printf("    total time: %f sec\n",time_spent);
    cout << "   writing" <<endl;  
    i.writeImage("greyFilter.ppm");

    cout << "horizontal sharpen filter" << endl;
    cout << "   sequential processing" <<endl;
    time(&begin);   
    i.horizontalSharpenFilter(3, false);
    time(&end);
    time_spent = difftime(end, begin);
    printf("    total time: %f sec\n",time_spent);
    cout << "   writing" <<endl;  
    i.writeImage("horizontalSharpenFilter.ppm");
    cout << "   parallel processing" <<endl;
    time(&begin);   
    i.horizontalSharpenFilter(3, true);
    time(&end);
    time_spent = difftime(end, begin);
    printf("    total time: %f sec\n",time_spent);
    cout << "   writing" <<endl;  
    i.writeImage("horizontalSharpenFilterParallel.ppm");

    cout << "vertical sharpen filter" << endl;
    cout << "   sequential processing" <<endl;
    time(&begin);  
    i.verticalSharpenFilter(3, false);
    time(&end);
    time_spent = difftime(end, begin);
    printf("    total time: %f sec\n",time_spent);
    cout << "   writing" <<endl;  
    i.writeImage("verticalSharpenFilter.ppm");
    cout << "   parallel processing" <<endl;
    time(&begin);  
    i.verticalSharpenFilter(3, true);
    time(&end);
    time_spent = difftime(end, begin);
    printf("    total time: %f sec\n",time_spent);
    cout << "   writing" <<endl;  
    i.writeImage("verticalSharpenFilterParalle.ppm");

    cout << "gaussian blur filter" <<endl;
    cout << "   sequential processing" <<endl;
    time(&begin); 
    i.gaussianBlurFilter(7, false);
    time(&end);
    time_spent = difftime(end, begin);
    printf("    total time: %f sec\n",time_spent);
    cout << "   writing" <<endl;  
    i.writeImage("gaussianBlurFilter.ppm");
    cout << "   parallel processing" <<endl;
    time(&begin); 
    i.gaussianBlurFilter(7, true);
    time(&end);
    time_spent = difftime(end, begin);
    printf("    total time: %f sec\n",time_spent);
    cout << "   writing" <<endl;  
    i.writeImage("gaussianBlurFilterParallel.ppm");

    return 0;
}
/*
        OUTPUT

    reading
    blue filter
    sequential processing
        total time: 0.000000 sec
    writing
    blur filter
    sequential processing
        total time: 57.000000 sec
    writing
    parallel processing
        total time: 7.000000 sec
    writing
    sharpen filter
    sequential processing
        total time: 17.000000 sec
    writing
    parallel processing
        total time: 3.000000 sec
    writing
    grey filter
    sequential processing
        total time: 1.000000 sec
    writing
    horizontal sharpen filter
    sequential processing
        total time: 3.000000 sec
    writing
    parallel processing
        total time: 1.000000 sec
    writing
    vertical sharpen filter
    sequential processing
        total time: 4.000000 sec
    writing
    parallel processing
        total time: 1.000000 sec
    writing
    gaussian blur filter
    sequential processing
        total time: 17.000000 sec
    writing
    parallel processing
        total time: 2.000000 sec
    writing

*/