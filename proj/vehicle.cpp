/*!
 * @file
 * @brief Tento soubor obsahuje implementaci třídy vehicle
 *
 * @author Boris Burkalo (xburka00), Jan Klusáček (xklusa14)
 */
#include "vehicle.h"
#include <cmath>

#include <QBrush>
#include <QDebug>

#include "busline.h"
#include "coordinate.h"
#include "stop.h"
#include "street.h"
#include "ellipse.h"
#include "line.h"

/**
 * @brief konstruktor
 */
vehicle::vehicle()
{

}

/**
 * @brief konstruktor s parametry
 * @param vehicleCoords \ref coordinate vozidla
 * @param vehicleNumber číslo linky
 */
vehicle::vehicle(coordinate vehicleCoords, int vehicleNumber)
{
    coords = new coordinate(vehicleCoords.getX(), vehicleCoords.getY());
    number = vehicleNumber;
}

/**
 * @brief funkce sloužící pro získání \ref coordinate vozidla
 * @return souřadnice vozidla
 */
coordinate* vehicle::getCoords()
{
    return coords;
}

/**
 * @brief funkce sloužící pro získání linky na které vozdilo jede
 * @return linka
 */
busLine* vehicle::getLine()
{
    return line;
}

/**
 * @brief funkce sloužící pro získání číslo linky daného vozidla
 * @return číslo linky
 */
int vehicle::getNumber()
{
    return number;
}

/**
 * @brief funkce sloužící pro získání vektoru zastávek pro dané vozidlo
 * @return zastávky
 */
QVector<stop> vehicle::getStopVec()
{
    return stopVec;
}

/**
 * @brief funkce sloužící pro získání poměru zastávek
 * @return poměr zastávek s ohledem na trasu
 */
QVector<double> vehicle::getStopRatio()
{
    QVector<double> retVec;
    for(int j = 0; j < getLine()->getRoute().size(); j++){
        for(int i = 0; i < journey.size(); i++){
            if(getLine()->getRoute()[j].getCoord()->getX() == journey[i].getX()
            && getLine()->getRoute()[j].getCoord()->getY() == journey[i].getY()){
                retVec.append((double) i / journey.size());
                break;
            }
        }
    }

    if(!wayBack){
        retVec[0] = 0.0;
        retVec[retVec.size() - 1] = 1.0;
    }
    else if(!wayBack){
        retVec[0] = 1.0;
        retVec[retVec.size() - 1] = 0.0;
    }


    return retVec;
}

/**
 * @brief funkce sloužící pro získání poozice vozidla ve vektoru trasy
 * @return pozice vozidla
 */
int vehicle::getJourneyPos()
{
    return journeyPos;
}

/**
 * @brief funkce sloužící pro získání celé cesty
 * @return vektor celé cesty
 */
QVector<coordinate> vehicle::getFullJourney()
{
    return journey;
}

/**
 * @brief funkce sloužící pro zjistění, jeslti jede vozidlo zpátky
 * @return true/false
 */
bool vehicle::getWayBack()
{
    return wayBack;
}

/**
 * @brief funkce sloužící pro získání vzhledu (grafiky) vozidla
 * @return QVector QGraphicsItemů
 */
QVector<QGraphicsItem *> vehicle::getGraphics() const
{
    return vehicleGraphics;
}

/**
 * @brief funkce sloužící pro získání barvy vozidla
 * @return barva vozidla
 */
QColor vehicle::getColor()
{
    return color;
}

/**
 * @brief funkce sloužící pro zjištění, jestli se na dané vozidlo kliklo
 * @return true/false
 */
bool vehicle::getClicked()
{
    return clicked;
}

/**
 * @brief funkce sloužící ke zjištění počtu zastávek dané linky
 * @return počet zastávek
 */
int vehicle::get_stops_number()
{
    return stopVec.size();
}

/**
 * @brief funkce pro zjištění, jesltli má být nad vozidlem zavolán destruktor
 * @return true/false
 */
bool vehicle::destruct()
{
    return destr;
}

/**
 * @brief funkce sloužící pro nastavení pozice vozidla
 * @param pozice kam ho chceme nastavit
 */
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

/**
 * @brief funkce sloužící pro nastavení linky danému vozidlu
 * @param bus autobus, který chceme nastavit
 */
void vehicle::setLine(busLine bus)
{
    if(line){
        *line = bus;
        color = line->getColor();
    }
    else{
        line = new busLine();
        *line = bus;
        color = line->getColor();
    }
}

/**
 * @brief funkce sloužící pro nastavení vzhledu (grafiky) vozidla
 */
void vehicle::setGraphics()
{
    ellipse *ellipseVeh = new ellipse();
    ellipseVeh->setRect(this->getCoords()->getX() - 7, this->getCoords()->getY() - 7, 14, 14);
    ellipseVeh->setVehicle(this);
    vehicleGraphics.append(ellipseVeh);
    dynamic_cast<QGraphicsEllipseItem*>(vehicleGraphics.at(0))->setBrush(QBrush(color, Qt::SolidPattern));
    /* NASTAVENÍ FLAGU */
}


/**
 * @brief funkce sloužící pro nastavení flagu kliknutí na vozidlo
 * @param switchClicked true/false
 */
void vehicle::setClicked(bool switchClicked)
{
    clicked = switchClicked;
}

/**
 * @brief nastaví pozici vozidla ve vektoru cesty
 * @param pos pozice
 */
void vehicle::setJourneyPos(int pos, int stop)
{
    journeyPos = pos;
    //stopNum = stop;
}

/**
 * @brief funkce, která nastaví flag, jeslti se u vozidla má nastavit cesta zpět
 * @param wB true/false
 */
void vehicle::setWayback(bool wB)
{
    wayBack = wB;
}

bool isBetween(coordinate start, coordinate end, coordinate point){
    double crossproduct = (point.getY() - start.getY()) * (end.getX() - start.getX()) - (point.getX() - start.getX()) * (end.getY() - start.getY());
    if(abs(crossproduct) > 0.1){
        return false;
    }

    double dotproduct = (point.getX() - start.getX()) * (end.getX() - start.getX()) + (point.getY() - start.getY()) * (end.getY() - start.getY());
    if(dotproduct < 0){
        return false;
    }

    double squaredlen = (end.getX() - start.getX()) * (end.getX() - start.getX()) + (end.getY() - start.getY()) * (end.getY() - start.getY());
    if(dotproduct > squaredlen){
        return false;
    }

    return true;
}

/**
 * @brief funkce, která zajištujě pohyb vozidla
 * @param sceneTime čas scény
 */
void vehicle::move(QTime sceneTime)
{
    //qDebug() << speed;
    //qDebug() << "Speed in Move: " << speed;
    if(!stopBool || sceneTime >= stopTime.addMSecs(10000)){
        stop nextStop = stopVec.at(stopNum);


        if((!stopVec[stopNum - 1].getStreets()[0]->getDelayed() && isBetween(stopVec[stopNum - 1].getStreets()[0]->getStart(), stopVec[stopNum - 1].getStreets()[0]->getEnd(), journey[journeyPos]))
        && (!stopVec[stopNum].getStreets()[0]->getDelayed() && isBetween(stopVec[stopNum].getStreets()[0]->getStart(), stopVec[stopNum].getStreets()[0]->getEnd(), journey[journeyPos]))){
            preDelay = sceneTime;
        }

        if((stopVec[stopNum - 1].getStreets()[0]->getDelayed() && isBetween(stopVec[stopNum - 1].getStreets()[0]->getStart(), stopVec[stopNum - 1].getStreets()[0]->getEnd(), journey[journeyPos]))
        || (stopVec[stopNum].getStreets()[0]->getDelayed() && isBetween(stopVec[stopNum].getStreets()[0]->getStart(), stopVec[stopNum].getStreets()[0]->getEnd(), journey[journeyPos]))){

            int delay = 0;
            if((stopVec[stopNum - 1].getStreets()[0]->getDelayed() && isBetween(stopVec[stopNum - 1].getStreets()[0]->getStart(), stopVec[stopNum - 1].getStreets()[0]->getEnd(), journey[journeyPos]))){
                delay = stopVec[stopNum - 1].getStreets()[0]->getDelay();
            }
            else if (stopVec[stopNum].getStreets()[0]->getDelayed() && isBetween(stopVec[stopNum].getStreets()[0]->getStart(), stopVec[stopNum].getStreets()[0]->getEnd(), journey[journeyPos])){
                delay = stopVec[stopNum].getStreets()[0]->getDelay();
            }


            if(sceneTime < preDelay.addMSecs(delay)){
                //qDebug() << "Vehicle is delayed here, Street " << nextStop.getStreets()[0]->getName() << " Delay: " << nextStop.getStreets()[0]->getDelay();

                //qDebug() << "Not going";
                return;
            }

            //qDebug() << "Going";
            preDelay = sceneTime;
        }



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
            stopTime = sceneTime;
            stopNum++;
            if(line->getRoute().size() == stopNum){
                if(wayBack){
                    wayBack = false;
                    destr = true;
                     //qDebug() << " WAYBACK IS TRUE X CURRENT: " << coords->getX() << " Y CURRENT: " << coords->getY() << journeyPos;
                     //qDebug() << " X STOP: " << nextStop.getCoord()->getX() << " Y STOP: " << nextStop.getCoord()->getY();
                    delete getGraphics()[0];
                }
                else{
                    //qDebug() << journey.size() << stopVec.size();
                    wayBack = true;
                    //qDebug() << "WAYBACK IS FALSE X CURRENT: " << coords->getX() << " Y CURRENT: " << coords->getY() << journeyPos;
                    //qDebug() << " X STOP: " << nextStop.getCoord()->getX() << " Y STOP: " << nextStop.getCoord()->getY();

                }

                stopNum = 1;
                std::reverse(journey.begin(), journey.end());
                std::reverse(stopVec.begin(), stopVec.end());
                journeyPos = 0;
            }
        }
    }
    //
}

double vehicle::pointDistance(coordinate oldCoord, coordinate newCoord){
    return sqrt(pow(oldCoord.getX() - newCoord.getX(), 2) + pow( oldCoord.getY() - newCoord.getY(), 2));
}

/**
 * @brief funkce, která vypočítá cestu, kterou pojede vozidlo v rámci linky
 */
void vehicle::getJourney()
{
    stopNum = 1;
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
    coordinate oldCoordinate;
    int i = 0;
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
                //i--;
            }
            oldCoordinate = journey[journey.size() - 1];
            do{
                //++i;

                a = abs(oldCoordinate.getY() - line->getRoute().at(j).getStreet(stopStreetNum)->getEnd().getY());
                b = abs(oldCoordinate.getX() - line->getRoute().at(j).getStreet(stopStreetNum)->getEnd().getX());

                b_pow = pow(b, 2);
                a_pow = pow(a, 2);
                c_pow = a_pow + b_pow;

                c = sqrt(c_pow);
                ratio = 0.75 / c;

                if(oldCoordinate.getX() > line->getRoute().at(j).getStreet(stopStreetNum)->getEnd().getX()){
                    if(oldCoordinate.getY() > line->getRoute().at(j).getStreet(stopStreetNum)->getEnd().getY()){
                        coordinate newCoord(oldCoordinate.getX() - ratio * b, oldCoordinate.getY() - ratio * a);
                        if(pointDistance(journey.at(i), newCoord) >= 0.5){
                            journey.append(newCoord);
                            i++;
                        }
                        else{
                            oldCoordinate = newCoord;
                        }
                    }
                    else if(oldCoordinate.getY() < line->getRoute().at(j).getStreet(stopStreetNum)->getEnd().getY()){
                        coordinate newCoord(oldCoordinate.getX() - ratio * b, oldCoordinate.getY() + ratio * a);
                        if(pointDistance(journey.at(i), newCoord) >= 0.5){
                            journey.append(newCoord);
                            i++;
                        }
                        else{
                            oldCoordinate = newCoord;
                        }
                    }
                    else if(oldCoordinate.getY() == line->getRoute().at(j).getStreet(stopStreetNum)->getEnd().getY()){
                        coordinate newCoord(oldCoordinate.getX() - ratio * b, oldCoordinate.getY());
                        if(pointDistance(journey.at(i), newCoord) >= 0.5){
                            journey.append(newCoord);
                            i++;
                        }
                        else{
                            oldCoordinate = newCoord;
                        }
                    }
                }
                else if(oldCoordinate.getX() < line->getRoute().at(j).getStreet(stopStreetNum)->getEnd().getX()){
                    if(oldCoordinate.getY() > line->getRoute().at(j).getStreet(stopStreetNum)->getEnd().getY()){
                        coordinate newCoord(oldCoordinate.getX() + ratio * b, oldCoordinate.getY() - ratio * a);
                        if(pointDistance(journey.at(i), newCoord) >= 0.5){
                            journey.append(newCoord);
                            i++;
                        }
                        else{
                            oldCoordinate = newCoord;
                        }
                    }
                    else if(oldCoordinate.getY() < line->getRoute().at(j).getStreet(stopStreetNum)->getEnd().getY()){
                        coordinate newCoord(oldCoordinate.getX() + ratio * b, oldCoordinate.getY() + ratio * a);
                        if(pointDistance(journey.at(i), newCoord) >= 0.5){
                            journey.append(newCoord);
                            i++;
                        }
                        else{
                            oldCoordinate = newCoord;
                        }
                    }
                    else if(oldCoordinate.getY() == line->getRoute().at(j).getStreet(stopStreetNum)->getEnd().getY()){
                        coordinate newCoord(oldCoordinate.getX() + ratio * b, oldCoordinate.getY());
                        if(pointDistance(journey.at(i), newCoord) >= 0.5){
                            journey.append(newCoord);
                            i++;
                        }
                        else{
                            oldCoordinate = newCoord;
                        }
                    }
                }
                else if(oldCoordinate.getX() == line->getRoute().at(j).getStreet(stopStreetNum)->getEnd().getX()){
                    if(oldCoordinate.getY() > line->getRoute().at(j).getStreet(stopStreetNum)->getEnd().getY()){
                        coordinate newCoord(oldCoordinate.getX(), oldCoordinate.getY() - ratio * a);
                        if(pointDistance(journey.at(i), newCoord) >= 0.5){
                            journey.append(newCoord);
                            i++;
                        }
                        else{
                            oldCoordinate = newCoord;
                        }
                    }
                    else if(oldCoordinate.getY() < line->getRoute().at(j).getStreet(stopStreetNum)->getEnd().getY()){
                        coordinate newCoord(oldCoordinate.getX(), oldCoordinate.getY() + ratio * a);
                        if(pointDistance(journey.at(i), newCoord) >= 0.5){
                            journey.append(newCoord);
                            i++;
                        }
                        else{
                            oldCoordinate = newCoord;
                        }
                    }
                }


                if(line->getRoute().at(j).getStreet(0)->getName().compare("testStreet23") == 0){
                    //qDebug() << journey.at(i).getX() << " :X Y: " << journey.at(i).getY();
                }


                /*
                qDebug() << "X: " << journey.at(i).getX() << " Y: " << journey.at(i).getY();
                qDebug() << "X: " << line->getRoute().at(j).getStreet(stopStreetNum)->getEnd().getX() << " Y: " << line->getRoute().at(j).getStreet(stopStreetNum)->getEnd().getY();
                qDebug() << "X: " << journey.at(i).getX() << " Y: " << journey.at(i).getY();
                */

            }while(pointDistance(journey.at(i), line->getRoute().at(j).getStreet(stopStreetNum)->getEnd()) > 0.5);
            //journey.append(coordinate(line->getRoute().at(j).getStreet(stopStreetNum)->getEnd().getX(), line->getRoute().at(j).getStreet(stopStreetNum)->getEnd().getY()));
            journey[journey.size() - 1] = coordinate(line->getRoute().at(j).getStreet(stopStreetNum)->getEnd().getX(), line->getRoute().at(j).getStreet(stopStreetNum)->getEnd().getY());
            //i++;
            swpStop = new stop();
            *swpStop = line->getRoute().at(j);
        }
    }

    int k = 0;
    int idx = 0;
    for(int j = 0; j < line->getRoute().size(); j++){
        k = 0;
        //qDebug() << line->getRoute().at(j).getStopName();
        //qDebug() << line->getRoute()[j].getCoord()->getX() << line->getRoute()[j].getCoord()->getY();
        for (coordinate journeyCoord : journey){

            if(journeyCoord.getX() == 292);
                //qDebug() << journeyCoord.getY();

            if(round(line->getRoute().at(j).getCoord()->getX()) == round(journeyCoord.getX())
            && round(line->getRoute().at(j).getCoord()->getY()) == round(journeyCoord.getY())){

                journey[k] = *line->getRoute().at(j).getCoord();
                idx = k;

                qDebug() << line->getRoute().at(j).getStopName();

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

/**
 * @brief funkce, která nastaví číslo následující zastávky
 */
void vehicle::setStopNum(){
    int stopCnt = 0;
    for(coordinate jCoord : journey){
        if(stopVec[stopCnt].getCoord()->getX() == jCoord.getX()
        && stopVec[stopCnt].getCoord()->getY() == jCoord.getY()){

            //qDebug() << stopVec[stopCnt].getStopName();

            stopCnt++;
        }

        if(jCoord.getX() == journey[journeyPos].getX() && jCoord.getY() == journey[journeyPos].getY()){


            stopNum = stopCnt;
            //qDebug() << stopNum;
            //qDebug() << jCoord.getX() << " " << jCoord.getY();
            break;
        }
    }

    //qDebug() << "STOPNUM " << stopNum;
}

/**
 * @brief funkce sloužící k otočení vektoru cesty ->pro cestu zpět
 */
void vehicle::reverseVectors()
{
    std::reverse(journey.begin(), journey.end());
    std::reverse(stopVec.begin(), stopVec.end());
}
