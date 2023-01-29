#ifndef FREQUENCYDOMAIN_H
#define FREQUENCYDOMAIN_H

#include <iostream>
#include <QDialog>
#include <fourierscene.h>
#include <complex>
#include <valarray>
#include <QGraphicsPixmapItem>
#include <lidaimage.h>

using namespace std;

typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;

namespace Ui {
class FrequencyDomain;
}

class FrequencyDomain : public QDialog
{
    Q_OBJECT

public:
    explicit FrequencyDomain(QWidget *parent = nullptr);
    ~FrequencyDomain();

    Ui::FrequencyDomain *ui;

    LidaImage* lida_spectrum;
    QImage* image;
    FourierScene* scene;
    QGraphicsPixmapItem* pixmap_item;

    void set(int row, int col, Complex*** frequency, int mode);

private:
//    Ui::FrequencyDomain *ui;
};

#endif // FREQUENCYDOMAIN_H
