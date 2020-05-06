#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "vehicle.h"

#include <QGraphicsEllipseItem>



class ellipse : public QGraphicsEllipseItem
{
public:
    void setVehicle(vehicle *ellVeh);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    vehicle* ellipseVehicle;

};

#endif // ELLIPSE_H
