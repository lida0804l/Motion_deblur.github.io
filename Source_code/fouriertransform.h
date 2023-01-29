#ifndef FOURIERTRANSFORM_H
#define FOURIERTRANSFORM_H

#include <iostream>
#include <lidaimage.h>
#include <frequencydomain.h>

#include <complex>
#include <valarray>

typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;

using namespace std;

class FourierTransform
{
public:
    FourierTransform(LidaImage *input);
    ~FourierTransform();
    enum Mode{
        ideal_rect,
        butterworth_circle,
    };

    int original_row;
    int original_col;

    int row;
    int col;

    Complex*** frequency;

    void F(CArray &x);
    void fft(LidaImage *input);
    LidaImage* ifft();
    LidaImage* get_spectrum();

    static LidaImage* ILPF(LidaImage* input, float D0 = 60);
    static LidaImage* BLPF(LidaImage* input, float n = 2, float D0 = 60);
    static LidaImage* GLPF(LidaImage* input, float D0 = 60);

    static LidaImage* IHPF(LidaImage* input, float D0 = 60);
    static LidaImage* BHPF(LidaImage* input, float n = 2, float D0 = 60);
    static LidaImage* GHPF(LidaImage* input, float D0 = 60);

    static LidaImage* laplacianSharpening(LidaImage* input);
    static LidaImage* high_frequency_emphasis(LidaImage* input, float k1 = 0.5, float k2 = 0.75, float D0 = 40);
    static LidaImage* homomorphic(LidaImage* input, float gamma_H = 2, float gamma_L = 0.75, float c = 1, float D0 = 80);
    static LidaImage* selective_filtering(LidaImage* input, FourierTransform::Mode mode = FourierTransform::ideal_rect);
//    static LidaComplex* F(int u, LidaComplex* input, int length);

    static LidaImage* motion_blur(LidaImage* input, float a = 0.1, float b = 0.1, float T = 1);
//    static LidaImage* wiener_filter(LidaImage* input, float K);
    LidaImage* wiener_filter(float angle, float length, float T, float SNR);

    static LidaImage* constraint_least_square_filter(LidaImage* input, float gamma);
};

#endif // FOURIERTRANSFORM_H

//LidaImage* input = LIDA::QImage2LidaImage(image);
//    LidaImage* output = FourierTransform::homomorphic(input, 2, 0.75, 1, 80);
//    LidaImage* output = FourierTransform::ILPF(input, 300);
//    LidaImage* output = FourierTransform::BLPF(input, 2, 100);
//    LidaImage* output = FourierTransform::GLPF(input, 100);
//    LidaImage* output = FourierTransform::IHPF(input, 100);
//    LidaImage* output = FourierTransform::BHPF(input, 4, 50);
//    LidaImage* output = FourierTransform::GHPF(input, 100);
//    LidaImage* output = FourierTransform::laplacianSharpening(input);
//    LidaImage* output = FourierTransform::high_frequency_emphasis(input, 1, 2, 40);
//    LidaImage* output = FourierTransform::selective_filtering(input, FourierTransform::ideal_rect);
//LidaImage* output = FourierTransform::selective_filtering(input, FourierTransform::butterworth_circle);

//    for (int x = 0; x < output->row; x++) {
//        for (int y = 0; y < output->col; y++) {
//            for (int channel = 0; channel < 3; channel++) {
//                if(output->matrix3D[channel][x][y] < 0){
//                    output->matrix3D[channel][x][y] = 0;
//                }
//                else {
//                    output->matrix3D[channel][x][y] = 255;
//                }
//            }
//        }
//    }

//output->scaling(LidaImage::cutoff);
//QImage* result = LidaImage2QImage(output);
//scene->image = result;
//LIDA::showImage(result);
