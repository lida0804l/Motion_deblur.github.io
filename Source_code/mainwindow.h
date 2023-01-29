#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <lidascene.h>
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QtTest/QTest>
//#include "windows.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actiontest_triggered();

    void on_actionROI_triggered();

    void on_actiontest2_triggered();

    void on_actionset_up_from_graph_triggered();

    void on_pushButton_apply_clicked();

    void on_horizontalScrollBar_angle_valueChanged(int value);

    void on_horizontalScrollBar_length_valueChanged(int value);

    void on_horizontalScrollBar_exposureTime_valueChanged(int value);

    void on_horizontalScrollBar_SNR_valueChanged(int value);

    void on_lineEdit_angleStart_editingFinished();

    void on_lineEdit_angleEnd_editingFinished();

    void on_lineEdit_lengthStart_editingFinished();

    void on_lineEdit_lengthEnd_editingFinished();

    void on_lineEdit_exposureTimeStart_editingFinished();

    void on_lineEdit_exposureTimeEnd_editingFinished();

    void on_lineEdit_SNRStart_editingFinished();

    void on_lineEdit_SNREnd_editingFinished();

    void on_actionsave_as_triggered();

private:
    Ui::MainWindow *ui;

    QImage* image;
    LidaImage* input;
    LidaImage* ROI;
//    FourierTransform* freq;
    LidaScene* scene;
    QGraphicsPixmapItem* pixmap_item;

    void showImage(QImage*);
    LidaImage* QImage2LidaImage(QImage* input);
    QImage* LidaImage2QImage(LidaImage* input);

    void setAngle(float angle);
    void setLength(float length);
};

#endif // MAINWINDOW_H
