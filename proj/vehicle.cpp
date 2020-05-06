#include "vehicle.h"
#include <cmath>

#include <QBrush>
#include <QDebug>

#include "busline.h"
#include "coordinate.h"
#include "stop.h"
#include "street.h"
#include "ellipse.h"

vehicle::vehicle()
{

}

vehicle::vehicle(coordinate vehicleCoords, int vehicleNumber)
{
    coords = new coordinate(vehicleCoords.getX(), vehicleCoords.getY());
    number = vehicleNumber;
    color.setRgb(rand() % 256, rand() % 256, rand() % 256);
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

QVector<QGraphicsItem *> vehicle::getGraphics() const
{
    return vehicleGraphics;
}

QColor vehicle::getColor()
{
    return color;
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

void vehicle::setGraphics()
{
    ellipse *ellipseVeh = new ellipse();
    ellipseVeh->setRect(this->getCoords()->getX() - 6, this->getCoords()->getY() - 6, 12, 12);
    ellipseVeh->setVehicle(this);
    vehicleGraphics.append(ellipseVeh);
    dynamic_cast<QGraphicsEllipseItem*>(vehicleGraphics.at(0))->setBrush(QBrush(color, Qt::SolidPattern));
    /* NASTAVENÍ FLAGU */
}

void vehicle::speedUp()
{
    speed /= 1.2;
    //WqDebug() << "Speed up: " << speed;
}

void vehicle::slowDown()
{
    speed *= 1.2;
}



void vehicle::move()
{
    //qDebug() << speed;
    if(!stopBool || QTime::currentTime() >= stopTime.addMSecs(speed)){
        stop nextStop = stopVec.at(stopNum);

        /*qDebug() << " X CURRENT: " << coords->getX() << " Y CURRENT: " << coords->getY() << journeyPos;
        qDebug() << " X STOP: " << nextStop.getCoord()->getX() << " Y STOP: " << nextStop.getCoord()->getY();
        qDebug() << journey.size() << stopVec.size();*/

        QGraphicsEllipseItem *newVehicleGraphics = dynamic_cast<QGraphicsEllipseItem*>(vehicleGraphics.at(0));
        newVehicleGraphics->setRect(journey.at(journeyPos).getX() - 6, journey.at(journeyPos).getY() - 6, 12, 12);
        *coords = journey[journeyPos];



        journeyPos++;
        stopBool = false;


        if(nextStop.getCoord()->getX() == coords->getX() && nextStop.getCoord()->getY() == coords->getY()){
            stopBool = true;
            stopTime = QTime::currentTime();
            stopNum++;
            if(line->getRoute().size() == stopNum){
                if(wayBack)
                    wayBack = false;
                else
                    wayBack = true;

                stopNum = 1;
                std::reverse(journey.begin(), journey.end());
                std::reverse(stopVec.begin(), stopVec.end());
                journeyPos = 0;
            }
        }
    }
    //
}

void vehicle::getJourney()
{
    stopNum = 1;
    speed = 1000;
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
    /* ZERO BY DEFAULT HAS TO BE CHANGED */
    int stopStreetNum = 0;

    for(int j = 0; j < line->getRoute().size(); j++){
        stopVec.append(line->getRoute().at(j));
        current = line->getRoute().at(j);
        if((swpStop == NULL || swpEnd == NULL) || (swpStop->getStreet(stopStreetNum)->getStart().getX() != current.getStreet(stopStreetNum)->getStart().getX()
                                               ||  swpStop->getStreet(stopStreetNum)->getStart().getY() != current.getStreet(stopStreetNum)->getStart().getY()
                                               ||  swpStop->getStreet(stopStreetNum)->getEnd().getX() != current.getStreet(stopStreetNum)->getEnd().getX()
                                               ||  swpStop->getStreet(stopStreetNum)->getEnd().getX() != current.getStreet(stopStreetNum)->getEnd().getX())){
            if(journey.size() == 0){
                journey.append(coordinate(current.getStreet(stopStreetNum)->getStart().getX(), current.getStreet(stopStreetNum)->getStart().getY()));
            }
            else{
                i--;
            }
            do{
                ++i;

                a = abs(journey.at(i).getY() - line->getRoute().at(j).getStreet(stopStreetNum)->getEnd().getY());
                b = abs(journey.at(i).getX() - line->getRoute().at(j).getStreet(stopStreetNum)->getEnd().getX());

                b_pow = pow(b, 2);
                a_pow = pow(a, 2);
                c_pow = a_pow + b_pow;

                c = sqrt(c_pow);
                ratio = 0.5 / c;

                if(journey.at(i).getX() > line->getRoute().at(j).getStreet(stopStreetNum)->getEnd().getX()){
                    if(journey.at(i).getY() > line->getRoute().at(j).getStreet(stopStreetNum)->getEnd().getY()){
                        journey.append(coordinate(journey.at(i).getX() - ratio * b, journey.at(i).getY() - ratio * a));
                    }
                    else if(journey.at(i).getY() < line->getRoute().at(j).getStreet(stopStreetNum)->getEnd().getY()){
                        journey.append(coordinate(journey.at(i).getX() - ratio * b, journey.at(i).getY() + ratio * a));
                    }
                    else if(journey.at(i).getY() == line->getRoute().at(j).getStreet(stopStreetNum)->getEnd().getY()){
                        journey.append(coordinate(journey.at(i).getX() - ratio * b, journey.at(i).getY()));
                    }
                }
                else if(journey.at(i).getX() < line->getRoute().at(j).getStreet(stopStreetNum)->getEnd().getX()){
                    if(journey.at(i).getY() > line->getRoute().at(j).getStreet(stopStreetNum)->getEnd().getY()){
                        journey.append(coordinate(journey.at(i).getX() + ratio * b, journey.at(i).getY() - ratio * a));
                    }
                    else if(journey.at(i).getY() < line->getRoute().at(j).getStreet(stopStreetNum)->getEnd().getY()){
                        journey.append(coordinate(journey.at(i).getX() + ratio * b, journey.at(i).getY() + ratio * a));
                    }
                    else if(journey.at(i).getY() == line->getRoute().at(j).getStreet(stopStreetNum)->getEnd().getY()){
                        journey.append(coordinate(journey.at(i).getX() + ratio * b, journey.at(i).getY()));
                    }
                }
                else if(journey.at(i).getX() == line->getRoute().at(j).getStreet(stopStreetNum)->getEnd().getX()){
                    if(journey.at(i).getY() > line->getRoute().at(j).getStreet(stopStreetNum)->getEnd().getY()){
                        journey.append(coordinate(journey.at(i).getX(), journey.at(i).getY() - ratio * a));
                    }
                    else if(journey.at(i).getY() < line->getRoute().at(j).getStreet(stopStreetNum)->getEnd().getY()){
                        journey.append(coordinate(journey.at(i).getX(), journey.at(i).getY() + ratio * a));
                    }
                }


                if((coords->getX() == round(journey.at(i).getX()) && coords->getY() == round(journey.at(i).getY()))
                        && (coords->getX() >= journey.at(i).getX() && coords->getY() >= journey.at(i).getY()) ){
                    journeyPos = i;
                    stopNum = j;
                }

                /*qDebug() << "X: " << journey.at(i).getX() << " Y: " << journey.at(i).getY();
                qDebug() << "X: " << line->getRoute().at(j).getStreet(stopStreetNum)->getEnd().getX() << " Y: " << line->getRoute().at(j).getStreet(stopStreetNum)->getEnd().getY();
                qDebug() << "X: " << journey.at(i).getX() << " Y: " << journey.at(i).getY();*/

            }while(round(journey.at(i).getY()) != line->getRoute().at(j).getStreet(stopStreetNum)->getEnd().getY() || round(journey.at(i).getX()) != line->getRoute().at(j).getStreet(stopStreetNum)->getEnd().getX());
            journey.append(coordinate(line->getRoute().at(j).getStreet(stopStreetNum)->getEnd().getX(), line->getRoute().at(j).getStreet(stopStreetNum)->getEnd().getY()));
            i++;
            swpStop = new stop();
            *swpStop = line->getRoute().at(j);
        }
    }

    int k = 0;
    int idx = 0;
    for(int j = 0; j < line->getRoute().size(); j++){
        k = 0;
        for (coordinate journeyCoord : journey){
            if(round(line->getRoute().at(j).getCoord()->getX()) == round(journeyCoord.getX())
            && round(line->getRoute().at(j).getCoord()->getY()) == round(journeyCoord.getY())){
                //qDebug() << line->getRoute()[j].getCoord()->getX() << line->getRoute()[j].getCoord()->getY();
                journey[k].setX(line->getRoute().at(j).getCoord()->getX());
                journey[k].setY(line->getRoute().at(j).getCoord()->getY());
                idx = k;

                if(j == line->getRoute().size() - 1){
                    for(int l = journey.size() - 1; l > idx; l--){
                        journey.remove(l);
                    }
                }
                break;
            }
            k++;
        }
    }

    //qDebug() << "SIZE IS: " << journey.size() << " TIME IS in minutes: " << ((500.0 / 1000.0)/60) * (double)journey.size();
    //qDebug() << stopVec.size();
    //exit(0);


    //for (QVector<coordinate>::const_iterator i = journey.begin(); i != journey.end(); ++i)
        //qDebug() << i->getX() << " " << i->getY() << ' ';
}
