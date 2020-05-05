#ifndef BUSLINE_H
#define BUSLINE_H


#include <QColor>
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
    /* */
    void addStop(stop busStop);
    void setColor(QColor color);


private:
    int id;
    QVector<QString> stopNames;
    QVector<stop> lineRoute;
    QColor lineColor;



};

#endif // BUSLINE_H
