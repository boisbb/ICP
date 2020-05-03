#include "stop.h"
#include "coordinate.h"
#include "street.h"


stop::stop()
{

}

stop::stop(QString stopName, coordinate stopPosition, QString stopStreetName)
{
    name = stopName;
    *position = stopPosition;
    streetName = stopStreetName;
}

void stop::setStreet(street s)
{
    *Street = s;
}

QString stop::getStreetName() const
{
    return Street->getName();
}

QString stop::getStopName() const
{
    return name;
}

street* stop::getStreet() const
{
    return Street;
}

coordinate* stop::getCoord() const
{
    return position;
}
