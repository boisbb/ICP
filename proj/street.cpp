#include "street.h"
#include "stop.h"
#include "coordinate.h"

#include <QGraphicsLineItem>
#include <QDebug>

street::street()
{

}

street::street(coordinate streetStart, coordinate streetEnd, QString streetName)
{
    start = new coordinate();
    *start = streetStart;
    end = new coordinate();
    *end = streetEnd;
    name = streetName;
}

/*
void street::addStop(stop Stop)
{

}
*/
QString street::getName()
{
    return name;
}

coordinate street::getStart()
{
    return *start;
}

coordinate street::getEnd()
{
    return *end;
}

QVector<QGraphicsItem*> street::getGraphics()
{
    return streetGraphics;
}

void street::setGraphics()
{
    streetGraphics.append(new QGraphicsLineItem(this->getStart().getX(), this->getStart().getY(), this->getEnd().getX(), this->getEnd().getY()));
    qDebug() << this->getStart().getX() << " StartX";
}
