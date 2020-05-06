#include "ellipse.h"
#include <QDebug>


void ellipse::setVehicle(vehicle *ellVeh)
{
    ellipseVehicle = ellVeh;
}

void ellipse::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "clicked";
    if(ellipseVehicle){
        qDebug() << ellipseVehicle->getNumber();
    }
}
