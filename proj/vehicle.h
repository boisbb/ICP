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
    /* */
    /* setters */
    void setCoords(coordinate newCoord);
    void setLine(busLine bus);
    void setGraphics();
    void speedUp();
    void slowDown();
    void setClicked(bool switchClicked);
    /* */
    void move();
    void getJourney();

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
    bool wayBack;
    QVector<QGraphicsItem*> vehicleGraphics;
    double speed;
    bool clicked = false;





};

#endif // VEHICLE_H
