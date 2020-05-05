#ifndef STOP_H
#define STOP_H

#include <QGraphicsItem>
#include <QString>
#include <QVector>


class street;
class coordinate;

class stop
{
public:
    stop();
    stop(QString stopName, coordinate stopPosition);
    void setStreet(street s);
    //QString getStreetName() const;
    QString getStopName() const;
    street* getStreet(int i) const;
    coordinate* getCoord() const;
    QVector<street*> getStreets();
    QVector<QGraphicsItem*> getGraphics();
    void setGraphics();


private:
    QString name;
    coordinate* position;
    QString streetName;
    QVector<street*> streets;
    QVector<QGraphicsItem*> stopGraphics;
};

#endif // STOP_H
