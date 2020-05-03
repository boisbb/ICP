#ifndef BUSLINE_H
#define BUSLINE_H


#include <QColor>
#include <QVector>

class stop;

class busLine
{
public:
    busLine();
    busLine(int lineId, QVector<QString> lineStopNames);
    /* getters */
    int getId();
    QVector<QString> getStopNames();
    QColor getLineColor();
    /* */
    void addStop(stop busStop);
    QVector<stop> getRoute();

private:
    int id;
    QVector<QString> stopNames;
    QVector<stop> lineRoute;
    QColor lineColor;



};

#endif // BUSLINE_H
