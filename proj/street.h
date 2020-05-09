/*!
 * @file
 * @brief Tento soubor obsahuje třídu \ref street
 *
 * @author Boris Burkalo (xburka00), Jan Klusáček (xklusa14)
 */
#ifndef STREET_H
#define STREET_H

#include <QGraphicsItem>
#include <QString>

class stop;
class coordinate;
class street
{
public:
    street();
    street(coordinate streetStart, coordinate streetEnd, QString streetName);
    /* not sure about usage for now */
    //void addStop(stop Stop);
    /* getters */
    QString getName();
    coordinate getStart();
    coordinate getEnd();
    QVector<QGraphicsItem*> getGraphics();
    /**/
    void setDelay(int delay);
    int getDelay();
    bool getDelayed();
    void setGraphics();
    void setDelayed(bool del);

private:
    /**
     * @brief začátek ulice
     */
    coordinate *start;
    /**
     * @brief konec ulice
     */
    coordinate *end;
    /**
     * @brief název ulice
     */
    QString name;
    /**
     * @brief vzhled (grafika) ulice
     */
    QVector<QGraphicsItem*> streetGraphics;
    bool delayed = false;
    int delayMsec = 0;


};

#endif // STREET_H
