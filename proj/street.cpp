#include "street.h"
#include "stop.h"
#include "coordinate.h"
#include "line.h"

#include <QGraphicsLineItem>
#include <QDebug>
#include <QPen>

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

void street::setDelay(int delay)
{
    delayMsec = delay;
}

int street::getDelay()
{
    return delayMsec;
}

bool street::getDelayed()
{
    return delayed;
}

void street::setGraphics()
{
    line* graphicsLine = new line();
    graphicsLine->setLineStreet(this);
    QPen pen;
    pen.setWidth(2);
    graphicsLine->setPen(pen);
    graphicsLine->setLine(this->getStart().getX(), this->getStart().getY(), this->getEnd().getX(), this->getEnd().getY());
    streetGraphics.append(graphicsLine);
}

void street::setDelayed(bool del)
{
    delayed = del;
}
