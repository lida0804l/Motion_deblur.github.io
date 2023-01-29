#include "fourierscene.h"

FourierScene::FourierScene()
{
    rect = new QGraphicsRectItem();
    ellipse = new QGraphicsEllipseItem();
    rectVertex1 = QPoint(0,0);
    rectVertex2 = QPoint(0,0);
}

FourierScene::~FourierScene()
{
    delete rect;
    delete ellipse;
    delete pixmap_item;
//    delete image;
}

void FourierScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    rectVertex1 = mouseEvent->scenePos().toPoint();
}

void FourierScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    int mouse_y = mouseEvent->scenePos().toPoint().x();
    int mouse_x = mouseEvent->scenePos().toPoint().y();
    if(((mouse_x >= 0) && (mouse_x < this->image->height())) && ((mouse_y >= 0) && (mouse_y < this->image->width()))){
        if(mouseEvent->buttons() & Qt::LeftButton){
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

            if(mode ==0){
                rect->setPen(QPen(Qt::blue, 5, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin));
                QList<QGraphicsItem *> itemList = this->items();
                if(itemList.contains(rect))
                {
                    this->removeItem(rect);
                }
                this->addItem(rect);
            }
            else if (mode == 1) {
                double radius = std::sqrt(std::pow(rect->rect().width(),2) + std::pow(rect->rect().height(),2));
                int x_min = rectVertex1.x() - radius;
                int y_min = rectVertex1.y() - radius;
                ellipse->setRect(x_min, y_min, 2*radius, 2*radius);
                ellipse->setPen(QPen(Qt::blue, 5, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin));
                QList<QGraphicsItem *> itemList = this->items();
                if(itemList.contains(ellipse))
                {
                    this->removeItem(ellipse);
                }
                this->addItem(ellipse);
            }
        }
    }
}

void FourierScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(mode == 0){
        int x_min = rectVertex1.y();
        int y_min = rectVertex1.x();
        int x_max = rectVertex2.y();
        int y_max = rectVertex2.x();
        int tmp;
        if(x_min > x_max)
        {tmp = x_min; x_min = x_max; x_max = tmp;}
        if(y_min > y_max)
        {tmp = y_min; y_min = y_max; y_max = tmp;}
        for (int x = x_min; x <= x_max; x++) {
            for (int y = y_min; y <= y_max; y++) {
                for (int channel = 0; channel < 3; channel++) {
                    this->frequency[channel][x][y] = {0,0};
                }
                this->image->setPixel(y,x,qRgb(0,0,0));
            }
        }

        x_min = x_min - 2*(x_min - float(this->image->height())/2);
        y_min = y_min - 2*(y_min - float(this->image->width()/2));
        x_max = x_max - 2*(x_max - float(this->image->height())/2);
        y_max = y_max - 2*(y_max - float(this->image->width()/2));
        tmp = x_min; x_min = x_max; x_max = tmp;
        tmp = y_min; y_min = y_max; y_max = tmp;
        for (int x = x_min; x <= x_max; x++) {
            for (int y = y_min; y <= y_max; y++) {
                for (int channel = 0; channel < 3; channel++) {
                    this->frequency[channel][x][y] = {0,0};
                }
                this->image->setPixel(y,x,qRgb(0,0,0));
            }
        }
    }
    else if (mode == 1) {
        int n = 2;
        double D0k = std::sqrt(std::pow(rect->rect().width(),2) + std::pow(rect->rect().height(),2));
        int Dk_x = rectVertex1.y();
        int Dk_y = rectVertex1.x();

        int Dk_mirror_x = Dk_x - 2*(Dk_x - float(this->image->height())/2);
        int Dk_mirror_y = Dk_y - 2*(Dk_y - float(this->image->width())/2);

        float Dk;
        float Dk_mirror;

        for (int x = 0; x < this->image->height(); x++) {
            for (int y = 0; y < this->image->width(); y++) {
                Dk = std::sqrt(std::pow(x-Dk_x,2)+std::pow(y-Dk_y,2));
                Dk_mirror = std::sqrt(std::pow(x-Dk_mirror_x,2)+std::pow(y-Dk_mirror_y,2));
                for (int channel = 0; channel < 3; channel++) {
                    this->frequency[channel][x][y] = {(frequency[channel][x][y].real()) * (1/(1 + std::pow(D0k/Dk, 2*n))) * (1/(1 + std::pow(D0k/Dk_mirror, 2*n))),(frequency[channel][x][y].imag()) * (1/(1 + std::pow(D0k/Dk, 2*n))) * (1/(1 + std::pow(D0k/Dk_mirror, 2*n)))};
                }

                int r = (this->image->pixelColor(y,x).red()) * (1/(1 + std::pow(D0k/Dk, 2*n))) * (1/(1 + std::pow(D0k/Dk_mirror, 2*n)));
                int g = (this->image->pixelColor(y,x).green()) * (1/(1 + std::pow(D0k/Dk, 2*n))) * (1/(1 + std::pow(D0k/Dk_mirror, 2*n)));
                int b = (this->image->pixelColor(y,x).blue()) * (1/(1 + std::pow(D0k/Dk, 2*n))) * (1/(1 + std::pow(D0k/Dk_mirror, 2*n)));
                this->image->setPixel(y,x,qRgb(r,g,b));
            }
        }
    }


    QList<QGraphicsItem *> itemList = this->items();
    if(itemList.contains(pixmap_item))
    {
        this->removeItem(pixmap_item);
        pixmap_item->setPixmap(QPixmap::fromImage(*image));
    }
    this->addItem(pixmap_item);
    this->setSceneRect(pixmap_item->boundingRect());
}
