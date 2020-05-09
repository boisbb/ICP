/*!
 * @file
 * @brief Tento soubor obsahuje třídu \ref ellipse
 *
 * @author Boris Burkalo (xburka00), Jan Klusáček (xklusa14)
 */
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
    /**
     * @brief vozidlo
     */
    vehicle* ellipseVehicle;

};

#endif // ELLIPSE_H
