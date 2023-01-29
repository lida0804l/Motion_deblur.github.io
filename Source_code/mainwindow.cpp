#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(QString("Motion deblur"));
    image = new QImage();
    scene = new LidaScene();
    pixmap_item = new QGraphicsPixmapItem();

    ui->lineEdit_angleStart->setText(QString::number(-90));
    ui->lineEdit_angleEnd->setText(QString::number(90));
    ui->lineEdit_angle->setText(QString::number(0));
    ui->horizontalScrollBar_angle->setMinimum(ui->lineEdit_angleStart->text().toFloat());
    ui->horizontalScrollBar_angle->setMaximum(ui->lineEdit_angleEnd->text().toFloat());

    ui->lineEdit_lengthStart->setText(QString::number(0.01));
    ui->lineEdit_lengthEnd->setText(QString::number(0.5));
    ui->horizontalScrollBar_length->setMinimum(ui->lineEdit_lengthStart->text().toFloat()*10000);
    ui->horizontalScrollBar_length->setMaximum(ui->lineEdit_lengthEnd->text().toFloat()*10000);

    ui->lineEdit_exposureTimeStart->setText(QString::number(1));
    ui->lineEdit_exposureTimeEnd->setText(QString::number(5));
    ui->horizontalScrollBar_exposureTime->setMinimum(ui->lineEdit_exposureTimeStart->text().toFloat()*10000);
    ui->horizontalScrollBar_exposureTime->setMaximum(ui->lineEdit_exposureTimeEnd->text().toFloat()*10000);

    ui->lineEdit_SNRStart->setText(QString::number(100));
    ui->lineEdit_SNREnd->setText(QString::number(1000));
    ui->horizontalScrollBar_SNR->setMinimum(ui->lineEdit_SNRStart->text().toFloat());
    ui->horizontalScrollBar_SNR->setMaximum(ui->lineEdit_SNREnd->text().toFloat());

    QObject::connect(scene, &LidaScene::sendAngle, this, &MainWindow::setAngle);
    QObject::connect(scene, &LidaScene::sendLength, this, &MainWindow::setLength);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(NULL, "Load Image", 0, "Image Files(*.jpg *.bmp *.png *tif)");

    if(!fileName.isNull()){
        if(!image->isNull()){
            scene->rectVertex1 = QPoint(0,0);
            scene->rectVertex2 = QPoint(0,0);
            delete image;
            delete ROI;
            delete this->input;
            image = new QImage();
        }
        image->load(fileName);
        *image = image->convertToFormat(QImage::Format_RGB888);

        this->input = MainWindow::QImage2LidaImage(image);
        ROI = new LidaImage(input->row, input->col);
        for (int x = 0; x < input->row; x++) {
            for (int y = 0; y < input->col; y++) {
                ROI->matrix3D[0][x][y] = input->matrix3D[0][x][y];
                ROI->matrix3D[1][x][y] = input->matrix3D[1][x][y];
                ROI->matrix3D[2][x][y] = input->matrix3D[2][x][y];
            }
        }
        scene->input = this->input;
        scene->ROI = this->ROI;
        MainWindow::showImage(image);
    }

}

void MainWindow::showImage(QImage *imageDisplay)
{
    pixmap_item->setPixmap(QPixmap::fromImage(*imageDisplay));

    QList<QGraphicsItem *> itemList = scene->items();
    if(itemList.contains(pixmap_item))
    {
        scene->removeItem(pixmap_item);
    }
    scene->pixmap_item = pixmap_item;
    scene->addItem(pixmap_item);
    scene->setSceneRect(pixmap_item->boundingRect());
    ui->graphicsView->setScene(scene);
}

LidaImage *MainWindow::QImage2LidaImage(QImage *input)
{
    LidaImage* output = new LidaImage(input->height(), input->width());
    for (int x = 0; x < input->height(); x++) {
        for (int y = 0; y < input->width(); y++) {
            int r = input->pixelColor(y,x).red();
            int g = input->pixelColor(y,x).green();
            int b = input->pixelColor(y,x).blue();
            output->matrix3D[0][x][y] = r;
            output->matrix3D[1][x][y] = g;
            output->matrix3D[2][x][y] = b;
        }
    }
    return output;
}

QImage *MainWindow::LidaImage2QImage(LidaImage *input)
{
    QImage* output = new QImage(input->col, input->row, QImage::Format_RGB888);
    for (int x = 0; x < output->height(); x++) {
        for (int y = 0; y < output->width(); y++) {
            int r = input->matrix3D[0][x][y];
            int g = input->matrix3D[1][x][y];
            int b = input->matrix3D[2][x][y];
            output->setPixel(y,x,qRgb(r,g,b));
        }
    }
    return output;
}

void MainWindow::setAngle(float angle)
{
    ui->lineEdit_angle->setText(QString::number(angle));
}

void MainWindow::setLength(float length)
{
    ui->lineEdit_length->setText(QString::number(length));
}

void MainWindow::on_actiontest_triggered()
{
    LidaImage* psf = new LidaImage(input->row, input->col);
    float center_x = (psf->row)/2.0;
    float center_y = (psf->col)/2.0;
    float D;
    float D0 = 53;
    int count = 0;
    for (int x = 0; x < psf->row; x++) {
        for (int y = 0; y < psf->col; y++) {
            D = std::sqrt(std::pow(x-center_x,2) + std::pow(y-center_y,2));
            if(D <= D0){
                count++;
                for (int channel = 0; channel < 3; channel++) {
                    psf->matrix3D[channel][x][y] = 1;
                }
            }
        }
    }
    for (int x = 0; x < psf->row; x++) {
        for (int y = 0; y < psf->col; y++) {
            D = std::sqrt(std::pow(x-center_x,2) + std::pow(y-center_y,2));
            if(D <= D0){
                count++;
                for (int channel = 0; channel < 3; channel++) {
                    psf->matrix3D[channel][x][y] = psf->matrix3D[channel][x][y]/count;
                }
            }
        }
    }
    FourierTransform* freq = new FourierTransform(input);
    FourierTransform* PSF = new FourierTransform(psf);

    for (int x = 0; x < freq->row; x++) {
        for (int y = 0; y < freq->col; y++) {
            for (int channel = 0; channel < 3; channel++) {
                freq->frequency[channel][x][y] *= ((Complex(1,0)/PSF->frequency[channel][x][y]) * (std::norm(PSF->frequency[channel][x][y])) / (std::norm(PSF->frequency[channel][x][y]) + Complex(1/5200.0,0)));
            }
        }
    }
    LidaImage *output = freq->ifft();
    QImage* result = LidaImage2QImage(output);
    scene->input = output;
    MainWindow::showImage(result);
}

void MainWindow::on_actiontest2_triggered()
{

}

void MainWindow::on_actionROI_triggered()
{
    scene->ROI_trigger = true;
    scene->Parameter_trigger = false;
}

void MainWindow::on_actionset_up_from_graph_triggered()
{
    scene->ROI_trigger = false;
    scene->Parameter_trigger = true;
}

void MainWindow::on_pushButton_apply_clicked()
{
    if(image->isNull()){
        return;
    }
    this->ROI = scene->ROI;
    FourierTransform* freq = new FourierTransform(ROI);
    float angle = ui->lineEdit_angle->text().toFloat();
    float length = ui->lineEdit_length->text().toFloat();
    float T = ui->lineEdit_exposureTime->text().toFloat();
    float SNR = ui->lineEdit_SNR->text().toFloat();
    LidaImage* output = freq->wiener_filter(angle, length, T, SNR);
    output->scaling(LidaImage::cutoff);
    int x_min = scene->rectVertex1.y();
    int y_min = scene->rectVertex1.x();
    int x_max = scene->rectVertex2.y();
    int y_max = scene->rectVertex2.x();
    int tmp;
    if(x_min > x_max)
    {tmp = x_min; x_min = x_max; x_max = tmp;}
    if(y_min > y_max)
    {tmp = y_min; y_min = y_max; y_max = tmp;}
    for (int x = 0; x < output->row; x++) {
        for (int y = 0; y < output->col; y++) {
            int r = output->matrix3D[0][x][y];
            int g = output->matrix3D[1][x][y];
            int b = output->matrix3D[2][x][y];
            image->setPixel(y+y_min,x+x_min,qRgb(r,g,b));
        }
    }
    delete freq;
    delete output;
    MainWindow::showImage(image);
}

void MainWindow::on_horizontalScrollBar_angle_valueChanged(int value)
{
    ui->lineEdit_angle->setText(QString::number(value));
    if(image->isNull()){
        return;
    }
    this->ROI = scene->ROI;
    FourierTransform* freq = new FourierTransform(ROI);
    float angle = ui->lineEdit_angle->text().toFloat();
    float length = ui->lineEdit_length->text().toFloat();
    float T = ui->lineEdit_exposureTime->text().toFloat();
    float SNR = ui->lineEdit_SNR->text().toFloat();
    LidaImage* output = freq->wiener_filter(angle, length, T, SNR);
    output->scaling(LidaImage::cutoff);
    int x_min = scene->rectVertex1.y();
    int y_min = scene->rectVertex1.x();
    int x_max = scene->rectVertex2.y();
    int y_max = scene->rectVertex2.x();
    int tmp;
    if(x_min > x_max)
    {tmp = x_min; x_min = x_max; x_max = tmp;}
    if(y_min > y_max)
    {tmp = y_min; y_min = y_max; y_max = tmp;}
    for (int x = 0; x < output->row; x++) {
        for (int y = 0; y < output->col; y++) {
            int r = output->matrix3D[0][x][y];
            int g = output->matrix3D[1][x][y];
            int b = output->matrix3D[2][x][y];
            image->setPixel(y+y_min,x+x_min,qRgb(r,g,b));
        }
    }
    delete freq;
    delete output;
    MainWindow::showImage(image);
}

void MainWindow::on_horizontalScrollBar_length_valueChanged(int value)
{
    ui->lineEdit_length->setText(QString::number(value/10000.0));
    if(image->isNull()){
        return;
    }
    this->ROI = scene->ROI;
    FourierTransform* freq = new FourierTransform(ROI);
    float angle = ui->lineEdit_angle->text().toFloat();
    float length = ui->lineEdit_length->text().toFloat();
    float T = ui->lineEdit_exposureTime->text().toFloat();
    float SNR = ui->lineEdit_SNR->text().toFloat();
    LidaImage* output = freq->wiener_filter(angle, length, T, SNR);
    output->scaling(LidaImage::cutoff);
    int x_min = scene->rectVertex1.y();
    int y_min = scene->rectVertex1.x();
    int x_max = scene->rectVertex2.y();
    int y_max = scene->rectVertex2.x();
    int tmp;
    if(x_min > x_max)
    {tmp = x_min; x_min = x_max; x_max = tmp;}
    if(y_min > y_max)
    {tmp = y_min; y_min = y_max; y_max = tmp;}
    for (int x = 0; x < output->row; x++) {
        for (int y = 0; y < output->col; y++) {
            int r = output->matrix3D[0][x][y];
            int g = output->matrix3D[1][x][y];
            int b = output->matrix3D[2][x][y];
            image->setPixel(y+y_min,x+x_min,qRgb(r,g,b));
        }
    }
    delete freq;
    delete output;
    MainWindow::showImage(image);
}

void MainWindow::on_horizontalScrollBar_exposureTime_valueChanged(int value)
{
    ui->lineEdit_exposureTime->setText(QString::number(value/10000.0));
    if(image->isNull()){
        return;
    }
    this->ROI = scene->ROI;
    FourierTransform* freq = new FourierTransform(ROI);
    float angle = ui->lineEdit_angle->text().toFloat();
    float length = ui->lineEdit_length->text().toFloat();
    float T = ui->lineEdit_exposureTime->text().toFloat();
    float SNR = ui->lineEdit_SNR->text().toFloat();
    LidaImage* output = freq->wiener_filter(angle, length, T, SNR);
    output->scaling(LidaImage::cutoff);
    int x_min = scene->rectVertex1.y();
    int y_min = scene->rectVertex1.x();
    int x_max = scene->rectVertex2.y();
    int y_max = scene->rectVertex2.x();
    int tmp;
    if(x_min > x_max)
    {tmp = x_min; x_min = x_max; x_max = tmp;}
    if(y_min > y_max)
    {tmp = y_min; y_min = y_max; y_max = tmp;}
    for (int x = 0; x < output->row; x++) {
        for (int y = 0; y < output->col; y++) {
            int r = output->matrix3D[0][x][y];
            int g = output->matrix3D[1][x][y];
            int b = output->matrix3D[2][x][y];
            image->setPixel(y+y_min,x+x_min,qRgb(r,g,b));
        }
    }
    delete freq;
    delete output;
    MainWindow::showImage(image);
}

void MainWindow::on_horizontalScrollBar_SNR_valueChanged(int value)
{
    ui->lineEdit_SNR->setText(QString::number(value));
    if(image->isNull()){
        return;
    }
    this->ROI = scene->ROI;
    FourierTransform* freq = new FourierTransform(ROI);
    float angle = ui->lineEdit_angle->text().toFloat();
    float length = ui->lineEdit_length->text().toFloat();
    float T = ui->lineEdit_exposureTime->text().toFloat();
    float SNR = ui->lineEdit_SNR->text().toFloat();
    LidaImage* output = freq->wiener_filter(angle, length, T, SNR);
    output->scaling(LidaImage::cutoff);
    int x_min = scene->rectVertex1.y();
    int y_min = scene->rectVertex1.x();
    int x_max = scene->rectVertex2.y();
    int y_max = scene->rectVertex2.x();
    int tmp;
    if(x_min > x_max)
    {tmp = x_min; x_min = x_max; x_max = tmp;}
    if(y_min > y_max)
    {tmp = y_min; y_min = y_max; y_max = tmp;}
    for (int x = 0; x < output->row; x++) {
        for (int y = 0; y < output->col; y++) {
            int r = output->matrix3D[0][x][y];
            int g = output->matrix3D[1][x][y];
            int b = output->matrix3D[2][x][y];
            image->setPixel(y+y_min,x+x_min,qRgb(r,g,b));
        }
    }
    delete freq;
    delete output;
    MainWindow::showImage(image);
}

void MainWindow::on_lineEdit_angleStart_editingFinished()
{
    ui->horizontalScrollBar_angle->setMinimum(ui->lineEdit_angleStart->text().toFloat());
}

void MainWindow::on_lineEdit_angleEnd_editingFinished()
{
    ui->horizontalScrollBar_angle->setMaximum(ui->lineEdit_angleEnd->text().toFloat());
}

void MainWindow::on_lineEdit_lengthStart_editingFinished()
{
    ui->horizontalScrollBar_length->setMinimum(ui->lineEdit_lengthStart->text().toFloat()*10000);
}

void MainWindow::on_lineEdit_lengthEnd_editingFinished()
{
    ui->horizontalScrollBar_length->setMaximum(ui->lineEdit_lengthEnd->text().toFloat()*10000);
}

void MainWindow::on_lineEdit_exposureTimeStart_editingFinished()
{
    ui->horizontalScrollBar_exposureTime->setMinimum(ui->lineEdit_exposureTimeStart->text().toFloat()*10000);
}

void MainWindow::on_lineEdit_exposureTimeEnd_editingFinished()
{
    ui->horizontalScrollBar_exposureTime->setMaximum(ui->lineEdit_exposureTimeEnd->text().toFloat()*10000);
}

void MainWindow::on_lineEdit_SNRStart_editingFinished()
{
    ui->horizontalScrollBar_SNR->setMinimum(ui->lineEdit_SNRStart->text().toFloat());
}

void MainWindow::on_lineEdit_SNREnd_editingFinished()
{
    ui->horizontalScrollBar_SNR->setMaximum(ui->lineEdit_SNREnd->text().toFloat());
}

void MainWindow::on_actionsave_as_triggered()
{
    QString savepath = QFileDialog::getSaveFileName(this, tr("Save File"), NULL, tr("jpg (*.jpg);; bmp (*.bmp);; png (*.png)"));
    image->save(savepath);
}
