#include "line.h"
#include "street.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QPen>


void line::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug() << lineStreet->getName();
    if(event->button() == Qt::LeftButton)
    {
        chosen = !chosen;
        event->ignore();
    }
    else if(event->button() == Qt::RightButton){
        qDebug() << "Road of obstruction";
    }
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

void line::setClosed()
{
    QPen pen;
    if(!closed){
        closed = !closed;
        pen.setColor(QColor(255, 0, 0));
        pen.setStyle(Qt::DashDotLine);
    }
    else{
        closed = !closed;
        pen.setColor(QColor(0, 0, 0));
        pen.setStyle(Qt::SolidLine);
    }
    pen.setWidth(2);
    setPen(pen);
}
