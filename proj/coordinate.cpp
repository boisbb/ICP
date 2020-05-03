#include "coordinate.h"

coordinate::coordinate()
{

}

coordinate::coordinate(double xCoord, double yCoord)
{
    x = xCoord;
    y = yCoord;
}

double coordinate::getX() const
{
    return x;
}

double coordinate::getY() const
{
    return y;
}

void coordinate::setX(double xCoord)
{
    x = xCoord;
}

void coordinate::setY(double yCoord)
{
    y = yCoord;
}
