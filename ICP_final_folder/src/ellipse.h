/*!
 * @file
 * @brief Tento soubor obsahuje třídu \ref ellipse
 *
 * @author Boris Burkalo (xburka00), Jan Klusáček (xklusa14)
 */
#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "busline.h"
#include "stop.h"
#include "vehicle.h"

#include <QGraphicsEllipseItem>



class ellipse : public QGraphicsEllipseItem
{
public:
    void setVehicle(vehicle *ellVeh);
    void setStop(stop eStop, busLine *line);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    /**
     * @brief vozidlo
     */
    vehicle* ellipseVehicle;
    stop ellStop;
    busLine *ellLine;

};

#endif // ELLIPSE_H
