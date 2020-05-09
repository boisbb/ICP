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
    QVector<stop> getStopVec();
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
    void setLine(busLine bus);
    void setGraphics();
    void setClicked(bool switchClicked);
    void setJourneyPos(int pos, int stop);
    void setWayback(bool wB);
    /* */
    void move(QTime sceneTime);
    void getJourney();
    void reverseVectors();
    double pointDistance(coordinate oldCoord, coordinate newCoord);
    void setStopNum();
private:
    coordinate* coords = NULL;
    int number;
    QColor color;
    busLine* line = NULL;
    int stopNum = 0;
    QVector<bool> traveledStops;
    QVector<coordinate> journey;
    QVector<stop> stopVec;
    int journeyPos = 0;
    bool stopBool = false;
    QTime stopTime;
    QTime preDelay;
    bool wayBack = false;
    QVector<QGraphicsItem*> vehicleGraphics;
    bool clicked = false;
    bool destr = false;
    bool isDelayed = false;





};

#endif // VEHICLE_H
