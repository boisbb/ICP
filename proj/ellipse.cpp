#include "ellipse.h"
#include <QDebug>


void ellipse::setVehicle(vehicle *ellVeh)
{
    ellipseVehicle = ellVeh;
}

void ellipse::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug() << "clicked";
    static bool clicked = false;

    if(ellipseVehicle){
        //TODO překlikávání když bude víc vozidel
        if(clicked){
            ellipseVehicle->setClicked(false);
            clicked = false;
        }
        else{
            ellipseVehicle->setClicked(true);
            clicked = true;
        }
        //v mainwindow se v moveVeh zjsiití jeslti je trues
        //qDebug() << ellipseVehicle->getNumber();
    }
}
