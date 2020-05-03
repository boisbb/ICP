#ifndef COORDINATES_H
#define COORDINATES_H


class coordinate
{
public:
    coordinate();
    coordinate(double xCoord, double yCoord);
    double getX() const;
    double getY() const;
    void setX(double xCoord);
    void setY(double yCoord);


private:
    double x;
    double y;
};

#endif // COORDINATES_H
