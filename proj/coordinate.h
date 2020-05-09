/*!
 * @file
 * @brief Tento soubor obsahuje třídu \ref coordinate
 *
 * @author Boris Burkalo (xburka00), Jan Klusáček (xklusa14)
 */
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
    /**
     * @brief souřadnice X
     */
    double x;
    /**
     * @brief souřadnice Y
     */
    double y;
};

#endif // COORDINATES_H
