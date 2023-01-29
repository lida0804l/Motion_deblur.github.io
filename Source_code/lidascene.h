#ifndef LIDASCENE_H
#define LIDASCENE_H

//#include <QGraphicsScene>
#include <QGraphicsView>
#include <iostream>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsLineItem>
#include <lidaimage.h>
#include <fouriertransform.h>
#include <QObject>
//#include <lida.h>

using namespace std;

class LidaScene : public QGraphicsScene
{
    Q_OBJECT
public:
    LidaScene();
    ~LidaScene();

//    QImage* image;
    LidaImage* input;
    LidaImage* ROI;
//    FourierTransform* freq;

    QGraphicsPixmapItem *pixmap_item;

    QPoint rectVertex1;
    QPoint rectVertex2;
    QPoint point1;
    QPoint point2;

    bool ROI_trigger = false;
    bool Parameter_trigger = false;

signals:
    void sendAngle(float band);
    void sendLength(float length);

private:
    QGraphicsRectItem *rect;
    QGraphicsLineItem *line;
//private:


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent*);

    void mouseMoveEvent(QGraphicsSceneMouseEvent*);

    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);
};

#endif // LIDASCENE_H
