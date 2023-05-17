#include "Image.hpp"

vector<vector<int>> resImg;
vector<vector<double>> kernel;
int not_padded_height;
int not_padded_width;

Image::Image(string old_image_name, int kernel_size)
{
    //reading img
    int padded_width, padded_height;
    ifstream old_image;
    old_image.open(old_image_name);

    if(!old_image.is_open())
        cerr << "[!] couldn't open file "<< old_image_name << endl;
   
    old_image >> type;
    old_image >> padded_width;
    old_image >> padded_height;
    old_image >> rgb;
    not_padded_height = padded_height - (kernel_size/2)*2;
    not_padded_width = padded_width - (kernel_size/2)*2;
    for(int i = 0; i < padded_height; i++){
        vector<int> v1;
        mat.push_back(v1);
    }

    int row_index  = 0;
    int col_index = 0;
    string red="", green="",blue="";
    int r = 0, g =0, b =0;

    while(row_index < padded_height && !old_image.eof()){

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
        if(col_index >= 3 * padded_width){
            col_index = 0;
            row_index ++;
        }
    }
    old_image.close();
}

//edge detection
void Image::sharpenFilter(int kernel_size, int processing_type, int num_of_processors)
{
    resImg.clear();
    for(int j = 0; j < not_padded_height; j++){
        vector<int> vec(not_padded_width*3, 0);
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
    applyKernel(processing_type, kernel_size, num_of_processors);       
}

void Image::applyKernel(int processing_type, int kernel_size, int num_of_processors)
{
    if(processing_type == SEQUENTIAL)
    {
        sequentialApplyKernel(kernel_size);
    }
    else if(processing_type == OPEN_MP)
    {

        openMP_parallelApplyKernel( kernel_size, num_of_processors);
    }
}

void Image::openMP_parallelApplyKernel(int kernel_size, int num_of_processors)
{
    omp_set_num_threads(num_of_processors);
    #pragma omp parallel
    {
        int threadID = omp_get_thread_num();
        int threads_count = omp_get_num_threads();

        int height = not_padded_height;
        int width = not_padded_width*3;

        int heightInterval = height / threads_count;
    
        int strtHeight = threadID * heightInterval;
        int endHeight = strtHeight + heightInterval;

        if(threadID+1 == threads_count)
        {
            endHeight = height;
        }

        for (int i = strtHeight; i < endHeight; i++)
        {
            for (int j = 0; j < width; j+=3)
            {
                double temp_red = 0, temp_green = 0, temp_blue = 0;
                
                for (int k = 0; k < kernel.size(); k++)
                {
                    for (int l = 0; l < kernel[0].size(); l++)
                    {          
                        temp_red += kernel[k][l]*mat[i+k][(j)+3*l];
                        temp_green += kernel[k][l]*mat[i+k][(j+1)+3*l];
                        temp_blue += kernel[k][l]*mat[i+k][(j+2)+3*l]; 
                    }   
                }
                temp_red  = ((temp_red * 255) / ((255*(kernel_size*kernel_size-1))*2)) + 128;
                temp_green = ((temp_green * 255) / ((255*(kernel_size*kernel_size-1))*2)) + 128;
                temp_blue = ((temp_blue * 255) / ((255*(kernel_size*kernel_size-1))*2)) + 128;     
        
                resImg[i][j] = (temp_red < 0 ? 0 : temp_red);
                resImg[i][j+1] = (temp_green < 0 ? 0 : temp_green);
                resImg[i][j+2] = (temp_blue < 0 ? 0 : temp_blue);
            }
        }
    }
}

void Image::sequentialApplyKernel(int kernel_size)
{
    for (int i = 0; i < not_padded_height; i++)
    {
        for (int j = 0; j < not_padded_width*3; j+=3)
        {
            double temp_red = 0, temp_green = 0, temp_blue = 0;
            
            for (int k = 0; k < kernel.size(); k++)
            {
                for (int l = 0; l < kernel[0].size(); l++)
                {          
                    temp_red += kernel[k][l]*mat[i+k][(j)+3*l];
                    temp_green += kernel[k][l]*mat[i+k][(j+1)+3*l];
                    temp_blue += kernel[k][l]*mat[i+k][(j+2)+3*l]; 
                }   
            }
            temp_red  = ((temp_red * 255) / ((255*(kernel_size*kernel_size-1))*2)) + 128;
            temp_green = ((temp_green * 255) / ((255*(kernel_size*kernel_size-1))*2)) + 128;
            temp_blue = ((temp_blue * 255) / ((255*(kernel_size*kernel_size-1))*2)) + 128;     
            
            resImg[i][j] = (temp_red < 0 ? 0 : temp_red);
            resImg[i][j+1] = (temp_green < 0 ? 0 : temp_green);
            resImg[i][j+2] = (temp_blue < 0 ? 0 : temp_blue);
        }
    }
}

void Image::writeImage(string new_image_name)
{
    ofstream newImage;
    newImage.open(new_image_name);
    newImage << type << endl;
    newImage << not_padded_width << " " << not_padded_height << endl;
    newImage << rgb << endl;
    for(int row = 0 ; row < not_padded_height; row ++){
        for (int col = 0; col < not_padded_width; col++)
        {
            newImage << resImg[row][col*3] << " ";
            newImage << resImg[row][col*3 + 1] << " ";
            newImage << resImg[row][col*3 + 2] << " " << endl;
        } 
    }
    newImage.close();
}