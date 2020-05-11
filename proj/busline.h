/*!
 * @file
 * @brief Tento soubor obsahuje třídu \ref busLine
 *
 * @author Boris Burkalo (xburka00), Jan Klusáček (xklusa14)
 */
#ifndef BUSLINE_H
#define BUSLINE_H


#include <QColor>
#include <QTime>
#include <QVector>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class stop;

class busLine
{
public:
    busLine();
    busLine(int lineId);
    /* getters */
    int getId();
    QVector<QString> getStopNames();
    QColor getLineColor();
    QVector<stop*> getRoute();
    QVector<QVector<QTime*>> getStopTime(int index);
    QColor getColor();
    /* */
    void generateStopTimes(QJsonArray timetableArray);
    void addStop(stop *busStop);
    void setColor(QColor color);
    QTime getDuration(double journeySize);
    void deleteStops();
private:

    class timetableClass {
      public:
        /**
         * @brief zastávka
         */
        stop *busStop;
        /**
         * @brief obsahuje časy odjedzu
         */
        QVector<QVector<QTime*>> departureTime;
    };

    /**
     * @brief obsahuje id linky
     */
    int id;
    /**
     * @brief obsahuje názvy zastávek
     */
    QVector<QString> stopNames;
    /**
     * @brief obsahuje zastávky linky
     */
    QVector<stop*> lineRoute;
    /**
     * @brief barva linky
     */
    QColor lineColor;
    /**
     * @brief obsahuje časy odjezdů pro každou zastávku
     */
    QVector<timetableClass*> stopTimes;



};

#endif // BUSLINE_H
