/*!
 * @file
 * @brief Tento soubor obsahuje implementaci třídy ellipse
 *
 * @author Boris Burkalo (xburka00), Jan Klusáček (xklusa14)
 */
#include "ellipse.h"
#include <QDebug>
#include <QDialog>
#include <QGraphicsSceneMouseEvent>
#include <QLabel>

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
        QTime durationTime = ellipseVehicle->getLine()->getDuration(ellipseVehicle->getFullJourney().size());
        double durationSecs = durationTime.hour() * 3600 + durationTime.minute() * 60 + durationTime.second();
        int stopPos = 0;
        QVector<double> stopRatio = ellipseVehicle->getStopRatio();
        for(int j = 0; j < ellipseVehicle->getStopVec().size(); j++){
            if(!ellStop.getStopName().compare(ellipseVehicle->getStopVec()[j].getStopName())){
                //qDebug() << "Found" << ellipseVehicle->getNumber();
                stopPos = j;
                timetableString = timetableString + "       " + ellStop.getStopName() + "\n\n";
                QVector<QTime> departures;
                for(int i = 0; i < ellLine->getStopTime(0).size(); i++){
                    //timetableString = timetableString + "       " + QString::number(i) + "      ";
                    //qDebug() << QString::number(i);
                    for(int k = 0; k < ellLine->getStopTime(0)[i].size(); k++){
                        //QTime time =

                        //qDebug() << durationTime << " PREV";
                        //qDebug() << ellLine->getStopTime(0)[i][k]->addSecs(durationSecs * stopRatio[j]).toString();
                        departures.append(ellLine->getStopTime(0)[i][k]->addSecs(durationSecs * stopRatio[j]));

                      //  timetableString = timetableString + "       " + ellLine->getStopTime(0)[i][k]->toString() + "      ";
                    }


                    //timetableString = timetableString + "\n\n";
                }

                int prev = 0;
                timetableString = timetableString + "       " + "0" + " ";
                for(int l = 0; l < departures.size(); l++){
                    if(prev == departures[l].hour()){
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
                    }
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
