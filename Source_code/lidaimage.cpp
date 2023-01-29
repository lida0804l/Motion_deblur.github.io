#include "lidaimage.h"

LidaImage::LidaImage(int row, int col)
{
    this->row = row;
    this->col = col;

    matrix3D = new float**[3];
    for(int i = 0; i < 3; ++i){
        matrix3D[i] = new float *[row];
        for(int j = 0; j < row; ++j){
            matrix3D[i][j] = new float[col];
            for(int k = 0; k < col; ++k){
                matrix3D[i][j][k] = 0;
            }
        }
    }
}

LidaImage::~LidaImage()
{
    for(int i = 0; i < 3; ++i){
        for(int j=0; j < row; ++j){
            delete [] matrix3D[i][j];
        }
        delete [] matrix3D[i];
    }
    delete [] matrix3D;
    matrix3D = 0;
    //    cout << "delete" << endl;
}

void LidaImage::scaling(LidaImage::Calibration calibration)
{
    if(calibration == LidaImage::cutoff){
        for (int x = 0; x < row; x++) {
            for (int y = 0; y < col; y++) {
                for (int channel = 0; channel < 3; channel++) {
                    if(matrix3D[channel][x][y] > 255){
                        matrix3D[channel][x][y] = 255;
                    }
                    else if (matrix3D[channel][x][y] < 0) {
                        matrix3D[channel][x][y] = 0;
                    }
                }
            }
        }
    }
    else if (calibration == LidaImage::full_range) {
        float R_min = matrix3D[0][0][0];
        float G_min = matrix3D[1][0][0];
        float B_min = matrix3D[2][0][0];
        for (int x = 0; x < row; x++) {
            for (int y = 0; y < col; y++) {
                if(matrix3D[0][x][y] < R_min){
                    R_min = matrix3D[0][x][y];
                }
                if(matrix3D[1][x][y] < G_min){
                    G_min = matrix3D[1][x][y];
                }
                if(matrix3D[2][x][y] < B_min){
                    B_min = matrix3D[2][x][y];
                }
            }
        }
        for (int x = 0; x < row; x++) {
            for (int y = 0; y < col; y++) {
                matrix3D[0][x][y] = matrix3D[0][x][y] - R_min;
                matrix3D[1][x][y] = matrix3D[1][x][y] - G_min;
                matrix3D[2][x][y] = matrix3D[2][x][y] - B_min;
            }
        }
        const int K = 255;
        float R_max = matrix3D[0][0][0];
        float G_max = matrix3D[1][0][0];
        float B_max = matrix3D[2][0][0];
        for (int x = 0; x < row; x++) {
            for (int y = 0; y < col; y++) {
                if(matrix3D[0][x][y] > R_max){
                    R_max = matrix3D[0][x][y];
                }
                if(matrix3D[1][x][y] > G_max){
                    G_max = matrix3D[1][x][y];
                }
                if(matrix3D[2][x][y] > B_max){
                    B_max = matrix3D[2][x][y];
                }
            }
        }
        for (int x = 0; x < row; x++) {
            for (int y = 0; y < col; y++) {
                matrix3D[0][x][y] = K*(matrix3D[0][x][y]/R_max);
                matrix3D[1][x][y] = K*(matrix3D[1][x][y]/G_max);
                matrix3D[2][x][y] = K*(matrix3D[2][x][y]/B_max);
            }
        }
    }
}
