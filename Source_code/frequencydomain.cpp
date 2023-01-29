#include "frequencydomain.h"
#include "ui_frequencydomain.h"

FrequencyDomain::FrequencyDomain(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrequencyDomain)
{
    ui->setupUi(this);

    scene = new FourierScene();
    pixmap_item = new QGraphicsPixmapItem();
}

FrequencyDomain::~FrequencyDomain()
{
//    delete lida_spectrum;
    delete ui;
    delete image;
    delete scene;
//    delete pixmap_item;
    cout << "deleted!!!!!!" << endl;
}

void FrequencyDomain::set(int row, int col, Complex ***frequency, int mode)
{
    scene->mode = mode;
    lida_spectrum = new LidaImage(row, col);
    for (int x = 0; x < row; x++) {
        for (int y = 0; y < col; y++) {
            lida_spectrum->matrix3D[0][x][y] = std::abs(frequency[0][x][y]);
            lida_spectrum->matrix3D[1][x][y] = std::abs(frequency[1][x][y]);
            lida_spectrum->matrix3D[2][x][y] = std::abs(frequency[2][x][y]);

            lida_spectrum->matrix3D[0][x][y] = std::log(1 + lida_spectrum->matrix3D[0][x][y]);
            lida_spectrum->matrix3D[1][x][y] = std::log(1 + lida_spectrum->matrix3D[1][x][y]);
            lida_spectrum->matrix3D[2][x][y] = std::log(1 + lida_spectrum->matrix3D[2][x][y]);
        }
    }
    lida_spectrum->scaling(LidaImage::full_range);

    image = new QImage(col, row, QImage::Format_RGB888);
    for (int x = 0; x < row; x++) {
        for (int y = 0; y < col; y++) {
            int r = lida_spectrum->matrix3D[0][x][y];
            int g = lida_spectrum->matrix3D[1][x][y];
            int b = lida_spectrum->matrix3D[2][x][y];
            image->setPixel(y,x,qRgb(r,g,b));
        }
    }
    delete lida_spectrum;

    pixmap_item->setPixmap(QPixmap::fromImage(*image));
    scene->addItem(pixmap_item);
    scene->setSceneRect(pixmap_item->boundingRect());

    scene->frequency = frequency;
    scene->image = this->image;
    scene->pixmap_item = this->pixmap_item;

    ui->graphicsView->setScene(scene);
}
