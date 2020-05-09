#include "stop.h"
#include "coordinate.h"
#include "street.h"

#include <QBrush>
#include <QDebug>


stop::stop()
{

}

stop::stop(QString stopName, coordinate stopPosition)
{
    name = stopName;
    position = new coordinate();
    *position = stopPosition;
}

void stop::setStreet(street *s)
{
    streets.append(s);
}
/*
QString stop::getStreetName() const
{
    return Street->getName();
}
*/
QString stop::getStopName() const
{
    return name;
}

street *stop::getStreet(int i) const
{
    return streets.at(i);
}



coordinate* stop::getCoord() const
{
    return position;
}

QVector<street *> stop::getStreets()
{
    return streets;
}

QVector<QGraphicsItem *> stop::getGraphics()
{
    return stopGraphics;
}

void stop::setGraphics()
{
    stopGraphics.append(new QGraphicsEllipseItem(this->getCoord()->getX() - 5, this->getCoord()->getY() - 5, 10, 10));
    qDebug() << this->getCoord()->getX() << " "<< this->getCoord()->getY();
    dynamic_cast<QGraphicsEllipseItem*>(stopGraphics.at(0))->setBrush(QBrush(QColor(0, 0, 0), Qt::SolidPattern));
    QGraphicsTextItem *text = new QGraphicsTextItem(name);
    text->setPos(getCoord()->getX(), getCoord()->getY());
    //stopGraphics.append(text);
}

