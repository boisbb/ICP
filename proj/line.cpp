#include "line.h"
#include "street.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QPen>


void line::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug() << lineStreet->getName();

    chosen = !chosen;
    event->ignore();
    //lineStreet-
}

void line::setLineStreet(street *value)
{
    lineStreet = value;
}

void line::Choose()
{
    QPen pen;
    if(chosen)
        pen.setColor(QColor(255,0,0));
    else
        pen.setColor(QColor(0,0,0));

    pen.setWidth(2);
    this->setPen(pen);
}

void line::unChoose()
{
    chosen = false;
    QPen pen;
    if(!lineStreet->getDelayed())
        pen.setColor(QColor(0,0,0));
    else
        pen.setColor(QColor(150,20,0));
    pen.setWidth(2);
    setPen(pen);
}

bool line::getChosen()
{
    return chosen;
}
