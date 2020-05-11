/*!
 * @file
 * @brief Slouží pro zachytávání klikání na vozidlo
 *
 * @author Boris Burkalo (xburka00), Jan Klusáček (xklusa14)
 */
#include "ellipse.h"
#include <QDebug>
#include <QDialog>
#include <QGraphicsSceneMouseEvent>
#include <QLabel>
#include <cmath>

#include "coordinate.h"


/**
 * @brief TODO funkce pro nastavení vozidla
 * @param ellVeh vozidlo
 */
void ellipse::setVehicle(vehicle *ellVeh)
{
    ellipseVehicle = ellVeh;
}

void ellipse::setStop(stop eStop, busLine *line)
{
    ellStop = eStop;
    ellLine = line;
}

/**
 * @brief funkce, sloužící pro zachycení eventu kliknutí na vozidlo
 * @param event event - kliknutí
 * @details pokud se ve scéně klikne na vozidlo, pak se mu nastvaví flag clicked
 */
void ellipse::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(ellLine == nullptr){
        //TODO překlikávání když bude víc vozidel
        if(ellipseVehicle->getClicked()){
            ellipseVehicle->setClicked(false);
        }
        else{
            ellipseVehicle->setClicked(true);
        }
    }
    else{

        qDebug() << "Clicked but not vehicle";
        QDialog *timetableDialog = new QDialog();
        timetableDialog->setWindowTitle("Timetable");
        QLabel *timetableLabel = new QLabel(timetableDialog);
        QString timetableString;
        QTime durationTime = ellipseVehicle->getLine()->getDuration(ellipseVehicle->getFullJourney().size() - 1);
        double durationSecs = durationTime.hour() * 3600 + durationTime.minute() * 60 + durationTime.second();
        int stopPos = 0;
        QVector<double> stopRatio = ellipseVehicle->getStopRatio();
        for(int j = 0; j < ellipseVehicle->getStopVec().size(); j++){
            if(!ellStop.getStopName().compare(ellipseVehicle->getStopVec()[j]->getStopName())){
                stopPos = j;
                timetableString = timetableString + "       " + ellStop.getStopName() + "\n\n";
                QVector<QTime> departures;
                for(int i = 0; i < ellLine->getStopTime(0).size(); i++){
                    for(int k = 0; k < ellLine->getStopTime(0)[i].size(); k++){
                        if(ellipseVehicle->getWayBack())
                            stopRatio[j] = 1 - stopRatio[j] + 1;

                        departures.append(ellLine->getStopTime(0)[i][k]->addSecs(durationSecs * stopRatio[j]));
                    }

                }

                for(int l = 0; l < 23; l++){
                    timetableString = timetableString + "       " + QString::number(l) + " ";
                    for(int m = 0; m < departures.size(); m++){
                        if(l == departures[m].hour()){
                            timetableString = timetableString + "  " + QString::number(round(((double)departures[m].minute() + (double)((double)departures[m].second()/60.0))));
                        }
                    }
                    timetableString = timetableString + "    \n\n";

                    /*if(prev == departures[l].hour()){
                        //timetableString = timetableString +
                        qDebug() << departures[l].toString();
                        timetableString = timetableString + "  " + QString::number(departures[l].minute());
                        //timet
                    }
                    else{
                        qDebug() << departures[l].toString() << " SWITCHED";
                        prev = departures[l].hour();
                        timetableString = timetableString + "    \n\n       " + QString::number(departures[l].hour());
                        timetableString = timetableString + "   " + QString::number(departures[l].minute());
                    }*/
                }
            }
            //break;

        }

        timetableLabel->setText(timetableString);
        timetableLabel->adjustSize();
        timetableDialog->show();


    }
    event->ignore();
}
