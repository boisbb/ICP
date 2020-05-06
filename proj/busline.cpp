#include "busline.h"
#include "stop.h"
#include "coordinate.h"

#include <QDebug>

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

void busLine::getStopTimes()
{
    for(stop busS : lineRoute){
        stopTimes.append(new timetableClass());
    }

    stopTimes.append(new timetableClass());
    stopTimes[0]->busStop = new stop(lineRoute[0].getStopName(),*lineRoute[0].getCoord());

    for(int i = 0; i < 48; i++){
        stopTimes[0]->departureTime[i].append(new QTime(i, 0, 0));
        qDebug() << stopTimes[0]->departureTime[i][0] << " BUSTIME";
        stopTimes[0]->departureTime[i].append(new QTime(i, 30, 0));
        qDebug() << stopTimes[0]->departureTime[i][1];
    }


}
