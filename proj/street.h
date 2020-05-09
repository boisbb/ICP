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
    void setDelay(int delay);
    int getDelay();
    bool getDelayed();
    void setGraphics();
    void setDelayed(bool del);

private:
    coordinate *start;
    coordinate *end;
    QString name;
    QVector<QGraphicsItem*> streetGraphics;
    bool delayed = false;
    int delayMsec = 0;


};

#endif // STREET_H
