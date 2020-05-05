#include "busline.h"
#include "stop.h"

busLine::busLine()
{

}

busLine::busLine(int lineId)
{
    id = lineId;
}

int busLine::getId()
{
    return id;
}

QVector<QString> busLine::getStopNames()
{
    return stopNames;
}

QColor busLine::getLineColor()
{
    return lineColor;
}

void busLine::addStop(stop busStop)
{
    lineRoute.append(busStop);
}

void busLine::setColor(QColor color)
{
    lineColor = color;
}

QVector<stop> busLine::getRoute()
{
    return lineRoute;
}
