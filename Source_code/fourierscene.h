#ifndef FOURIERSCENE_H
#define FOURIERSCENE_H

#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>
#include <lidaimage.h>
#include <QtMath>
#include <math.h>

#include <complex>
#include <valarray>

typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;

class FourierScene : public QGraphicsScene
{
public:
    FourierScene();
    ~FourierScene();

    int mode;

    QImage* image;
    Complex*** frequency;
    QGraphicsPixmapItem* pixmap_item;

    QPoint rectVertex1;
    QPoint rectVertex2;

private:
    QGraphicsRectItem *rect;
    QGraphicsEllipseItem *ellipse;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent*);

    void mouseMoveEvent(QGraphicsSceneMouseEvent*);

    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);
};

#endif // FOURIERSCENE_H
