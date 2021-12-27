#include "Image.hpp"

int globalWidth;
vector<vector<int>> resImg;
vector<vector<int>> tempMat;
vector<vector<double>> kernel;

Image::Image(string old_image_name)
{
    //reading img

    ifstream old_image;
    old_image.open(old_image_name);

    if(!old_image.is_open())
        cerr << "[!] couldn't open file "<< old_image_name << endl;
   
    old_image >> type;
    old_image >> width;
    old_image >> height;
    old_image >> rgb;
    globalWidth = width;
    for(int i = 0; i < height; i++){
        vector<int> v1;
        mat.push_back(v1);
    }

    int row_index  = 0;
    int col_index = 0;
    string red="", green="",blue="";
    int r = 0, g =0, b =0;

    while(!old_image.eof()){

        old_image >> red;
        old_image >> green;
        old_image >> blue;

        stringstream redStream(red);
        stringstream greenStream(green);
        stringstream blueStream(blue);

        redStream >> r;
        greenStream >> g;
        blueStream >> b;
   
        mat[row_index].push_back(r);
        mat[row_index].push_back(g);
        mat[row_index].push_back(b);

        col_index += 3;
        if(col_index >= 3 * width){
            col_index = 0;
            row_index ++;
        }
    }
    old_image.close();
}

void Image::blueFilter()
{
    resImg.clear();
    for(int j = 0; j < height; j++){
        vector<int> vec;
        resImg.push_back(vec);
    }
    for(int row = 0 ; row < height; row ++){
        for (int col = 0; col < width; col++)
        {
            resImg[row].push_back(mat[row][col*3] );
            resImg[row].push_back(mat[row][col*3+1] );
            resImg[row].push_back(mat[row][col*3+2] + 50 > 255 ? 255 : mat[row][col*3+2] + 50);

        }   
    }
}

void Image::blurFilter(int kernel_size, bool useThreads)
{

    resImg.clear();
    for(int j = 0; j < height; j++){
        vector<int> vec(width*3, 0);
        resImg.push_back(vec);
    }

   // vector<vector<double>> kernel;
    kernel.clear();

    for(int j = 0; j < kernel_size; j++){

        vector<double> v1(kernel_size, 1.0/(kernel_size * kernel_size));
        kernel.push_back(v1);
    }
    initTempMat();
    applyKernel(useThreads);
}

void Image::gaussianBlurFilter(int kernel_size, bool useThreads)
{
    resImg.clear();
    for(int j = 0; j < height; j++){
        vector<int> vec(width*3, 0);
        resImg.push_back(vec);
    }

    //vector<vector<double>> kernel;
    kernel.clear();
    for(int j = 0; j < kernel_size; j++){
        vector<double> vec;
        kernel.push_back(vec);
    }

    fillGaussianKernel();
    
    initTempMat();
    applyKernel(useThreads);

}

void Image::fillGaussianKernel()
{
    //https://www.geeksforgeeks.org/gaussian-filter-generation-c/

    int halfSize = kernel.size() / 2;
	double sigma = 1.0;
    double r, s = 2.0 * sigma * sigma; // 2.0 wala halfSize
 
    double sum = 0.0;
 
    for (int x = -halfSize; x <= halfSize; x++) {
        for (int y = -halfSize; y <= halfSize; y++) {
            r = sqrt(x * x + y * y);
            kernel[x + halfSize].push_back((exp(-(r * r) / s)) / (M_PI * s));
            sum += kernel[x + halfSize][y + halfSize];
        }
    }
 
    for (int i = 0; i < kernel.size(); ++i)
        for (int j = 0; j < kernel.size(); ++j)
            kernel[i][j] /= sum;

}

//edge detection
void Image::sharpenFilter(int kernel_size, bool useThreads)
{
    resImg.clear();
    for(int j = 0; j < height; j++){
        vector<int> vec(width*3, 0);
        resImg.push_back(vec);
    }
    /*
    int A = 0;
    vector<vector<double>> kernel = {
        {1,  1,  1},
        {1,-8-A, 1},
        {1,  1,  1}
        };
        */
    
    //vector<vector<double>> kernel;
    kernel.clear();

    for(int j = 0; j < kernel_size; j++){

        vector<double> v1(kernel_size, 1.0);
        if(j == kernel_size / 2)
            v1[j] = -1 * (kernel_size * kernel_size - 1);

        kernel.push_back(v1);
    }

    initTempMat();
    applyKernel(useThreads);
   
    //pthread_exit(NULL);
       
}

void Image::applyKernel(bool useThreads)
{
     if(!useThreads)
    {
        sequentialApplyKernel();
        return;
    }

    pthread_t threads[THREADS_NUM];
    for (long i = 0; i < THREADS_NUM; i++)
    {
        if(pthread_create(&threads[i], NULL, parallelApplyKernel, (void *) i) < 0)
        {
            cerr << "[!] failed to create thread " << i << endl;
        }
    }
    for (long i = 0; i < THREADS_NUM; i++)
    {
        if(pthread_join(threads[i], NULL))
        {
            cerr << "[!] failed to join thread " << i << endl;
        }
    }

}


void* Image::parallelApplyKernel(void* thread_id)
{
    long threadID = (long) thread_id;
   
    
    int height = resImg.size();
    int width = globalWidth*3;

    int widthInterval = width / ROOT_THREADS_NUM;
    int heightInterval = height / ROOT_THREADS_NUM;
   
    int strtWidth = (threadID%ROOT_THREADS_NUM) * widthInterval;
    int endWidth = strtWidth + widthInterval;

    int strtHeight = (threadID/ROOT_THREADS_NUM) * heightInterval;
    int endHeight = strtHeight + heightInterval;

    if(threadID+1 == THREADS_NUM)
    {
        endWidth = width;
        endHeight = height;
    }

    for (int i = strtHeight; i < endHeight; i++)
    {
        for (int j = strtWidth; j < endWidth; j+=3)
        {
            double temp_red = 0, temp_green = 0, temp_blue = 0;
            
            for (int k = 0; k < kernel.size(); k++)
            {
                for (int l = 0; l < kernel[0].size(); l++)
                {          
                    temp_red += kernel[k][l]*tempMat[i+k][(j)+3*l];
                    temp_green += kernel[k][l]*tempMat[i+k][(j+1)+3*l];
                    temp_blue += kernel[k][l]*tempMat[i+k][(j+2)+3*l]; 
                }   
            }
            temp_red = temp_red > 255 ? 255 : temp_red;
            temp_green = temp_green > 255 ? 255 : temp_green;      
            temp_blue = temp_blue > 255 ? 255 : temp_blue;      
    
            resImg[i][j] = (temp_red < 0 ? 0 : temp_red);
            resImg[i][j+1] = (temp_green < 0 ? 0 : temp_green);
            resImg[i][j+2] = (temp_blue < 0 ? 0 : temp_blue);
        }
    }
    return NULL;
}


//vertical edge detection
void Image::verticalSharpenFilter(int kernel_size, bool useThreads)
{
    resImg.clear();
    for(int j = 0; j < height; j++){
        vector<int> vec(width*3, 0);
        resImg.push_back(vec);
    }
    /*
    int A = 0;
    vector<vector<double>> kernel = {
        {1, -2, 1},
        {1, -2, 1},
        {1, -2, 1}
        };
        */
    //vector<vector<double>> kernel;
    kernel.clear();

    for(int j = 0; j < kernel_size; j++){

        vector<double> v1(kernel_size, 1.0);
        v1[kernel_size / 2] = -1 * (kernel_size / 2 + 1);

        kernel.push_back(v1);
    }
    initTempMat();
    applyKernel(useThreads);
}

//horizontal edge detection
void Image::horizontalSharpenFilter( int kernel_size, bool useThreads)
{
    resImg.clear();
    for(int j = 0; j < height; j++){
        vector<int> vec(width*3, 0);
        resImg.push_back(vec);
    }
    /*
    int A = 0;
    vector<vector<double>> kernel = {
        {1,  1,   1},
        {-2, -2, -2},
        {1,  1,   1}
        };
        */
   // vector<vector<double>> kernel;
    kernel.clear();

    for(int j = 0; j < kernel_size; j++){
     
        if(j == kernel_size / 2){
             vector<double> v1(kernel_size, -1 * (kernel_size / 2 + 1));
             kernel.push_back(v1);
        }else{
            vector<double> v1(kernel_size, 1.0);
            kernel.push_back(v1);
        }
            
    }
    initTempMat();  
    applyKernel(useThreads);
}

//must call one of the filters before initTempMat (so that the kernel get initialized)
void Image::initTempMat()
{
    int kernel_size = kernel.size();

    //vector<vector<int>> imgDes;
    tempMat.clear();
    for(int j = 0; j < height; j++){
        vector<int> v1;
        tempMat.push_back(v1);
    }

    clone();

    int num = kernel_size / 2;
    padding(num);
}

//must call initTempMat before applyKernel
void Image::sequentialApplyKernel()
{

    for (int i = 0; i <= tempMat.size()-kernel.size(); i++)
    {
        for (int j = 0; j <= tempMat[0].size()-kernel.size(); j+=3)
        {
            double temp_red = 0, temp_green = 0, temp_blue = 0;
            
            for (int k = 0; k < kernel.size(); k++)
            {
                for (int l = 0; l < kernel[0].size(); l++)
                {          
                    temp_red += kernel[k][l]*tempMat[i+k][(j)+3*l];
                    temp_green += kernel[k][l]*tempMat[i+k][(j+1)+3*l];
                    temp_blue += kernel[k][l]*tempMat[i+k][(j+2)+3*l]; 
                }   
            }
            temp_red = temp_red > 255 ? 255 : temp_red;
            temp_green = temp_green > 255 ? 255 : temp_green;      
            temp_blue = temp_blue > 255 ? 255 : temp_blue;      
    
            resImg[i][j] = (temp_red < 0 ? 0 : temp_red);
            resImg[i][j+1] = (temp_green < 0 ? 0 : temp_green);
            resImg[i][j+2] = (temp_blue < 0 ? 0 : temp_blue);
        }
    }

}

void Image::greyFilter()
{
    resImg.clear();
    for(int j = 0; j < height; j++){
        vector<int> vec;
        resImg.push_back(vec);
    }
    for(int row = 0 ; row < height; row ++){
        for (int col = 0; col < width; col++)
        {
            for(int num = 0 ; num < 3; num ++)
                resImg[row].push_back((mat[row][col*3] + mat[row][col*3+1] + mat[row][col*3+2]) / 3);

        }   
    }
}

void Image::clone()
{
    for (int i = 0; i < mat.size(); i++)
    {
        for (int j = 0; j < mat[i].size(); j++)
        {      
            tempMat[i].push_back(mat[i][j]);
        }
    }
}

void Image::padding(int num)
{
    //right and left padding
    for(int i = 0; i < tempMat.size() ; i++){
        for(int j = 0; j < num; j++)
        {
            tempMat[i].insert(tempMat[i].begin(), 0);
            tempMat[i].push_back(0);
        }
    }

    //top and down padding
    for(int i = 0; i < num; i++)
    {
        vector<int> v(tempMat[0].size(),0);
        tempMat.insert(tempMat.begin(), v);
        tempMat.push_back(v);
    }
}

void Image::writeImage(string new_image_name)
{
    ofstream newImage;
    newImage.open(new_image_name);

    newImage << type << endl;
    newImage << width << " " << height << endl;
    newImage << rgb << endl;

    for(int row = 0 ; row < height; row ++){
        for (int col = 0; col < width; col++)
        {
            newImage << resImg[row][col*3] << " ";
            newImage << resImg[row][col*3 + 1] << " ";
            newImage << resImg[row][col*3 + 2] << " " << endl;
        }
        
    }
    newImage.close();
}