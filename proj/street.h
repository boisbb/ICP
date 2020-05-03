#ifndef STREET_H
#define STREET_H

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
    /**/

private:
    coordinate *start;
    coordinate *end;
    QString name;


};

#endif // STREET_H
