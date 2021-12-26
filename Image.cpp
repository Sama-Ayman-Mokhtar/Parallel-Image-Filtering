
#include "Image.hpp"

Image::Image(string old_image_name)
{
    ifstream old_image;
    old_image.open(old_image_name);

    if(!old_image.is_open())
        cerr << "[!] couldn't open file "<< old_image_name << endl;
   
    old_image >> type;
    old_image >> width;
    old_image >> height;
    old_image >> rgb;

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

void Image::blueFilter(vector<vector<int>> &img)
{
    for(int row = 0 ; row < height; row ++){
        for (int col = 0; col < width; col++)
        {
            img[row].push_back(mat[row][col*3] );
            img[row].push_back(mat[row][col*3+1] );
            img[row].push_back(mat[row][col*3+2] + 50 > 255 ? 255 : mat[row][col*3+2] + 50);

        }   
    }
}

void Image::blurFilter(vector<vector<int>> &img, int kernel_size)
{

    vector<vector<double>> kernel;
    for(int j = 0; j < kernel_size; j++){
        vector<double> v1(kernel_size, 1.0/(kernel_size * kernel_size));
        kernel.push_back(v1);
    }

    applyKernel(img, kernel);
}

void Image::sharpenFilter(vector<vector<int>> &img)
{
    int kernel_size = 3;
    int A = 0;

    vector<vector<double>> kernel = {
        {1,  1,  1},
        {1,-8-A, 1},
        {1,  1,  1}
        };

    applyKernel(img, kernel);
}

void Image::applyKernel(vector<vector<int>> &img, vector<vector<double>> &kernel)
{
    int kernel_size = kernel.size();

    vector<vector<int>> imgDes;
    for(int j = 0; j < height; j++){
        vector<int> v1;
        imgDes.push_back(v1);
    }

    clone(imgDes);

    int num = kernel_size / 2;
    padding(imgDes, num);

    for (int i = 0; i <= imgDes.size()-kernel_size; i++)
    {
        for (int j = 0; j <= imgDes[0].size()-kernel_size; j+=3)
        {
            double temp_red = 0, temp_green = 0, temp_blue = 0;
            
            for (int k = 0; k < kernel.size(); k++)
            {
                for (int l = 0; l < kernel[0].size(); l++)
                {          
                    temp_red += kernel[k][l]*imgDes[i+k][(j)+3*l];
                    temp_green += kernel[k][l]*imgDes[i+k][(j+1)+3*l];
                    temp_blue += kernel[k][l]*imgDes[i+k][(j+2)+3*l]; 
                }   
            }
            temp_red = temp_red > 255 ? 255 : temp_red;
            temp_green = temp_green > 255 ? 255 : temp_green;      
            temp_blue = temp_blue > 255 ? 255 : temp_blue;      
    
            img[i].push_back(temp_red < 0 ? 0 : temp_red);
            img[i].push_back(temp_green < 0 ? 0 : temp_green);
            img[i].push_back(temp_blue < 0 ? 0 : temp_blue);
        }
    }

}

void Image::greyFilter(vector<vector<int>> &img)
{
    for(int row = 0 ; row < height; row ++){
        for (int col = 0; col < width; col++)
        {
            for(int num = 0 ; num < 3; num ++)
                img[row].push_back((mat[row][col*3] + mat[row][col*3+1] + mat[row][col*3+2]) / 3);

        }   
    }
}

void Image::clone(vector<vector<int>> &imgDes)
{
    for (int i = 0; i < mat.size(); i++)
    {
        for (int j = 0; j < mat[i].size(); j++)
        {      
            imgDes[i].push_back(mat[i][j]);
        }
    }
}

void Image::padding(vector<vector<int>> &img, int num)
{
    //right and left padding
    for(int i = 0; i < img.size() ; i++){
        for(int j = 0; j < num; j++)
        {
            img[i].insert(img[i].begin(), 0);
            img[i].push_back(0);
        }
    }

    //top and down padding
    for(int i = 0; i < num; i++)
    {
        vector<int> v(img[0].size(),0);
        img.insert(img.begin(), v);
        img.push_back(v);
    }
}

void Image::writeImage(string new_image_name, vector<vector<int>> img)
{
    ofstream newImage;
    newImage.open(new_image_name);

    newImage << type << endl;
    newImage << width << " " << height << endl;
    newImage << rgb << endl;

    for(int row = 0 ; row < height; row ++){
        for (int col = 0; col < width; col++)
        {
            newImage << img[row][col*3] << " ";
            newImage << img[row][col*3 + 1] << " ";
            newImage << img[row][col*3 + 2] << " " << endl;
        }
        
    }
    newImage.close();
}
