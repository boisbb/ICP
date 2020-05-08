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

void busLine::generateStopTimes(QJsonArray timetableArray)
{
    for(stop busS : lineRoute){
        stopTimes.append(new timetableClass());
    }

    //qDebug() << timetableArray[2].toObject().find("night").value().toArray();

    stopTimes.append(new timetableClass());
    stopTimes[0]->busStop = new stop(lineRoute[0].getStopName(),*lineRoute[0].getCoord());

    QJsonArray morning = timetableArray[0].toObject().find("morning").value().toArray();
    QJsonArray day = timetableArray[1].toObject().find("day").value().toArray();
    QJsonArray night = timetableArray[2].toObject().find("night").value().toArray();
    for(int i = 0; i < 5; i++){
        QVector<QTime*> times;
        for(int j = 0; j < night.size(); j++){
            times.append(new QTime(i, night[j].toInt(), 0));
             //qDebug() << "Added times: " << times[times.size() - 1]->toString();
        }
        stopTimes[0]->departureTime.append(times);
    }
    for(int i = 5; i < 10; i++){
        QVector<QTime*> times;
        for(int j = 0; j < morning.size(); j++){
            times.append(new QTime(i, morning[j].toInt(), 0));
             //qDebug() << "Added times: " << times[times.size() - 1]->toString();
        }
        stopTimes[0]->departureTime.append(times);
    }

    for(int i = 10; i < 18; i++){
        QVector<QTime*> times;
        for(int j = 0; j < day.size(); j++){
            times.append(new QTime(i, day[j].toInt(), 0));
             //qDebug() << "Added times: " << times[times.size() - 1]->toString();
        }
        stopTimes[0]->departureTime.append(times);
    }
    for(int i = 18; i < 24; i++){
        QVector<QTime*> times;
        for(int j = 0; j < night.size(); j++){
            times.append(new QTime(i, night[j].toInt(), 0));
             //qDebug() << "Added times: " << times[times.size() - 1]->toString();
        }
        stopTimes[0]->departureTime.append(times);
    }


}
