#ifndef STOP_H
#define STOP_H

#include <QString>


class street;
class coordinate;

class stop
{
public:
    stop();
    stop(QString stopName, coordinate stopPosition, QString stopStreetName);
    void setStreet(street s);
    QString getStreetName() const;
    QString getStopName() const;
    street* getStreet() const;
    coordinate* getCoord() const;




private:
    QString name;
    coordinate* position;
    QString streetName;
    street* Street;

};

#endif // STOP_H
