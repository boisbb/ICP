#include "vehicle.h"
#include <cmath>

#include <QDebug>

#include "busline.h"
#include "coordinate.h"
#include "stop.h"
#include "street.h"

vehicle::vehicle()
{

}

vehicle::vehicle(coordinate vehicleCoords, int vehicleNumber)
{
    coords = new coordinate(vehicleCoords.getX(), vehicleCoords.getY());
    number = vehicleNumber;
}

coordinate* vehicle::getCoords()
{
    return coords;
}

busLine* vehicle::getLine()
{
    return line;
}

int vehicle::getNumber()
{
    return number;
}

QVector<stop> vehicle::getStopVec()
{
    return stopVec;
}

QVector<double> vehicle::getStopRatio()
{

}

int vehicle::getJourneyPos()
{

}

QVector<coordinate> vehicle::getFullJourney()
{

}

bool vehicle::getWayBack()
{
    return wayBack;
}

void vehicle::setCoords(coordinate newCoord)
{
    if(coords){
        coords->setX(newCoord.getX());
        coords->setY(newCoord.getX());
    }
    else{
        coords = new coordinate(newCoord.getX(), newCoord.getY());
    }
}

void vehicle::setLine(busLine bus)
{
    if(line){
        *line = bus;
    }
    else{
        line = new busLine();
        *line = bus;
    }
}

void vehicle::move()
{

}

void vehicle::getJourney()
{
    double a = 0.0;
    double b = 0.0;
    double c = 0.0;
    double a_pow = 0.0;
    double b_pow = 0.0;
    double c_pow = 0.0;
    double ratio = 0.0;
    stop *swpStop = NULL;
    stop current;
    coordinate *swpEnd = NULL;
    int i = -1;

    for(int j = 0; j < line->getRoute().size(); j++){
        stopVec.append(line->getRoute().at(j));
        current = line->getRoute().at(j);
        if((swpStop == NULL || swpEnd == NULL) || (swpStop->getStreet()->getStart().getX() != current.getStreet()->getStart().getX()
                                               ||  swpStop->getStreet()->getStart().getY() != current.getStreet()->getStart().getY()
                                               ||  swpStop->getStreet()->getEnd().getX() != current.getStreet()->getEnd().getX()
                                               ||  swpStop->getStreet()->getEnd().getX() != current.getStreet()->getEnd().getX())){
            if(journey.size() == 0){
                journey.append(coordinate(current.getStreet()->getStart().getX(), current.getStreet()->getStart().getY()));
            }
            else{
                i--;
            }
            do{
                ++i;

                a = abs(journey.at(i).getY() - line->getRoute().at(j).getStreet()->getEnd().getY());
                b = abs(journey.at(i).getX() - line->getRoute().at(j).getStreet()->getEnd().getY());

                b_pow = pow(b, 2);
                a_pow = pow(a, 2);
                c_pow = a_pow + b_pow;

                c = sqrt(c_pow);
                ratio = 1 / c;

                if(journey.at(i).getX() > line->getRoute().at(j).getStreet()->getEnd().getX()){
                    if(journey.at(i).getY() > line->getRoute().at(j).getStreet()->getEnd().getY()){
                        journey.append(coordinate(journey.at(i).getX() - ratio * b, journey.at(i).getY() - ratio * a));
                    }
                    else if(journey.at(i).getY() < line->getRoute().at(j).getStreet()->getEnd().getY()){
                        journey.append(coordinate(journey.at(i).getX() - ratio * b, journey.at(i).getY() + ratio * a));
                    }
                    else if(journey.at(i).getY() == line->getRoute().at(j).getStreet()->getEnd().getY()){
                        journey.append(coordinate(journey.at(i).getX() - ratio * b, journey.at(i).getY()));
                    }
                }
                else if(journey.at(i).getX() < line->getRoute().at(j).getStreet()->getEnd().getX()){
                    if(journey.at(i).getY() > line->getRoute().at(j).getStreet()->getEnd().getY()){
                        journey.append(coordinate(journey.at(i).getX() + ratio * b, journey.at(i).getY() - ratio * a));
                    }
                    else if(journey.at(i).getY() < line->getRoute().at(j).getStreet()->getEnd().getY()){
                        journey.append(coordinate(journey.at(i).getX() + ratio * b, journey.at(i).getY() + ratio * a));
                    }
                    else if(journey.at(i).getY() == line->getRoute().at(j).getStreet()->getEnd().getY()){
                        journey.append(coordinate(journey.at(i).getX() + ratio * b, journey.at(i).getY()));
                    }
                }
                else if(journey.at(i).getX() == line->getRoute().at(j).getStreet()->getEnd().getX()){
                    if(journey.at(i).getY() > line->getRoute().at(j).getStreet()->getEnd().getY()){
                        journey.append(coordinate(journey.at(i).getX(), journey.at(i).getY() - ratio * a));
                    }
                    else if(journey.at(i).getY() < line->getRoute().at(j).getStreet()->getEnd().getY()){
                        journey.append(coordinate(journey.at(i).getX(), journey.at(i).getY() + ratio * a));
                    }
                }


                if(coords->getX() == round(journey.at(i).getX()) && coords->getY() == round(journey.at(i).getY())){
                    journeyPos = i;
                    stopNum = j;
                }

            }while(round(journey.at(i).getY()) != line->getRoute().at(j).getStreet()->getEnd().getY() || round(journey.at(i).getX()) != line->getRoute().at(j).getStreet()->getEnd().getX());
            journey.append(coordinate(line->getRoute().at(j).getStreet()->getEnd().getX(), line->getRoute().at(j).getStreet()->getEnd().getY()));
            i++;
            *swpStop = line->getRoute().at(j);
        }
    }
    for (QVector<coordinate>::const_iterator i = journey.begin(); i != journey.end(); ++i)
        qDebug() << i->getX() << " " << i->getY() << ' ';
}
