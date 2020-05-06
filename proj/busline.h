#ifndef BUSLINE_H
#define BUSLINE_H


#include <QColor>
#include <QTime>
#include <QVector>

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
    QVector<stop> getRoute();
    QVector<QVector<QTime*>> getStopTime(int index);
    /* */
    void generateStopTimes();
    void addStop(stop busStop);
    void setColor(QColor color);


private:

    class timetableClass {
      public:
        stop *busStop;
        QVector<QVector<QTime*>> departureTime;
    };


    int id;
    QVector<QString> stopNames;
    QVector<stop> lineRoute;
    QColor lineColor;
    QVector<timetableClass*> stopTimes;



};

#endif // BUSLINE_H
