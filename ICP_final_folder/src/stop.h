/*!
 * @file
 * @brief Tento soubor obsahuje třídu \ref stop
 *
 * @author Boris Burkalo (xburka00), Jan Klusáček (xklusa14)
 */
#ifndef STOP_H
#define STOP_H

#include <QGraphicsItem>
#include <QString>
#include <QVector>


class street;
class coordinate;

class stop
{
public:
    stop();
    stop(QString stopName, coordinate stopPosition);
    void setStreet(street *s);
    //QString getStreetName() const;
    QString getStopName() const;
    street* getStreet(int i) const;
    coordinate* getCoord() const;
    QVector<street*> getStreets();
    QVector<QGraphicsItem*> getGraphics();
    void setGraphics();


private:
    /**
     * @brief jméno zastávky
     */
    QString name;
    /**
     * @brief pozice zastávky
     */
    coordinate* position;
    /**
     * @brief jméno ulice
     */
    QString streetName;
    /**
     * @brief QVector ulic
     */
    QVector<street*> streets;
    /**
     * @brief vzhled (grafika) zastávky
     */
    QVector<QGraphicsItem*> stopGraphics;
};

#endif // STOP_H
