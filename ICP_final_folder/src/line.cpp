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
        justSetDet = true;
        QPen pen;
        if(detour)
            pen.setColor(QColor(255, 255, 0));
        else
            pen.setColor(QColor(255, 255, 0));
        pen.setWidth(2);
        setPen(pen);
    }
    //lineStreet-
}

bool line::getJustSetDet() const
{
    return justSetDet;
}

void line::setJustSetDet(bool value)
{
    justSetDet = value;
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
    if(detour)
            pen.setColor(QColor(255, 255, 0));
    else if(!lineStreet->getDelayed() && !lineStreet->getClosedDown())
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

void line::unSetDetour()
{
    detour = false;
    QPen pen;
    pen.setColor(QColor(160, 160, 160));

    setPen(pen);

}

bool line::getDetour()
{
    return detour;
}

void line::unClose()
{
    QPen pen;
    closed = !closed;
    if(chosen)
        pen.setColor(QColor(255, 0, 0));
    else
        pen.setColor(QColor(160, 160, 160));
    pen.setWidth(2);
    pen.setStyle(Qt::SolidLine);
    setPen(pen);
}
