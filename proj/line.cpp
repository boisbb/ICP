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
        detour = true;
        QPen pen;
        pen.setColor(QColor(255, 255, 0));
        setPen(pen);
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
    qDebug() << "choose" << chosen;
    if(chosen && !lineStreet->getClosedDown())
        pen.setColor(QColor(255,0,0));
    else if(!lineStreet->getClosedDown())
        pen.setColor(QColor(160, 160, 160));
    else if(lineStreet->getClosedDown()){
        pen.setColor(QColor(255, 0, 0));
        pen.setStyle(Qt::DashDotLine);
    }

    pen.setWidth(2);
    this->setPen(pen);
}

void line::unChoose()
{
    chosen = false;

    QPen pen;
    if(!lineStreet->getDelayed() && !lineStreet->getClosedDown())
        pen.setColor(QColor(160, 160, 160));
    else if(lineStreet->getDelayed())
        pen.setColor(QColor(150,20,0));
    else if(lineStreet->getClosedDown()){
        qDebug() << "It is kept closed down";
        pen.setColor(QColor(160, 160, 160));
        pen.setStyle(Qt::DashDotLine);
    }
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
        pen.setColor(QColor(255, 0, 0));
        pen.setStyle(Qt::SolidLine);
    }
    pen.setWidth(2);
    setPen(pen);
}

bool line::getDetour()
{
    return detour;
}
