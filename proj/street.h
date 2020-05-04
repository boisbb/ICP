#ifndef STREET_H
#define STREET_H

#include <QGraphicsItem>
#include <QString>

class stop;
class coordinate;
class street
{
public:
    street();
    street(coordinate streetStart, coordinate streetEnd, QString streetName);
    /* not sure about usage for now */
    //void addStop(stop Stop);
    /* getters */
    QString getName();
    coordinate getStart();
    coordinate getEnd();
    QVector<QGraphicsItem*> getGraphics();
    /**/
    void setGraphics();

private:
    coordinate *start;
    coordinate *end;
    QString name;
    QVector<QGraphicsItem*> streetGraphics;


};

#endif // STREET_H
