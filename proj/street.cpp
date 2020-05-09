/*!
 * @file
 * @brief Tento soubor obsahuje implementaci třídy street
 *
 * @author Boris Burkalo (xburka00), Jan Klusáček (xklusa14)
 */
#include "street.h"
#include "stop.h"
#include "coordinate.h"

#include <QGraphicsLineItem>
#include <QDebug>

/**
 * @brief konstruktor
 */
street::street()
{

}

/**
 * @brief konstruktor s parametry
 * @param streetStart začátek ulice
 * @param streetEnd konec ulice
 * @param streetName název ulice
 */
street::street(coordinate streetStart, coordinate streetEnd, QString streetName)
{
    start = new coordinate();
    *start = streetStart;
    end = new coordinate();
    *end = streetEnd;
    name = streetName;
}

/*
void street::addStop(stop Stop)
{

}
*/

/**
 * @brief funkce sloužící pro získání názvu ulice
 * @return název ulice
 */
QString street::getName()
{
    return name;
}

/**
 * @brief funkce sloužící pro získání začátku ulice
 * @return začátek ulice
 */
coordinate street::getStart()
{
    return *start;
}

/**
 * @brief funkce sloužící pro získání konce ulice
 * @return konec ulice
 */
coordinate street::getEnd()
{
    return *end;
}

/**
 * @brief funkce sloužící pro získání vzhledu (grafiky) ulice
 * @return QVector obsahjící QGrapihcsItemy
 */
QVector<QGraphicsItem*> street::getGraphics()
{
    return streetGraphics;
}

/**
 * @brief funkce sloužící pro nastvení vzhledu (grafiky) zastávky
 */
void street::setGraphics()
{
    streetGraphics.append(new QGraphicsLineItem(this->getStart().getX(), this->getStart().getY(), this->getEnd().getX(), this->getEnd().getY()));
    qDebug() << this->getStart().getX() << " StartX";
}
