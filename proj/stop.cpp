/*!
 * @file
 * @brief Slouží k práci se zastávkami
 *
 * @author Boris Burkalo (xburka00), Jan Klusáček (xklusa14)
 */
#include "stop.h"
#include "coordinate.h"
#include "street.h"

#include <QBrush>
#include <QDebug>

/**
 * @brief konstruktor
 */
stop::stop()
{

}

/**
 * @brief konstruktor s parametry
 * @param stopName název zastávky
 * @param stopPosition pozice zastávky
 */
stop::stop(QString stopName, coordinate stopPosition)
{
    name = stopName;
    position = new coordinate();
    *position = stopPosition;
}

/**
 * @brief funkce sloužící k nastavení ulice
 * @param s ulice
 */
void stop::setStreet(street *s)
{
    streets.append(s);
}
//TODO smazat
/*
QString stop::getStreetName() const
{
    return Street->getName();
}
*/

/**
 * @brief funkce sloužící pro získání jména zastávky
 * @return název zastávky
 */
QString stop::getStopName() const
{
    return name;
}

/**
 * @brief funkce sloužící pro získání ulice
 * @param i pozice ve vektoru ulic
 * @return vrací ulici
 */
street *stop::getStreet(int i) const
{
    return streets.at(i);
}


/**
 * @brief funkce sloužící pro získání pozice zastávky
 * @return zastávky
 */
coordinate* stop::getCoord() const
{
    return position;
}

/**
 * @brief funkce pro získání ulic
 * @return ulice
 */
QVector<street *> stop::getStreets()
{
    return streets;
}

/**
 * @brief funkce sloužící pro získání grafiky zastávky
 * @return grafika zastávky
 */
QVector<QGraphicsItem *> stop::getGraphics()
{
    return stopGraphics;
}

/**
 * @brief funkce sloužící pro nastavení vzhledu zastávky
 */
void stop::setGraphics()
{
    stopGraphics.append(new QGraphicsEllipseItem(this->getCoord()->getX() - 5, this->getCoord()->getY() - 5, 10, 10));
    dynamic_cast<QGraphicsEllipseItem*>(stopGraphics.at(0))->setBrush(QBrush(QColor(0, 0, 0), Qt::SolidPattern));
    QGraphicsTextItem *text = new QGraphicsTextItem(name);
    text->setPos(getCoord()->getX(), getCoord()->getY());
    //stopGraphics.append(text);
}

