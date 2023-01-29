#ifndef LIDAIMAGE_H
#define LIDAIMAGE_H

#include <iostream>
#include <math.h>

using namespace std;

class LidaImage
{
public:
    LidaImage(int row = 0, int col = 0);
    ~LidaImage();
    enum Calibration{
        cutoff,
        full_range,
    };

    int row;
    int col;
    float*** matrix3D;

    void scaling(LidaImage::Calibration calibration = LidaImage::cutoff);

private:

};

#endif // LIDAIMAGE_H
