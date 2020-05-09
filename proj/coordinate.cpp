/*!
 * @file
 * @brief Tento soubor ohsahuje implementaci coordinate
 *
 * @author Boris Burkalo (xburka00), Jan Klusáček (xklusa14)
 */

#include "coordinate.h"

/**
 * @brief konstruktor
 */
coordinate::coordinate()
{

}

/**
 * @brief konstruktor se zadanými souřadnicemi
 * @param xCoord souřadnice X
 * @param yCoord souřadnice Y
 */
coordinate::coordinate(double xCoord, double yCoord)
{
    x = xCoord;
    y = yCoord;
}

/**
 * @brief funkce sloužící pro získání x-ové souřadnice
 * @return double obsahující souřadnnici X
 */
double coordinate::getX() const
{
    return x;
}

/**
 * @brief funkce sloužící pro získání y-ové souřadnice
 * @return double obsahující souřadnici Y
 */
double coordinate::getY() const
{
    return y;
}

/**
 * @brief funkce sloužící k nastavení souřadnice X
 * @param xCoord x-ová souřadnice
 */
void coordinate::setX(double xCoord)
{
    x = xCoord;
}

/**
 * @brief funkce sloužící k nastavení souřadnice Y
 * @param yCoord y-ová souřadnice
 */
void coordinate::setY(double yCoord)
{
    y = yCoord;
}
