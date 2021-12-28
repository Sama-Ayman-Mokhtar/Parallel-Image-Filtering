#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Image.hpp"
#include <pthread.h>
#include <omp.h>

using namespace std;
//g++ -pthread -fopenmp main.cpp Image.cpp Image.hpp
//g++ -pthread -fopenmp main.cpp Image.cpp
//-fopenmp does not work correctly in Makefile!

//if blur filter then use kernel size > 5
int main(){
   
   cout << "reading" << endl;
   Image i("horse.ppm");

    time_t begin, end;
    double time_spent;
    
    /*cout << "blue filter" <<endl;
    cout << "   sequential processing" <<endl;
    time(&begin); 
    i.blueFilter();
    time(&end);
    time_spent = difftime(end, begin);
    printf("    total time: %f sec\n",time_spent);
    cout << "   writing" <<endl;  
    i.writeImage("blueFilter.ppm");*/

    cout << "blur filter" <<endl;
    cout << "   sequential processing" <<endl;    time(&begin); 
    i.blurFilter(13, SEQUENTIAL);
    time(&end);
    time_spent = difftime(end, begin);
    printf("    total time: %f sec\n",time_spent);
    cout << "   writing" <<endl;  
    i.writeImage("blurFilter.ppm");
    cout << "   pthreads parallel processing" <<endl;    time(&begin); 
    i.blurFilter(13, PTHREADS);
    time(&end);
    time_spent = difftime(end, begin);
    printf("    total time: %f sec\n",time_spent);
    cout << "   writing" <<endl;  
    i.writeImage("blurFilterParallel.ppm");
     cout << "   openMP parallel processing" <<endl;    time(&begin); 
    i.blurFilter(13, OPEN_MP);
    time(&end);
    time_spent = difftime(end, begin);
    printf("    total time: %f sec\n",time_spent);
    cout << "   writing" <<endl;  
    i.writeImage("blurFilterOMP.ppm");

    cout << "sharpen filter" << endl;
    cout << "   sequential processing" <<endl;    time(&begin); 
    i.sharpenFilter(7,SEQUENTIAL);
    time(&end);
    time_spent = difftime(end, begin);
    printf("    total time: %f sec\n",time_spent);
    cout << "   writing" <<endl;  
    i.writeImage("sharpenFilter.ppm");
    cout << "   pthreads parallel processing" <<endl;    time(&begin); 
    i.sharpenFilter(7,PTHREADS);
    time(&end);
    time_spent = difftime(end, begin);
    printf("    total time: %f sec\n",time_spent);
    cout << "   writing" <<endl;  
    i.writeImage("sharpenFilterParallel.ppm");
    cout << "   openMP parallel processing" <<endl;    time(&begin); 
    i.sharpenFilter(7,OPEN_MP);
    time(&end);
    time_spent = difftime(end, begin);
    printf("    total time: %f sec\n",time_spent);
    cout << "   writing" <<endl;  
    i.writeImage("sharpenFilterOMP.ppm");

    /*cout << "grey filter" << endl;
    cout << "   sequential processing" <<endl;
    time(&begin);   
    i.greyFilter();
    time(&end);
    time_spent = difftime(end, begin);
    printf("    total time: %f sec\n",time_spent);
    cout << "   writing" <<endl;  
    i.writeImage("greyFilter.ppm");*/

    cout << "horizontal sharpen filter" << endl;
    cout << "   sequential processing" <<endl;
    time(&begin);   
    i.horizontalSharpenFilter(3, SEQUENTIAL);
    time(&end);
    time_spent = difftime(end, begin);
    printf("    total time: %f sec\n",time_spent);
    cout << "   writing" <<endl;  
    i.writeImage("horizontalSharpenFilter.ppm");
    cout << "   pthreads parallel processing" <<endl;
    time(&begin);   
    i.horizontalSharpenFilter(3, PTHREADS);
    time(&end);
    time_spent = difftime(end, begin);
    printf("    total time: %f sec\n",time_spent);
    cout << "   writing" <<endl;  
    i.writeImage("horizontalSharpenFilterParallel.ppm");
    cout << "   openMP parallel processing" <<endl;
    time(&begin);   
    i.horizontalSharpenFilter(3, OPEN_MP);
    time(&end);
    time_spent = difftime(end, begin);
    printf("    total time: %f sec\n",time_spent);
    cout << "   writing" <<endl;  
    i.writeImage("horizontalSharpenFilterOMP.ppm");

    cout << "vertical sharpen filter" << endl;
    cout << "   sequential processing" <<endl;
    time(&begin);  
    i.verticalSharpenFilter(3, SEQUENTIAL);
    time(&end);
    time_spent = difftime(end, begin);
    printf("    total time: %f sec\n",time_spent);
    cout << "   writing" <<endl;  
    i.writeImage("verticalSharpenFilter.ppm");
    cout << "   pthreads parallel processing" <<endl;
    time(&begin);  
    i.verticalSharpenFilter(3, PTHREADS);
    time(&end);
    time_spent = difftime(end, begin);
    printf("    total time: %f sec\n",time_spent);
    cout << "   writing" <<endl;  
    i.writeImage("verticalSharpenFilterParallel.ppm");
    cout << "   openMP parallel processing" <<endl;
    time(&begin);  
    i.verticalSharpenFilter(3, OPEN_MP);
    time(&end);
    time_spent = difftime(end, begin);
    printf("    total time: %f sec\n",time_spent);
    cout << "   writing" <<endl;  
    i.writeImage("verticalSharpenFilterOMP.ppm");

    cout << "gaussian blur filter" <<endl;
    cout << "   sequential processing" <<endl;
    time(&begin); 
    i.gaussianBlurFilter(7, SEQUENTIAL);
    time(&end);
    time_spent = difftime(end, begin);
    printf("    total time: %f sec\n",time_spent);
    cout << "   writing" <<endl;  
    i.writeImage("gaussianBlurFilter.ppm");
    cout << "   parallel processing" <<endl;
    time(&begin); 
    i.gaussianBlurFilter(7, PTHREADS);
    time(&end);
    time_spent = difftime(end, begin);
    printf("    total time: %f sec\n",time_spent);
    cout << "   writing" <<endl;  
    i.writeImage("gaussianBlurFilterParallel.ppm");
    cout << "   openMP parallel processing" <<endl;
    time(&begin); 
    i.gaussianBlurFilter(7, OPEN_MP);
    time(&end);
    time_spent = difftime(end, begin);
    printf("    total time: %f sec\n",time_spent);
    cout << "   writing" <<endl;  
    i.writeImage("gaussianBlurFilterOMP.ppm");

    return 0;
}
/*
        OUTPUT

    reading
blur filter
   sequential processing
    total time: 38.000000 sec
   writing
   pthreads parallel processing
    total time: 6.000000 sec
   writing
   openMP parallel processing
    total time: 6.000000 sec
   writing
sharpen filter
   sequential processing
    total time: 11.000000 sec
   writing
   pthreads parallel processing
    total time: 2.000000 sec
   writing
   openMP parallel processing
    total time: 2.000000 sec
   writing
horizontal sharpen filter
   sequential processing
    total time: 3.000000 sec
   writing
   pthreads parallel processing
    total time: 1.000000 sec
   writing
   openMP parallel processing
    total time: 1.000000 sec
   writing
vertical sharpen filter
   sequential processing
    total time: 3.000000 sec
   writing
   pthreads parallel processing
    total time: 0.000000 sec
   writing
   openMP parallel processing
    total time: 1.000000 sec
   writing
gaussian blur filter
   sequential processing
    total time: 11.000000 sec
   writing
   parallel processing
    total time: 2.000000 sec
   writing
   openMP parallel processing
    total time: 2.000000 sec
   writing

*/