/*!
 * @file
 * @brief Slouží k obsluze dané linky
 *
 * @author Boris Burkalo (xburka00), Jan Klusáček (xklusa14)
 */
#include "busline.h"
#include "stop.h"
#include "coordinate.h"

#include <QDebug>


/**
 * @brief konstruktor
 * @details který nastaví barvu dané lince
 */
busLine::busLine()
{
    lineColor.setRgb(rand() % 256, rand() % 256, rand() % 256);
}

/**
 * @brief konstruktor,
 * @details nastaví barvu dané lince a id na základně parametru
 * @param lineId číslo dané linky
 */
busLine::busLine(int lineId)
{
    id = lineId;
    lineColor.setRgb(rand() % 256, rand() % 256, rand() % 256);
}

/**
 * @brief TODO funkce sloužící pro zíkání čísla linky
 * @return číslo linky
 */
int busLine::getId()
{
    return id;
}

/**
 * @brief funkce sloužící pro získání názvů zastávek linky
 * @return názvy zastávek linky
 */
QVector<QString> busLine::getStopNames()
{
    return stopNames;
}

/**
 * @brief funkce sloužící pro získání barvy linky
 * @return barva linky
 */
QColor busLine::getLineColor()
{
    return lineColor;
}

/**
 * @brief funkce sloužící k přidání zastávky
 * @param busStop zastávka, kterou chceme přidat
 */
void busLine::addStop(stop busStop)
{
    lineRoute.append(busStop);
}

//TODO smazat??
/*
void busLine::setColor(QColor color)
{
    lineColor = color;
}
*/

/**
 * @brief funkce sloužící pro zjištění časového intervalu trasy jedné linky
 * @param journeySize délka trasy
 * @return čas trvání
 */
QTime busLine::getDuration(double journeySize)
{
    double seconds = ((double)((journeySize + 1 - (double)getRoute().size()) * 500 +
                    ((double) getRoute().size() - 2) * (double)10000) / (double) 1000);
    qDebug() << seconds;
    return QTime(0, seconds / 60, (int)seconds % 60);
}

/**
 * @brief funkce sloužící pro získání trasy linky
 * @return zastávky dané trasy
 */
QVector<stop> busLine::getRoute()
{
    return lineRoute;
}

/**
 * @brief funkce sloužící ke získání jízdního řádu na dané zastávce
 * @param index index zastávky ve vektoru zastávek
 * @return jízdní řád
 */
QVector<QVector<QTime *>> busLine::getStopTime(int index)
{
    return stopTimes[index]->departureTime;
}

/**
 * @brief funkce sloužící pro získání barvy linky
 * @return barvu linky
 */
QColor busLine::getColor()
{
    return lineColor;
}

/**
 * @brief vygeneruje interní jízdní řád na základě vstupních dat
 * @param timetableArray pole jízního řádu extrahované ze souboru .json
 */
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
