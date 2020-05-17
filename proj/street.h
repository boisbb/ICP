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
    bool getClosedDown();
    QVector<stop *> getStop();
    /**/
    void setDelay(int delay);
    int getDelay();
    bool getDelayed();
    void setGraphics();
    void setDelayed(bool del);
    void setClosedDown(bool newCls);
    void addStop(stop *newStop);
    void setStart(coordinate newStart);
    void setEnd(coordinate newEnd);
    void reverseStops();

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
    /**
     * @brief vektor zastávek na ulici
     */
    QVector<stop*> stops;
    /**
     * @brief značí, zda je ulice zpomalená
     */
    bool delayed = false;
    /**
     * @brief značí zpomalení ulice
     */
    int delayMsec = 0;
    /**
     * @brief značí, zda je ulice zavřená
     */
    bool closedDown = false;


};

#endif // STREET_H
