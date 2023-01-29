#include "fouriertransform.h"

FourierTransform::FourierTransform(LidaImage *input)
{
    FourierTransform::fft(input);
}

FourierTransform::~FourierTransform()
{
    for(int i = 0; i < 3; ++i){
        for(int j=0; j < row; ++j){
            delete [] frequency[i][j];
        }
        delete [] frequency[i];
    }
    delete [] frequency;
    frequency = 0;
//    cout << "delete" << endl;
}

void FourierTransform::F(CArray &x)
{
    // DFT
    unsigned int N = x.size(), k = N, n;
    double thetaT = 3.14159265358979323846264338328L / N;
    Complex phiT = Complex(cos(thetaT), -sin(thetaT)), T;
    while (k > 1)
    {
        n = k;
        k >>= 1;
        phiT = phiT * phiT;
        T = 1.0L;
        for (unsigned int l = 0; l < k; l++)
        {
            for (unsigned int a = l; a < N; a += n)
            {
                unsigned int b = a + k;
                Complex t = x[a] - x[b];
                x[a] += x[b];
                x[b] = t * T;
            }
            T *= phiT;
        }
    }
    // Decimate
    unsigned int m = (unsigned int)log2(N);
    for (unsigned int a = 0; a < N; a++)
    {
        unsigned int b = a;
        // Reverse bits
        b = (((b & 0xaaaaaaaa) >> 1) | ((b & 0x55555555) << 1));
        b = (((b & 0xcccccccc) >> 2) | ((b & 0x33333333) << 2));
        b = (((b & 0xf0f0f0f0) >> 4) | ((b & 0x0f0f0f0f) << 4));
        b = (((b & 0xff00ff00) >> 8) | ((b & 0x00ff00ff) << 8));
        b = ((b >> 16) | (b << 16)) >> (32 - m);
        if (b > a)
        {
            Complex t = x[a];
            x[a] = x[b];
            x[b] = t;
        }
    }
    //LidaComplex* FourierTransform::F(int u, LidaComplex *input, int length)
    //{
    //    LidaComplex* output = new LidaComplex[3];
    //    int K = length/2;
    //    const double Pi = 3.1415926;
    //    if((length % 2) != 0){
    //        cout << "Error: length should be an integer power of 2 " << endl;
    //    }
    //    if(length == 2){
    //        output[0].set(input[0].real, input[0].imaginary);

    //        LidaComplex F_odd(input[1].real, input[1].imaginary);
    //        LidaComplex W(cos(Pi*u/K), -1*sin(Pi*u/K));
    //        double realpart = ((F_odd.real)*(W.real)) - ((F_odd.imaginary)*(W.imaginary));
    //        double imaginarypart = ((F_odd.real)*(W.imaginary)) + ((F_odd.imaginary)*(W.real));
    ////        double realpart = 1;       //
    ////        double imaginarypart = 1;  //
    //        output[1].set(realpart, imaginarypart);
    //    }
    //    else {
    //        LidaComplex* even = new LidaComplex[K];
    //        LidaComplex* odd = new LidaComplex[K];
    //        for(int x = 0; x < K; x++) {
    //            even[x].set(input[2*x].real, input[2*x].imaginary);
    //            odd[x].set(input[(2*x)+1].real, input[(2*x)+1].imaginary);
    //        }

    //        LidaComplex* F_even = F(u, even, K);
    //        output[0].set(F_even[2].real, F_even[2].imaginary);

    //        LidaComplex* F_odd = F(u, odd, K);
    //        LidaComplex W(cos(Pi*u/K), -1*sin(Pi*u/K));
    //        double realpart = ((F_odd[2].real)*(W.real)) - ((F_odd[2].imaginary)*(W.imaginary));
    //        double imaginarypart = ((F_odd[2].real)*(W.imaginary)) + ((F_odd[2].imaginary)*(W.real));
    ////        double realpart = 1;       //
    ////        double imaginarypart = 1;  //
    //        output[1].set(realpart, imaginarypart);

    //        delete[] even;
    //        delete[] odd;
    //        delete[] F_even;
    //        delete[] F_odd;
    //    }
    //    output[2].set((output[0].real) + (output[1].real), (output[0].imaginary) + (output[1].imaginary));
    //    return output;
    //}
}

void FourierTransform::fft(LidaImage *input)
{
    original_row = input->row;
    original_col = input->col;
    int P = 2;
    int Q = 2;
    while(P < (input->row * 2))
    {P = P*2;}
    while(Q < (input->col * 2))
    {Q = Q*2;}

    int offset_x = (P - original_row)/2;
    int offset_y = (Q - original_col)/2;
//    cout << offset_x << " " << offset_y << endl;

    LidaImage *padded = new LidaImage(P, Q);
    for (int x = 0; x < input->row; x++) {
        for (int y = 0; y < input->col; y++) {
            for (int channel = 0; channel < 3; channel++) {
                padded->matrix3D[channel][x][y] = input->matrix3D[channel][x][y];
            }
        }
    }
    for (int x = 0; x < padded->row; x++) {
        for (int y = 0; y < padded->col; y++) {
            for (int channel = 0; channel < 3; channel++) {
                padded->matrix3D[channel][x][y] = pow(-1, (x+y))*(padded->matrix3D[channel][x][y]);
//                padded->matrix3D[channel][x][y] = pow(-1, (x+y))*(padded->matrix3D[channel][x][y]);
            }
        }
    }

    this->row = padded->row;
    this->col = padded->col;
    frequency = new Complex**[3];
    for(int i = 0; i < 3; ++i){
        frequency[i] = new Complex *[this->row];
        for(int j = 0; j < this->row; ++j){
            frequency[i][j] = new Complex[this->col];
            for(int k = 0; k < this->col; ++k){
//                frequency[i][j][k];
            }
        }
    }

    Complex* row_segment = new Complex[this->col];
    for (int channel = 0; channel < 3; channel++) {
        for (int x = 0; x < this->row; x++) {
            for (int y = 0; y < this->col; y++) {
                row_segment[y] = {padded->matrix3D[channel][x][y], 0};
            }
            CArray data(row_segment, this->col);
            FourierTransform::F(data);
            for(int y = 0; y < this->col; y++) {
                frequency[channel][x][y] = {data[y].real(), data[y].imag()};
            }
        }
    }
    delete[] row_segment;

    Complex* col_segment = new Complex[this->row];
    for (int channel = 0; channel < 3; channel++) {
        for (int y = 0; y < this->col; y++) {
            for (int x = 0; x < this->row; x++) {
                col_segment[x] = {frequency[channel][x][y].real(), frequency[channel][x][y].imag()};
            }
            CArray data(col_segment, this->row);
            FourierTransform::F(data);
            for(int x = 0; x < this->row; x++) {
                frequency[channel][x][y] = {data[x].real(), data[x].imag()};
            }
        }
    }
    delete[] col_segment;
    delete padded;
}

LidaImage *FourierTransform::ifft()
{
//    LidaImage* output = new LidaImage(this->row, this->col);
    LidaImage* output = new LidaImage(original_row, original_col);

    Complex*** frequency_clone = new Complex**[3];;
    for(int i = 0; i < 3; ++i){
        frequency_clone[i] = new Complex *[this->row];
        for(int j = 0; j < this->row; ++j){
            frequency_clone[i][j] = new Complex[this->col];
            for(int k = 0; k < this->col; ++k){
//                frequency[i][j][k];
            }
        }
    }
    for(int x = 0; x < this->row; x++){
        for(int y = 0; y < this->col; y++){
            for (int channel= 0; channel < 3; channel++) {
                frequency_clone[channel][x][y] = {frequency[channel][x][y].real() ,-1*(frequency[channel][x][y].imag())};
            }
        }
    }

    Complex* row_segment = new Complex[this->col];
    for (int channel = 0; channel < 3; channel++) {
        for (int x = 0; x < this->row; x++) {
            for (int y = 0; y < this->col; y++) {
                row_segment[y] = {frequency_clone[channel][x][y].real(), frequency_clone[channel][x][y].imag()};
            }
            CArray data(row_segment, this->col);
            FourierTransform::F(data);
            for(int y = 0; y < output->col; y++) {
                frequency_clone[channel][x][y] = {data[y].real(), data[y].imag()};
            }
        }
    }
    delete[] row_segment;

    Complex* col_segment = new Complex[this->row];
    for (int channel = 0; channel < 3; channel++) {
        for (int y = 0; y < this->col; y++) {
            for (int x = 0; x < this->row; x++) {
                col_segment[x] = {frequency_clone[channel][x][y].real(), frequency_clone[channel][x][y].imag()};
            }
            CArray data(col_segment, this->row);
            FourierTransform::F(data);
            for(int x = 0; x < this->row; x++) {
                frequency_clone[channel][x][y] = {data[x].real(), data[x].imag()};
            }
        }
    }
    delete[] col_segment;

    int MN = (this->row)*(this->col);

    for (int x = 0; x < output->row; x++) {
        for (int y = 0; y < output->col; y++) {
            for (int channel = 0; channel < 3; channel++) {
                output->matrix3D[channel][x][y] = (std::pow(-1,x+y))*(frequency_clone[channel][x][y].real())/(MN);
//                output->matrix3D[channel][x][y] = (std::pow(-1,x+y+offset_x+offset_y))*(frequency_clone[channel][x+offset_x][y+offset_y].real())/(MN);
//                frequency_clone[channel][x][y] = {(std::pow(-1,x+y))*(frequency_clone[channel][x][y].real())/(MN),0};
            }
        }
    }


    for(int i = 0; i < 3; ++i){
        for(int j=0; j < row; ++j){
            delete [] frequency_clone[i][j];
        }
        delete [] frequency_clone[i];
    }
    delete [] frequency_clone;
    frequency_clone = 0;

    return output;
}

LidaImage *FourierTransform::get_spectrum()
{
    LidaImage* output = new LidaImage(this->row, this->col);
    for (int x = 0; x < this->row; x++) {
        for (int y = 0; y < this->col; y++) {
            output->matrix3D[0][x][y] = std::abs(this->frequency[0][x][y]);
            output->matrix3D[1][x][y] = std::abs(this->frequency[1][x][y]);
            output->matrix3D[2][x][y] = std::abs(this->frequency[2][x][y]);

            output->matrix3D[0][x][y] = std::log(1 + output->matrix3D[0][x][y]);
            output->matrix3D[1][x][y] = std::log(1 + output->matrix3D[1][x][y]);
            output->matrix3D[2][x][y] = std::log(1 + output->matrix3D[2][x][y]);
        }
    }
    output->scaling(LidaImage::full_range);
    return output;
}

LidaImage *FourierTransform::ILPF(LidaImage *input, float D0)
{
    LidaImage* output;
    FourierTransform* freq = new FourierTransform(input);
    LidaImage* ILPF = new LidaImage(freq->row, freq->col);
    float center_x = (ILPF->row) / 2.0;
    float center_y = (ILPF->col) / 2.0;
    float D;
    for (int x = 0; x < ILPF->row; x++) {
        for (int y = 0; y < ILPF->col; y++) {
            D = std::sqrt(std::pow(x-center_x,2) + std::pow(y-center_y,2));
            if(D <= D0){
                for (int channel = 0; channel < 3; channel++) {
                    ILPF->matrix3D[channel][x][y] = 1;
                }
            }
        }
    }
    for (int x = 0; x < freq->row; x++) {
        for (int y = 0; y < freq->col; y++) {
            for (int channel = 0; channel < 3; channel++) {
                freq->frequency[channel][x][y] = {(freq->frequency[channel][x][y].real() * ILPF->matrix3D[channel][x][y]), (freq->frequency[channel][x][y].imag() * ILPF->matrix3D[channel][x][y])};
            }
        }
    }
    output = freq->ifft();
    delete freq;
    delete ILPF;
    return output;
}

LidaImage *FourierTransform::BLPF(LidaImage *input, float n, float D0)
{
    LidaImage* output;
    FourierTransform* freq = new FourierTransform(input);
    LidaImage* BLPF = new LidaImage(freq->row, freq->col);
    float center_x = (BLPF->row) / 2.0;
    float center_y = (BLPF->col) / 2.0;
    float D;
    for (int x = 0; x < BLPF->row; x++) {
        for (int y = 0; y < BLPF->col; y++) {
            D = std::sqrt(std::pow(x-center_x,2) + std::pow(y-center_y,2));
            for (int channel = 0; channel < 3; channel++) {
                BLPF->matrix3D[channel][x][y] = 1/(1 + std::pow(D/D0, 2*n));
            }
        }
    }
    for (int x = 0; x < freq->row; x++) {
        for (int y = 0; y < freq->col; y++) {
            for (int channel = 0; channel < 3; channel++) {
                freq->frequency[channel][x][y] = {(freq->frequency[channel][x][y].real() * BLPF->matrix3D[channel][x][y]), (freq->frequency[channel][x][y].imag() * BLPF->matrix3D[channel][x][y])};
            }
        }
    }
    output = freq->ifft();
    delete freq;
    delete BLPF;
    return output;
}

LidaImage *FourierTransform::GLPF(LidaImage *input, float D0)
{
    LidaImage* output;
    FourierTransform* freq = new FourierTransform(input);
    LidaImage* GLPF = new LidaImage(freq->row, freq->col);
    float center_x = (GLPF->row) / 2.0;
    float center_y = (GLPF->col) / 2.0;
    float D;
    for (int x = 0; x < GLPF->row; x++) {
        for (int y = 0; y < GLPF->col; y++) {
            D = std::sqrt(std::pow(x-center_x,2)+std::pow(y-center_y,2));
            for (int channel = 0; channel < 3; channel++) {
                GLPF->matrix3D[channel][x][y] = std::exp(-1*(D*D)/(2*D0*D0));
            }
        }
    }
    for (int x = 0; x < GLPF->row; x++) {
        for (int y = 0; y < GLPF->col; y++) {
            for (int channel = 0; channel < 3; channel++) {
                freq->frequency[channel][x][y] = {(freq->frequency[channel][x][y].real() * GLPF->matrix3D[channel][x][y]), (freq->frequency[channel][x][y].imag() * GLPF->matrix3D[channel][x][y])};
            }
        }
    }
    output = freq->ifft();
    delete freq;
    delete GLPF;
    return output;
}

LidaImage *FourierTransform::IHPF(LidaImage *input, float D0)
{
    LidaImage* output;
    FourierTransform* freq = new FourierTransform(input);
    LidaImage* IHPF = new LidaImage(freq->row, freq->col);
    float center_x = (IHPF->row) / 2.0;
    float center_y = (IHPF->col) / 2.0;
    float D;
    for (int x = 0; x < IHPF->row; x++) {
        for (int y = 0; y < IHPF->col; y++) {
            D = std::sqrt(std::pow(x-center_x,2) + std::pow(y-center_y,2));
            if(D <= D0){
                for (int channel = 0; channel < 3; channel++) {
                    IHPF->matrix3D[channel][x][y] = 0;
                }
            }
            else {
                for (int channel = 0; channel < 3; channel++) {
                    IHPF->matrix3D[channel][x][y] = 1;
                }
            }
        }
    }
    for (int x = 0; x < freq->row; x++) {
        for (int y = 0; y < freq->col; y++) {
            for (int channel = 0; channel < 3; channel++) {
                freq->frequency[channel][x][y] = {(freq->frequency[channel][x][y].real() * IHPF->matrix3D[channel][x][y]), (freq->frequency[channel][x][y].imag() * IHPF->matrix3D[channel][x][y])};
            }
        }
    }
    output = freq->ifft();
    delete freq;
    delete IHPF;
    return output;
}

LidaImage *FourierTransform::BHPF(LidaImage *input, float n, float D0)
{
    LidaImage* output;
    FourierTransform* freq = new FourierTransform(input);
    LidaImage* BHPF = new LidaImage(freq->row, freq->col);
    float center_x = (BHPF->row) / 2.0;
    float center_y = (BHPF->col) / 2.0;
    float D;
    for (int x = 0; x < BHPF->row; x++) {
        for (int y = 0; y < BHPF->col; y++) {
            D = std::sqrt(std::pow(x-center_x,2) + std::pow(y-center_y,2));
            for (int channel = 0; channel < 3; channel++) {
                BHPF->matrix3D[channel][x][y] = 1/(1 + std::pow(D0/D, 2*n));
            }
        }
    }
    for (int x = 0; x < freq->row; x++) {
        for (int y = 0; y < freq->col; y++) {
            for (int channel = 0; channel < 3; channel++) {
                freq->frequency[channel][x][y] = {(freq->frequency[channel][x][y].real() * BHPF->matrix3D[channel][x][y]), (freq->frequency[channel][x][y].imag() * BHPF->matrix3D[channel][x][y])};
            }
        }
    }
    output = freq->ifft();
    delete freq;
    delete BHPF;
    return output;
}

LidaImage *FourierTransform::GHPF(LidaImage *input, float D0)
{
    LidaImage* output;
    FourierTransform* freq = new FourierTransform(input);
    LidaImage* GHPF = new LidaImage(freq->row, freq->col);
    float center_x = (GHPF->row) / 2.0;
    float center_y = (GHPF->col) / 2.0;
    float D;
    for (int x = 0; x < GHPF->row; x++) {
        for (int y = 0; y < GHPF->col; y++) {
            D = std::sqrt(std::pow(x-center_x,2)+std::pow(y-center_y,2));
            for (int channel = 0; channel < 3; channel++) {
                GHPF->matrix3D[channel][x][y] = 1 - std::exp(-1*(D*D)/(2*D0*D0));
            }
        }
    }
    for (int x = 0; x < GHPF->row; x++) {
        for (int y = 0; y < GHPF->col; y++) {
            for (int channel = 0; channel < 3; channel++) {
                freq->frequency[channel][x][y] = {(freq->frequency[channel][x][y].real() * GHPF->matrix3D[channel][x][y]), (freq->frequency[channel][x][y].imag() * GHPF->matrix3D[channel][x][y])};
            }
        }
    }
    output = freq->ifft();
    delete freq;
    delete GHPF;
    return output;
}

LidaImage *FourierTransform::laplacianSharpening(LidaImage *input)
{
    LidaImage* output;
    FourierTransform* freq = new FourierTransform(input);
    LidaImage* laplacian = new LidaImage(freq->row, freq->col);
    float center_x = (laplacian->row) / 2.0;
    float center_y = (laplacian->col) / 2.0;
    float D_square;
    const float Pi = 3.1415926;
    for (int x = 0; x < laplacian->row; x++) {
        for (int y = 0; y < laplacian->col; y++) {
            D_square = std::pow(x - center_x, 2) + std::pow(y - center_y, 2);
            for (int channel = 0; channel < 3; channel++) {
                laplacian->matrix3D[channel][x][y] = (-4)*Pi*Pi*D_square;
            }
        }
    }
    for (int x = 0; x < freq->row; x++) {
        for (int y = 0; y < freq->col; y++) {
            for (int channel = 0; channel < 3; channel++) {
                freq->frequency[channel][x][y] = {(freq->frequency[channel][x][y].real() * laplacian->matrix3D[channel][x][y]), (freq->frequency[channel][x][y].imag() * laplacian->matrix3D[channel][x][y])};
            }
        }
    }
    output = freq->ifft();
    delete freq;
    delete laplacian;

    float c = -1;
    float r_max = 0;
    float g_max = 0;
    float b_max = 0;
    for (int x = 0; x < output->row; x++) {
        for (int y = 0; y < output->col; y++) {
            if(r_max < std::abs(output->matrix3D[0][x][y])){
                r_max = std::abs(output->matrix3D[0][x][y]);
            }
            if(g_max < std::abs(output->matrix3D[1][x][y])){
                g_max = std::abs(output->matrix3D[1][x][y]);
            }
            if(b_max < std::abs(output->matrix3D[2][x][y])){
                b_max = std::abs(output->matrix3D[2][x][y]);
            }
        }
    }
    for (int x = 0; x < output->row; x++) {
        for (int y = 0; y < output->col; y++) {
            output->matrix3D[0][x][y] = c*(output->matrix3D[0][x][y])/r_max + (input->matrix3D[0][x][y])/255;
            output->matrix3D[1][x][y] = c*(output->matrix3D[1][x][y])/g_max + (input->matrix3D[1][x][y])/255;
            output->matrix3D[2][x][y] = c*(output->matrix3D[2][x][y])/b_max + (input->matrix3D[2][x][y])/255;

            output->matrix3D[0][x][y] = 255 * output->matrix3D[0][x][y];
            output->matrix3D[1][x][y] = 255 * output->matrix3D[1][x][y];
            output->matrix3D[2][x][y] = 255 * output->matrix3D[2][x][y];
        }
    }
    return output;
}

LidaImage *FourierTransform::high_frequency_emphasis(LidaImage* input, float k1, float k2, float D0)
{
    LidaImage* output;
    FourierTransform* freq = new FourierTransform(input);
    LidaImage* GHPF = new LidaImage(freq->row, freq->col);
    float center_x = (GHPF->row) / 2.0;
    float center_y = (GHPF->col) / 2.0;
    float D;
    for (int x = 0; x < GHPF->row; x++) {
        for (int y = 0; y < GHPF->col; y++) {
            D = std::sqrt(std::pow(x-center_x,2)+std::pow(y-center_y,2));
            for (int channel = 0; channel < 3; channel++) {
                GHPF->matrix3D[channel][x][y] = 1 - std::exp(-1*(D*D)/(2*D0*D0));
            }
        }
    }
    for (int x = 0; x < freq->row; x++) {
        for (int y = 0; y < freq->col; y++) {
            for (int channel = 0; channel < 3; channel++) {
                freq->frequency[channel][x][y] = {(freq->frequency[channel][x][y].real() * (k1 + k2*(GHPF->matrix3D[channel][x][y]))), (freq->frequency[channel][x][y].imag() * (k1 + k2*(GHPF->matrix3D[channel][x][y])))};
            }
        }
    }
    output = freq->ifft();
    delete freq;
    delete GHPF;
    return output;
}

LidaImage *FourierTransform::homomorphic(LidaImage* input, float gamma_H, float gamma_L, float c, float D0)
{
    LidaImage* ln = new LidaImage(input->row, input->col);
    for (int x = 0; x < ln->row; x++) {
        for (int y = 0; y < ln->col; y++) {
            for (int channel = 0; channel < 3; channel++) {
                ln->matrix3D[channel][x][y] = std::log(1 + input->matrix3D[channel][x][y]);
            }
        }
    }
    FourierTransform* freq = new FourierTransform(ln);
    float center_x = (freq->row)/2.0;
    float center_y = (freq->col)/2.0;
    float D;
    for (int x = 0; x < freq->row; x++) {
        for (int y = 0; y < freq->col; y++) {
            D = std::sqrt(std::pow(x - center_x, 2) + std::pow(y - center_y, 2));
            for (int channel = 0; channel < 3; channel++) {
                freq->frequency[channel][x][y] = {(freq->frequency[channel][x][y].real()) * ((gamma_H - gamma_L)*(1 - std::exp(-1*c*D*D/D0/D0)) + gamma_L), (freq->frequency[channel][x][y].imag()) * ((gamma_H - gamma_L)*(1 - std::exp(-1*c*D*D/D0/D0)) + gamma_L)};
            }
        }
    }

    LidaImage* output = freq->ifft();
    for (int x = 0; x < ln->row; x++) {
        for (int y = 0; y < ln->col; y++) {
            for (int channel = 0; channel < 3; channel++) {
                output->matrix3D[channel][x][y] = std::exp(output->matrix3D[channel][x][y]) - 1;
            }
        }
    }
    delete ln;
    delete freq;
    return output;
}

LidaImage *FourierTransform::selective_filtering(LidaImage *input, FourierTransform::Mode mode)
{
    LidaImage* output;
    FourierTransform* freq = new FourierTransform(input);
    FrequencyDomain* domain = new FrequencyDomain();
    domain->setWindowTitle("Frequency domain");
    domain->set(freq->row, freq->col, freq->frequency, mode);
    domain->exec();

    output = freq->ifft();
    output->scaling(LidaImage::cutoff);

    delete  freq;
    delete  domain;
    return output;
}

LidaImage *FourierTransform::motion_blur(LidaImage *input, float a, float b, float T)
{
    LidaImage* output;
    FourierTransform* freq = new FourierTransform(input);
    int u;
    int v;
    float center_x = (freq->row)/2.0;
    float center_y = (freq->col)/2.0;
    const float Pi = 3.1415926;

    for (int x = 0; x < freq->row; x++) {
        for (int y = 0; y < freq->col; y++) {
            u = x - center_x;
            v = y - center_y;
//            u = x;
//            v = y;
            Complex H;
            float pi_ua_ub = Pi*(u*a + v*b);
            if(pi_ua_ub == 0){
                H = Complex(1,0);
            }
            else if (pi_ua_ub == int(pi_ua_ub)) {
                H = Complex(T,0) * std::exp(Complex(0, -1*(pi_ua_ub)));
            }
            else {
                H = Complex(T * (std::sin(pi_ua_ub)) / pi_ua_ub, 0) * std::exp(Complex(0, -1*(pi_ua_ub)));
            }
            for (int channel = 0; channel < 3; channel++) {
                freq->frequency[channel][x][y] *= H;
            }
            cout << u << " " << v << " " << pi_ua_ub << H << endl;
        }
    }
    output = freq->ifft();
    delete  freq;
    return output;
}

LidaImage *FourierTransform::wiener_filter(float angle, float length, float T, float SNR)
{
    float a = length*(std::sin((-3.14/180) * angle));
    float b = length*(std::cos((-3.14/180) * angle));
    float K = 1/SNR;
    LidaImage* output;
    int u;
    int v;
    float center_x = (this->row)/2.0;
    float center_y = (this->col)/2.0;
    const float Pi = 3.1415926;

    for (int x = 0; x < this->row; x++) {
        for (int y = 0; y < this->col; y++) {
            u = x - center_x;
            v = y - center_y;

            Complex H;
//            H = Complex(std::exp(-0.0025*(std::pow(u*u+v*v,5.0/6))),0);
            float pi_ua_ub = Pi*(u*a + v*b);
            if(pi_ua_ub == 0){
                H = Complex(1,0);
            }
            else if (pi_ua_ub == int(pi_ua_ub)) {
                H = Complex(T,0) * std::exp(Complex(0, -1*(pi_ua_ub)));
            }
            else {
                H = Complex(T * (std::sin(pi_ua_ub)) / pi_ua_ub, 0) * std::exp(Complex(0, -1*(pi_ua_ub)));
            }
            for (int channel = 0; channel < 3; channel++) {
                this->frequency[channel][x][y] *= ((Complex(1,0)/H) * (std::norm(H)) / (std::norm(H) + Complex(K,0)));
            }
        }
    }
    output = this->ifft();
    return output;
}

LidaImage *FourierTransform::constraint_least_square_filter(LidaImage *input, float gamma)
{
    float a = 0.03;
    float b = 0.03;
    float T = 1;
    LidaImage* output;
    LidaImage* p = new LidaImage(input->row, input->col);
    for (int channel = 0; channel < 3; channel++) {
        p->matrix3D[channel][0][0] = 0;
        p->matrix3D[channel][0][1] = -1;
        p->matrix3D[channel][0][2] = 0;
        p->matrix3D[channel][1][0] = -1;
        p->matrix3D[channel][1][1] = 4;
        p->matrix3D[channel][1][2] = -1;
        p->matrix3D[channel][2][0] = 0;
        p->matrix3D[channel][2][1] = -1;
        p->matrix3D[channel][2][2] = 0;
    }
    FourierTransform* P = new FourierTransform(p);
//    for (int x = 0; x < P->row; x++) {
//        for (int y = 0; y < P->col; y++) {
//            for (int channel = 0; channel < 3; channel++) {
//                Complex c(pow(-1, (x+y)),0);
//                P->frequency[channel][x][y] *= c;
//            }
//        }
//    }
    int noise_lt_x = 70;
    int noise_lt_y = 200;
    int noise_rb_x = 80;
    int noise_rb_y = 250;
    int MN = (noise_rb_x - noise_lt_x)*(noise_rb_y - noise_lt_y);
    double mean_noise = 0;
    double variance_noise = 0;
    for (int x = noise_lt_x; x < noise_rb_x; x++) {
        for (int y = noise_lt_y; y < noise_rb_y; y++) {
            mean_noise += (input->matrix3D[0][x][y] + input->matrix3D[1][x][y] + input->matrix3D[2][x][y])/3;
        }
    }
    mean_noise = mean_noise/MN;
    for (int x = noise_lt_x; x < noise_rb_x; x++) {
        for (int y = noise_lt_y; y < noise_rb_y; y++) {
            variance_noise += std::pow((input->matrix3D[0][x][y] + input->matrix3D[1][x][y] + input->matrix3D[2][x][y])/3 - mean_noise, 2);
        }
    }
    variance_noise = variance_noise/MN;

//    mean_noise = 0;
//    variance_noise = 0.00001;

    double r_norm;
    double eta_norm = (mean_noise*mean_noise + variance_noise)*MN;
//    cout << mean_noise << " " << variance_noise << " " << MN << endl;
    float accuracy = 1e+9;
    float correction_factor = 0.01;
//    float correction_factor = 0.000001;

    do{
        r_norm = 0;

        FourierTransform* freq = new FourierTransform(input);
        int u;
        int v;
        float center_x = (freq->row)/2.0;
        float center_y = (freq->col)/2.0;
        const float Pi = 3.1415926;

        for (int x = 0; x < freq->row; x++) {
            for (int y = 0; y < freq->col; y++) {
                u = x - center_x;
                v = y - center_y;

                Complex H;
//                H = Complex(std::exp(-0.0025*(std::pow(u*u+v*v,5.0/6))),0);
                float pi_ua_ub = Pi*(u*a + v*b);
                if(pi_ua_ub == 0){
                    H = Complex(1,0);
                }
                else if (pi_ua_ub == int(pi_ua_ub)) {
                    H = Complex(T,0) * std::exp(Complex(0, -1*(pi_ua_ub)));
                }
                else {
                    H = Complex(T * (std::sin(pi_ua_ub)) / pi_ua_ub, 0) * std::exp(Complex(0, -1*(pi_ua_ub)));
                }
                for (int channel = 0; channel < 3; channel++) {
//                    freq->frequency[channel][x][y] *= (std::conj(H)) / (std::norm(H) + Complex(gamma,0)*(std::norm(P->frequency[channel][x][y])));
                    freq->frequency[channel][x][y] = freq->frequency[channel][x][y] - ((std::conj(H)) / (std::norm(H) + Complex(gamma,0)*(std::norm(P->frequency[channel][x][y]))) * freq->frequency[channel][x][y] * H);
                }
            }
        }
        output = freq->ifft();

        for (int x = 0; x < output->row; x++) {
            for (int y = 0; y < output->col; y++) {
//                double difference = (output->matrix3D[0][x][y] + output->matrix3D[1][x][y] + output->matrix3D[2][x][y])/3 - (input->matrix3D[0][x][y] + input->matrix3D[1][x][y] + input->matrix3D[2][x][y])/3;
//                r_norm += difference*difference;
                double value = (output->matrix3D[0][x][y] + output->matrix3D[1][x][y] + output->matrix3D[2][x][y])/3;
                r_norm += (value * value);
            }
        }
        if(r_norm < (eta_norm - accuracy)){
            gamma = gamma + correction_factor;
        }
        else if (r_norm > (eta_norm + accuracy)) {
            gamma = gamma - correction_factor;
        }
        delete output;
        delete freq;

        cout << gamma << " " << r_norm << " " << eta_norm  << " " << std::abs(r_norm - eta_norm) << endl;
    }
    while(std::abs(r_norm - eta_norm) > accuracy);
//    while((r_norm < (eta_norm - accuracy)) || (r_norm > (eta_norm + accuracy)));

    FourierTransform* freq = new FourierTransform(input);
//    output = freq->get_spectrum();
    int u;
    int v;
    float center_x = (freq->row)/2.0;
    float center_y = (freq->col)/2.0;
    const float Pi = 3.1415926;

//    cout << freq->frequency[0][100][900] << " " << (std::conj(H)) / (std::norm(H) + Complex(gamma,0)*(std::norm(P->frequency[0][100][900])));

    for (int x = 0; x < freq->row; x++) {
        for (int y = 0; y < freq->col; y++) {
            u = x - center_x;
            v = y - center_y;

            Complex H;
//            H = Complex(std::exp(-0.0025*(std::pow(u*u+v*v,5.0/6))),0);
            float pi_ua_ub = Pi*(u*a + v*b);
            if(pi_ua_ub == 0){
                H = Complex(1,0);
            }
            else if (pi_ua_ub == int(pi_ua_ub)) {
                H = Complex(T,0) * std::exp(Complex(0, -1*(pi_ua_ub)));
            }
            else {
                H = Complex(T * (std::sin(pi_ua_ub)) / pi_ua_ub, 0) * std::exp(Complex(0, -1*(pi_ua_ub)));
            }
//            if((x == 100) && (y == 900)){
//                cout << freq->frequency[0][x][y] << " " << (std::conj(H)) / (std::norm(H) + Complex(gamma,0)*(std::norm(P->frequency[0][x][y]))) << (std::norm(P->frequency[0][x][y])) << endl;
//            }

            for (int channel = 0; channel < 3; channel++) {
                freq->frequency[channel][x][y] *= (std::conj(H)) / (std::norm(H) + Complex(gamma,0)*(std::norm(P->frequency[channel][x][y])));
//                freq->frequency[channel][x][y] *= (std::conj(H)) / (std::norm(H) + Complex(gamma,0)*(Complex(-4*Pi*Pi*(u*u+v*v),0)));
            }
        }
    }

//    output = P->get_spectrum();
//    output = freq->get_spectrum();
    output = freq->ifft();

    delete p;
    delete P;
    delete freq;
    return output;
}
