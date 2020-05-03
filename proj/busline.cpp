#include "busline.h"
#include "stop.h"

busLine::busLine()
{

}

busLine::busLine(int lineId, QVector<QString> lineStopNames)
{
    id = lineId;
    stopNames = lineStopNames;
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

QVector<stop> busLine::getRoute()
{
    return lineRoute;
}
