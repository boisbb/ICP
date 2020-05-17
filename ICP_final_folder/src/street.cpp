/*!
 * @file
 * @brief Slouží k práci s ulicemi
 *
 * @author Boris Burkalo (xburka00), Jan Klusáček (xklusa14)
 */
#include "street.h"
#include "stop.h"
#include "coordinate.h"
#include "line.h"

#include <QGraphicsLineItem>
#include <QDebug>
#include <QPen>

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
 * @brief zjistí, zda je ulice zavřená
 * @return true pokud je zavřená, jinak false
 */

bool street::getClosedDown()
{
    return closedDown;
}

/**
 * @brief getter ulic, které jsou lokalizované na ulici
 * @return seznam zastávek
 */

QVector<stop*> street::getStop()
{
    return stops;
}

/**
 * @brief nastaví zpoždeění dané ulici
 * @param delay zpoždění k nastavění
 */

void street::setDelay(int delay)
{
    delayMsec = delay;
}

/**
 * @brief getter pro zpoždění
 * @return vrátí zpoždění
 */

int street::getDelay()
{
    return delayMsec;
}

/**
 * @brief zjistí, zda je ulice zpožděná
 * @return true pokud je ulice zpožděná, jinak false
 */

bool street::getDelayed()
{
    return delayed;
}

/**
 * @brief funkce sloužící pro nastvení vzhledu (grafiky) zastávky
 */
void street::setGraphics()
{
    line* graphicsLine = new line();
    graphicsLine->setLineStreet(this);
    QPen pen;
    pen.setWidth(2);
    pen.setColor(QColor(160, 160, 160));
    graphicsLine->setPen(pen);
    graphicsLine->setLine(this->getStart().getX(), this->getStart().getY(), this->getEnd().getX(), this->getEnd().getY());
    streetGraphics.append(graphicsLine);
}

/**
 * @brief nastaví ulici jako zpožděnou/nezpožděnou
 * @param del zpožděná/nezpožděná
 */

void street::setDelayed(bool del)
{
    delayed = del;
}

/**
 * @brief nastaví ulici bool zavření
 * @param newCls zpožděná/nezpožděná
 */

void street::setClosedDown(bool newCls)
{
    closedDown = newCls;
}

/**
 * @brief přidá zastávku ulici
 * @param newStop nová zastávka
 */

void street::addStop(stop *newStop)
{
    stops.append(newStop);
}

/**
 * @brief nastaví novou počáteční pozici
 * @param newStart pozice k nastavení
 */

void street::setStart(coordinate newStart)
{
    *start = newStart;
}

/**
 * @brief nastaví novou konečnou pozici ulice
 * @param newEnd pozice k nastavení
 */

void street::setEnd(coordinate newEnd)
{
    *end = newEnd;
}

/**
 * @brief převrátí posloupnost ve vektoru zastávek
 */

void street::reverseStops()
{
    std::reverse(stops.begin(), stops.end());

}


