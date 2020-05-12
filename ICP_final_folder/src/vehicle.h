/*!
 * @file
 * @brief Tento soubor obsahuje třídu \ref vehicle
 *
 * @author Boris Burkalo (xburka00), Jan Klusáček (xklusa14)
 */
#ifndef VEHICLE_H
#define VEHICLE_H

#include <QColor>
#include <QGraphicsItem>
#include <QTime>
#include <QVector>

class busLine;
class coordinate;
class stop;

class vehicle
{
public:
    vehicle();
    vehicle(coordinate vehicleCoords, int vehicleNumber);
    /* getters */
    coordinate* getCoords();
    busLine* getLine();
    int getNumber();
    QVector<stop*> getStopVec();
    QVector<double> getStopRatio();
    int getJourneyPos();
    QVector<coordinate> getFullJourney();
    bool getWayBack();
    QVector<QGraphicsItem*> getGraphics() const;
    QColor getColor();
    bool getClicked();
    int get_stops_number();
    bool destruct();
    /* */
    /* setters */
    void setCoords(coordinate newCoord);
    void setLine(busLine *bus);
    void setGraphics();
    void setClicked(bool switchClicked);
    void setJourneyPos(int pos);
    void setWayback(bool wB);
    /* */
    void move(QTime sceneTime);
    void getJourney();
    void reverseVectors();
    double pointDistance(coordinate oldCoord, coordinate newCoord);
    void setStopNum();
    void flushStops();
private:
    /**
     * @brief \ref coordinate vozidla
     */
    coordinate* coords = NULL;

    /**
     * @brief číslo linky
     */
    int number;
    /**
     * @brief barva vozidla
     */
    QColor color;
    /**
     * @brief linka na které je vozdilo
     */
    busLine* line = NULL;
    /**
     * @brief pozice následující zastávky ve vektoru zastávek
     */
    int stopNum = 0;

    //TODO smazat
    QVector<bool> traveledStops;
    /**
     * @brief celá cesta vozidla
     */
    QVector<coordinate> journey;
    /**
     * @brief zastávky vozidla
     */
    QVector<stop*> stopVec;
    /**
     * @brief index aktuální pozice vozidla ve vektoru \ref journey
     */
    int journeyPos = 0;
    /**
     * @brief flag jeslti je vozidlo v zastávce nebo ne
     */
    bool stopBool = false;
    /**
     * @brief čas zastavení vozidla v zastávce
     */
    QTime stopTime;
    QTime preDelay;
    /**
     * @brief flag jeslti vozidlo jede zpátky
     */
    bool wayBack = false;
    /**
     * @brief vzhled (grafika) vozdila
     */
    QVector<QGraphicsItem*> vehicleGraphics;
    /**
     * @brief flag vozdila, ukazující, jeslti na vozidlo bylo kliknuto
     */
    bool clicked = false;
    /**
     * @brief flag jeslti se má smazat grafika v hlavním okně v mapě)
     */
    bool destr = false;
    bool isDelayed = false;





};

#endif // VEHICLE_H
