#include "line.h"
#include "street.h"
#include <QDebug>
#include <QPen>


void line::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug() << lineStreet->getName();
    QPen pen;
    if(!chosen)
        pen.setColor(QColor(255,0,0));
    else
        pen.setColor(QColor(0,0,0));

    chosen = !chosen;
    pen.setWidth(2);
    setPen(pen);
    //lineStreet-
}

void line::setLineStreet(street *value)
{
    lineStreet = value;
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
