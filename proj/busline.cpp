#include "busline.h"
#include "stop.h"
#include "coordinate.h"

#include <QDebug>

busLine::busLine()
{
    lineColor.setRgb(rand() % 256, rand() % 256, rand() % 256);
}

busLine::busLine(int lineId)
{
    id = lineId;
    lineColor.setRgb(rand() % 256, rand() % 256, rand() % 256);
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

/*
void busLine::setColor(QColor color)
{
    lineColor = color;
}
*/

QTime busLine::getDuration(double journeySize)
{
    double seconds = ((double)((journeySize + 1 - (double)getRoute().size()) * 500 +
                    ((double) getRoute().size() - 2) * (double)10000) / (double) 1000);
    qDebug() << seconds;
    return QTime(0, seconds / 60, (int)seconds % 60);
}

QVector<stop> busLine::getRoute()
{
    return lineRoute;
}

QVector<QVector<QTime *>> busLine::getStopTime(int index)
{
    return stopTimes[index]->departureTime;
}

QColor busLine::getColor()
{
    return lineColor;
}

void busLine::generateStopTimes()
{
    for(stop busS : lineRoute){
        stopTimes.append(new timetableClass());
    }

    stopTimes.append(new timetableClass());
    stopTimes[0]->busStop = new stop(lineRoute[0].getStopName(),*lineRoute[0].getCoord());

    for(int i = 0; i < 24; i++){
        QVector<QTime*> times;
        times.append(new QTime(i, 0, 0));
        times.append(new QTime(i, 10, 0));
        times.append(new QTime(i, 20, 0));
        times.append(new QTime(i, 30, 0));
        times.append(new QTime(i, 40, 0));
        times.append(new QTime(i, 50, 0));
        stopTimes[0]->departureTime.append(times);
        qDebug() << stopTimes[0]->departureTime[i][0]->toString() << " BUSTIME";
        qDebug() << stopTimes[0]->departureTime[i][1]->toString();
    }


}
