#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Image.hpp"
#include <pthread.h>
#include <omp.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace std;

int main(){

    string filename;
    int kernel_size;
    int num_of_processors;

    cout << "Enter image name: ";
    cin >> filename;

    cout << "Enter kernel size: ";
    cin >> kernel_size;

    cout << "Enter number of processors: ";
    cin >> num_of_processors;

    cv::Mat image = cv::imread(filename); 
    if (image.empty()) 
    {
        cerr << "[!] couldn't open file " << endl;
        return 1;
    }
    std::vector<int> p(2);
    p[0] = cv::IMWRITE_PXM_BINARY;
    p[1] = 0; 
    cv::Mat padded_image;
    cv::copyMakeBorder(image, padded_image, kernel_size/2, kernel_size/2, kernel_size/2, kernel_size/2, cv::BORDER_CONSTANT, cv::Scalar(0));
    cv::imwrite("img.ppm", padded_image, p );
   
    cout << "reading" << endl;
    Image i("img.ppm", kernel_size);

    time_t begin, end;
    double time_spent;

    cout << "High pass filter" << endl;
    cout << "   sequential processing" <<endl;    
    time(&begin); 
    i.sharpenFilter(kernel_size, SEQUENTIAL, num_of_processors);
    time(&end);
    time_spent = difftime(end, begin);
    printf("    total time: %f sec\n",time_spent);
    cout << "   writing" <<endl;  
    i.writeImage("sharpenFilter.ppm");
    
    cout << "   openMP parallel processing" <<endl;    
    time(&begin); 
    i.sharpenFilter(kernel_size,OPEN_MP, num_of_processors);
    time(&end);
    time_spent = difftime(end, begin);
    printf("    total time: %f sec\n",time_spent);
    cout << "   writing" <<endl;  
    i.writeImage("sharpenFilterOMP.ppm");

    cv::Mat output_image_seqential = cv::imread("sharpenFilterOMP.ppm"); 
    cv::Mat output_image_openMP = cv::imread("sharpenFilter.ppm"); 
    if (image.empty()) 
    {
        cerr << "[!] couldn't open file " << endl;
        return 1;
    }
    cv::imwrite("output_seqential_"+filename, output_image_seqential);
    cv::imwrite("output_openMP_"+filename, output_image_openMP);

    return 0;
}