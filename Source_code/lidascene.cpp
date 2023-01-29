#include "lidascene.h"

LidaScene::LidaScene()
{
    rect = new QGraphicsRectItem();
    line = new QGraphicsLineItem();
    rectVertex1 = QPoint(0,0);
    rectVertex2 = QPoint(0,0);
    point1 = QPoint(0,0);
    point2 = QPoint(0,0);
    //    pixmap_item = new QGraphicsPixmapItem();
}

LidaScene::~LidaScene()
{
    delete rect;
    delete pixmap_item;
}

void LidaScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    rectVertex1 = mouseEvent->scenePos().toPoint();
    point1 = mouseEvent->scenePos().toPoint();
}

void LidaScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    int mouse_y = mouseEvent->scenePos().toPoint().x();
    int mouse_x = mouseEvent->scenePos().toPoint().y();
//    cout << "x: " << mouse_x << " "
//         << "y: " << mouse_y << " "
//         << "r: " << image->pixelColor(x,y).red() << " "
//         << "g: " << image->pixelColor(x,y).green() << " "
//         << "b: " << image->pixelColor(x,y).blue() << endl;

    if(((mouse_x >= 0) && (mouse_x < this->input->row)) && ((mouse_y >= 0) && (mouse_y < this->input->col))){
        if(mouseEvent->buttons() & Qt::LeftButton){
            if(this->ROI_trigger == true){
                rectVertex2 = mouseEvent->scenePos().toPoint();
                int rectCase = 0;
                if((rectVertex1.x() < rectVertex2.x()) && (rectVertex1.y() < rectVertex2.y()))
                    rectCase = 1;
                else if((rectVertex1.x() > rectVertex2.x()) && (rectVertex1.y() < rectVertex2.y()))
                    rectCase = 2;
                else if((rectVertex1.x() > rectVertex2.x()) && (rectVertex1.y() > rectVertex2.y()))
                    rectCase = 3;
                else
                    rectCase = 4;

                switch (rectCase) {
                case 1:
                    rect->setRect(QRectF(rectVertex1, rectVertex2));
                    break;
                case 2:
                    rect->setRect(QRectF(rectVertex2.x(), rectVertex1.y(), qFabs(rectVertex2.x()-rectVertex1.x()), qFabs(rectVertex2.y()-rectVertex1.y())));
                    break;
                case 3:
                    rect->setRect(QRectF(rectVertex2, rectVertex1));
                    break;
                case 4:
                    rect->setRect(QRectF(rectVertex1.x(), rectVertex2.y(), qFabs(rectVertex2.x()-rectVertex1.x()), qFabs(rectVertex2.y()-rectVertex1.y())));
                    break;
                default:
                    break;
                }
                rect->setPen(QPen(Qt::blue, 5, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin));
                QList<QGraphicsItem *> itemList = this->items();
                if(itemList.contains(rect))
                {
                    this->removeItem(rect);
                }
                this->addItem(rect);
            }
            else if (this->Parameter_trigger == true) {
//                rectVertex2 = mouseEvent->scenePos().toPoint();
                point2 = mouseEvent->scenePos().toPoint();;
//                line->setLine(rectVertex1.x(),rectVertex1.y(),rectVertex2.x(),rectVertex2.y());
                line->setLine(point1.x(),point1.y(),point2.x(),point2.y());
                line->setPen(QPen(Qt::blue, 5, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin));
                QList<QGraphicsItem *> itemList = this->items();
                if(itemList.contains(line))
                {
                    this->removeItem(line);
                }
                this->addItem(line);
            }
        }
    }
}

void LidaScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(this->ROI_trigger == true){
        this->ROI_trigger = false;
        delete this->ROI;
        int x_min = rectVertex1.y();
        int y_min = rectVertex1.x();
        int x_max = rectVertex2.y();
        int y_max = rectVertex2.x();
        int tmp;
        if(x_min > x_max)
        {tmp = x_min; x_min = x_max; x_max = tmp;}
        if(y_min > y_max)
        {tmp = y_min; y_min = y_max; y_max = tmp;}
        ROI = new LidaImage(x_max - x_min + 1, y_max - y_min + 1);
        for (int x = x_min; x <= x_max; x++) {
            for (int y = y_min; y <= y_max; y++) {
                for (int channel = 0; channel < 3; channel++) {
                    ROI->matrix3D[channel][x - x_min][y - y_min] = input->matrix3D[channel][x][y];
                }
            }
        }
//        this->freq = new FourierTransform(ROI);
//        delete ROI;
        QList<QGraphicsItem *> itemList = this->items();
        if(itemList.contains(rect))
        {
            this->removeItem(rect);
        }
    }
    if(this->Parameter_trigger == true){
        this->Parameter_trigger = false;
        int x1 = point1.y();
        int y1 = point1.x();
        int x2 = point2.y();
        int y2 = point2.x();
//        int tmp;
//        if(x_min > x_max)
//        {tmp = x_min; x_min = x_max; x_max = tmp;}
//        if(y_min > y_max)
//        {tmp = y_min; y_min = y_max; y_max = tmp;}
        int dx = x2 - x1;
        int dy = y2 - y1;
        emit(sendAngle(std::atan2(dx,dy) * (-180/3.14)));
        emit(sendLength(std::sqrt(dx*dx + dy*dy)/1000));
        QList<QGraphicsItem *> itemList = this->items();
        if(itemList.contains(line))
        {
            this->removeItem(line);
        }
    }
}
