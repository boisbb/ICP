#include "street.h"
#include "stop.h"
#include "coordinate.h"

street::street()
{

}

street::street(coordinate streetStart, coordinate streetEnd, QString streetName)
{
    start = new coordinate();
    *start = streetStart;
    end = new coordinate();
    *end = streetStart;
    name = streetName;
}

/*
void street::addStop(stop Stop)
{

}
*/
QString street::getName()
{
    return name;
}

coordinate street::getStart()
{
    return *start;
}

coordinate street::getEnd()
{
    return *end;
}
