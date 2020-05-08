#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QLabel>//clock
#include <QString>//jen na ukázku pro clock v moveVeh
#include <QGraphicsScene>//info dole
#include <QDateTimeEdit>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initScene();

    connect(ui->button_plus, &QPushButton::clicked, this, &MainWindow::zoom_in);
    connect(ui->button_minus,&QPushButton::clicked, this, &MainWindow::zoom_out);
    connect(ui->speed_up, &QPushButton::clicked, this, &MainWindow::speed_up);
    connect(ui->slow_down, &QPushButton::clicked, this, &MainWindow::slow_down);
    connect(ui->time_changer, &QPushButton::clicked, this, &MainWindow::time_change);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onValueChange(int val)
{
    qDebug() << "value" << val;
}

//funkce na ukazování informací o zvolené trase
void MainWindow::showInfo(vehicle veh, bool check, bool was)
{
    //qDebug() << veh.getNumber();
    //aby se celý box stále nepřekresloval
    static bool was_here = false;
    //aby se bok "klikněte" stále nepřekresloval
    static bool showing = false;
    if(was){
        was_here = true;
    }
    else{
        was_here = false;
    }
    if(check){
        if(!was_here){//fungovalo pro jedno vozidlo
            was_here = true;
            showing = false;
            auto *info_box = new QGraphicsScene(ui->route_info);
            ui->route_info->setScene(info_box);

            auto linka = info_box->addText("Linka:");
            linka->setPos(-500, 0);

            QString number = QString::number(veh.getNumber());
            //qDebug() << number;
            auto cislo = info_box->addText(number);
            cislo->setPos(-450, 0);

            auto route = info_box->addLine(-60,12,330, 12);
            route->setPos(-350, 0);


            QVector<double> stopRatio = veh.getStopRatio();
            for (double ratio : stopRatio) {
                if(!veh.getWayBack()){
                    // Nememlo by byt natvrdo
                    double width = 390;
                    auto stopEll = info_box->addEllipse(-410 + ratio * width - 2, 12 - 2, 4, 4);
                    stopEll->setBrush(QBrush(QColor(0, 0, 0), Qt::SolidPattern));
                }
                else{
                    double width = 390;
                    auto stopEll = info_box->addEllipse(20 - ratio * width - 2, 12 - 2, 4, 4);
                    stopEll->setBrush(QBrush(QColor(0, 0, 0), Qt::SolidPattern));
                }
            }



            ui->route_info->setRenderHint(QPainter::Antialiasing);
            infoVehicle = new QGraphicsEllipseItem((-410 + ((double) veh.getJourneyPos()/(double) veh.getFullJourney().size()) * 390) - 4, 12 - 4, 8, 8);
            info_box->addItem(infoVehicle);
            infoVehicle->setBrush(QBrush(veh.getColor(), Qt::SolidPattern));
        }
       else{
            if(!veh.getWayBack())
                infoVehicle->setRect((-410 + ((double) veh.getJourneyPos()/(double) veh.getFullJourney().size()) * 390) - 4, 12 - 4, 8, 8);
            else
                infoVehicle->setRect((-20 - ((double) veh.getJourneyPos()/(double) veh.getFullJourney().size()) * 390) -4, 12 - 4, 8, 8);
        }
    }
    /* fungovalo pro jedno vozidlo
    else{
        //vyčistí dolní box
        if(!showing){
            showing = true;
            auto *info_box = new QGraphicsScene(ui->route_info);
            ui->route_info->setScene(info_box);
            was_here = false;
            auto text = info_box->addText("klikněte na autobus pro zobrazení podrobností");
        }
    }
    */


}

void MainWindow::draw_stops(QGraphicsScene *scene)
{
    /*
    auto stop =  scene->addEllipse((-400*20), 6, 4, 4);
    stop->setBrush(QBrush(QColor(0, 0, 0), Qt::SolidPattern));
    */
}

void MainWindow::moveVeh()
{
    //aby se "klikněte.." nepřekreslovalo
    static bool was_here = false;
    //na zrušení výberu staréh vozidla při kliknutí na jiné
    static vehicle *prev;
    static bool was = false;
    /// moving vehicles

    int counter = 0;
    int i = 0;
    QVector<int> toBeDestr;
    //zjistí počet vybraných vozidel
    for (vehicle *veh : vehicleVector) {
        veh->move(sceneTime);

        if(veh->destruct()){
            toBeDestr.append(i);
        }

        if(veh->getClicked()){
            counter++;
        }
        i++;
    }

    for(int dest : toBeDestr){
        qDebug() << "To be destructed: " << dest;
        vehicleVector.remove(dest);
    }

    //vozidlo je rozklikntué
    if(counter == 1){
        was_here = false;
        for (vehicle *veh : vehicleVector) {
            //veh->move(sceneTime);
            if(veh->getClicked()){
                MainWindow::showInfo(*veh, true, was);
                //do prev nastaví vozidlo které je zrovna rozkliknuté
                //když se klikne na další tak se tomuto vozidlu zruší flag clicked
                was = true;
                prev = veh;
            }
        }
    }
    //jedno vozidlo je rozkliknuté a klikne se na další
    else if(counter > 1){
        //zrušení flagu předchozího vozidla
        prev->setClicked(false);
        was = false;
    }
    //Žádné vozidlo není rozkliknuté
    else{
        if(!was_here){
            was_here = true;
            was = false;
            auto *info_box = new QGraphicsScene(ui->route_info);
            ui->route_info->setScene(info_box);
            auto text = info_box->addText("klikněte na autobus pro zobrazení podrobností");
        }

    }
    /*fungovalo pro jedno vozidlo
    for (vehicle *veh : vehicleVector) {
        veh->move(sceneTime);
        if(!clicked){
            clicked = true;
            if(veh->getClicked()){
                MainWindow::showInfo(*veh, true);
                qDebug() << "tady";
            }
            else{
                MainWindow::showInfo(*veh, false);
                qDebug() << "here";
                clicked = false;
            }
        }
        else{
            clicked = false;
        }
    }
    */
    bool started = false;
    for(busLine line : lineVector){
        line.getStopTime(0)[0];
        for(int i = 0; i < line.getStopTime(0)[sceneTime.hour()].size(); i++){
            if(sceneTime > *line.getStopTime(0)[sceneTime.hour()][i] && sceneTime < line.getStopTime(0)[sceneTime.hour()][i]->addSecs(1)){
                qDebug() << "Start a vehicle";
                qDebug() << sceneTime.toString();

                /* vehicle creation */
                int number = line.getId();
                coordinate position(line.getRoute()[0].getCoord()->getX(), line.getRoute()[0].getCoord()->getY());
                vehicleVector.append(new vehicle(position, number));

                int i = 0;
                for(busLine line : lineVector){
                    if(line.getId() == number){
                        vehicleVector[vehicleVector.size() - 1]->setLine(line);
                        //lineVector[i].setColor(vehicleVector[vehicleVector.size() - 1]->getColor());
                    }
                    i++;
                }


                qDebug() << "SETTING SPEED TO: " << speed;
                vehicleVector[vehicleVector.size() - 1]->getJourney();
                vehicleVector[vehicleVector.size() - 1]->setWayback(false);
                vehicleVector[vehicleVector.size() - 1]->setStopNum();

                vehicleVector[vehicleVector.size() - 1]->setGraphics();
                drawStuff(vehicleVector[vehicleVector.size() - 1]->getGraphics());

                //started = true;
            }
        }
    }
    sceneTime = sceneTime.addMSecs(500);
    ui->clock->setText(sceneTime.toString());


}

void MainWindow::zoom_in()
{
    ui->graphicsView->scale(1.25, 1.25);
}

void MainWindow::zoom_out()
{
    ui->graphicsView->scale(0.8, 0.8);
}

void MainWindow::speed_up()
{
    //zrychlení

    interval /= 2;
    speed /= 1.2;

    qDebug() << "Interval in Main Window: " << interval;
    //qDebug() << "Speed in Main Window: " << speed;
    timer->setInterval(interval);
}

void MainWindow::slow_down()
{
    interval *= 2;
    speed *= 1.2;

    qDebug() << "Interval in Main Window: " << interval;
    //qDebug() << "Speed in Main Window: " << speed;
    timer->setInterval(interval);
}

void MainWindow::time_change()
{



    /// TODO OPRAVIT KDYZ JE TAM 00:05:00
    sceneTime = ui->timeEdit->time();
    for (int i = vehicleVector.size() - 1; i >= 0; i--) {
        delete vehicleVector[i]->getGraphics()[0];
        vehicleVector.remove(i);
    }

    spawnVehicles();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{


    static QSize old = QWidget::size();
    QSize size = QWidget::size();

    float width = (float)size.rwidth()/(float)old.rwidth();
    //float height = (float)size.rheight()/(float)old.rheight();
    /*
    if(width == 1){
        width = height;
        qDebug() << "sirka";
    }
    else if(height == 1){
        qDebug() << "vyska";
    }
    else{
       height = width;
    }
    */
    ui->graphicsView->scale(width, width);
    //TODO upravit
    ui->route_info->scale(width, width);
    old = size;
    QWidget::resizeEvent(event);

}
void MainWindow::drawStuff(QVector<QGraphicsItem*> items)
{
    for(QGraphicsItem* item : items){
        myScene->addItem(item);
    }
}

void MainWindow::timerStart()
{
    timer->setInterval(interval);
    connect(timer, SIGNAL(timeout()), this, SLOT(moveVeh()));
    timer->start(100);
}

void MainWindow::see_info()
{

}

void MainWindow::deserialize()
{

    /*
    QJsonArray minutes;
    minutes.append(QJsonValue(0));
    minutes.append(QJsonValue(10));
    minutes.append(QJsonValue(20));
    minutes.append(QJsonValue(30));
    minutes.append(QJsonValue(40));
    minutes.append(QJsonValue(50));

    QJsonObject hour{{"0", minutes}};

    QJsonArray hours;
    hours.append(hour);
    hours.append(hour);


    QJsonObject lineObj{{"10", hours}};

    QJsonArray linesArr;
    linesArr.append(lineObj);

    QJsonDocument timetableDoc;
    timetableDoc.setArray(linesArr);

    timetable.write(timetableDoc.toJson());
    */

    QFile timetable("../examples/timetable.json");
    if(!timetable.open(QIODevice::ReadWrite))
        exit(1);

    QString timetableString = timetable.readAll();

    QJsonDocument timetableDoc;
    timetableDoc = QJsonDocument::fromJson(timetableString.toUtf8());
    QJsonArray timetableArray = timetableDoc.array();

    QFile input("../examples/map_base.json");
    if(!input.open(QIODevice::ReadWrite)){
        exit(1);
    }

    QJsonDocument doc;
    QJsonObject objStops;
    QJsonObject objVehicle;
    QJsonObject objLine;
    QJsonObject objStreets;



    QString inputData = input.readAll();
    doc = QJsonDocument::fromJson(inputData.toUtf8());
    QJsonArray fileArray = doc.array();


    QJsonArray stops = fileArray[0].toObject().find("stops").value().toArray();
    QJsonArray streets = fileArray[1].toObject().find("streets").value().toArray();
    QJsonArray lines = fileArray[2].toObject().find("lines").value().toArray();
    QJsonArray vehicles = fileArray[3].toObject().find("vehicles").value().toArray();



    /* Streets */
    for (QJsonValue streetVal : streets) {
        QJsonObject streetObj = streetVal.toObject();
        coordinate start(streetObj.find("start x")->toDouble(), streetObj.find("start y")->toDouble());
        coordinate end(streetObj.find("end x")->toDouble(), streetObj.find("end y")->toDouble());
        QString name = streetObj.find("name")->toString();
        streetVector.append(street(start, end, name));
        streetVector[streetVector.size() - 1].setGraphics();
        drawStuff(streetVector[streetVector.size() - 1].getGraphics());


    }

    /* STOPS */
    for(QJsonValue stopVal : stops){
        QJsonObject stopObj = stopVal.toObject();
        QString name = stopObj.find("name").value().toString();
        coordinate stopCoord = coordinate(stopObj.find("x").value().toDouble(), stopObj.find("y").value().toDouble());
        QJsonArray streetArray = stopObj.find("street name")->toArray();

        stopVector.append(stop(stopObj.find("name").value().toString(), stopCoord));
        stopVector[stopVector.size() - 1].setGraphics();
        drawStuff(stopVector[stopVector.size() - 1].getGraphics());

        for (street streetStop : streetVector) {
            for (QJsonValue streetName : streetArray) {
                if(streetStop.getName() == streetName.toString()){
                    stopVector[stopVector.size() - 1].setStreet(streetStop);
                }
            }

        }
    }


    // LINES /
    for (QJsonValue lineVal : lines) {
       QJsonObject lineObj = lineVal.toObject();
       int number = lineObj.find("number")->toInt();
       QJsonArray stops = lineObj.find("stops")->toArray();
       lineVector.append(busLine(number));
       for (stop lineStop : stopVector) {
            for(QJsonValue stopName : stops){
                if(stopName.toString() == lineStop.getStopName()){
                    lineVector[lineVector.size() - 1].addStop(lineStop);
                }
            }
       }
       //lineVector[lineVector.size() - 1].generateStopTimes();
       QJsonObject testObj;
       for (int i = 0; i < timetableArray.size(); i++) {
           testObj = timetableArray[i].toObject();
           if(testObj.find(QString::number(lineVector[lineVector.size() - 1].getId())) != testObj.end()){
               qDebug() << QString::number(lineVector[lineVector.size() - 1].getId());
               lineVector[lineVector.size() - 1].generateStopTimes(testObj.find(QString::number(lineVector[lineVector.size() - 1].getId())).value().toArray());
           }
       }
    }

    //lineVector[lineVector.size() - 1].generateStopTimes();
    //exit(1);


    spawnVehicles();
    //exit(1);

    ui->graphicsView->scale(0.5, 0.5);
}

void MainWindow::spawnVehicles(){
    // VEHICLES /
    // o pulnoci se to nejak jebe
    // create blank vehicle just to compute the journey
    for (int i = 0; i < lineVector.size(); i++) {
        vehicle blankVeh(*lineVector[i].getRoute()[0].getCoord(), -200);
        blankVeh.setLine(lineVector[i]);
        blankVeh.getJourney();
        QTime duration = lineVector[i].getDuration(blankVeh.getFullJourney().size());
        qDebug() << "Before " << sceneTime.toString();
        qDebug() << duration.toString();
        QTime swpSceneTime = sceneTime.addSecs((-duration.second() - duration.minute() * 60 - duration.hour() * 3600)*2);

        qDebug() << "After " << swpSceneTime.addSecs(-duration.second() - duration.minute() * 60 - duration.hour() * 3600).toString();
        QVector<QVector<QTime*>> stopTimes = lineVector[i].getStopTime(0);
        for (int k = swpSceneTime.hour(); k <= sceneTime.hour(); ++k) {
            for (int j = 0; j < stopTimes[k].size(); ++j) {
                //qDebug()<< "TIMES " << stopTimes[i][j]->toString();
                if(*stopTimes[k][j] >= swpSceneTime && *stopTimes[k][j] <= sceneTime){
                    qDebug()<< "TIME IN INTERVAL: " << stopTimes[k][j]->toString();
                    QTime travelledTime = sceneTime.addSecs(-stopTimes[k][j]->hour() * 3600 -stopTimes[k][j]->minute() * 60 -stopTimes[k][j]->second());
                    //qDebug() << travelledTime.toString();
                    double travelledMinsToDouble = travelledTime.minute() + (double)((double)travelledTime.second() / 60.0);
                    double durationMinsToDouble = duration.minute() + (double)((double)duration.second() / 60.0);
                    double travelRatio = travelledMinsToDouble / durationMinsToDouble;
                    //qDebug() << "Travelled: " << travelledMinsToDouble << " Duration: " << durationMinsToDouble << " Travel ratio: " << travelRatio;

                    int position = blankVeh.getFullJourney().size() * travelRatio;
                    //int stopPosition = (lineVector[i].getRoute().size()) * travelRatio;


                    if(travelRatio > 1){
                        qDebug() << "BIGGER TIME IN INTERVAL: " << stopTimes[k][j]->toString();
                        position = blankVeh.getFullJourney().size() * (travelRatio - 1);
                        //stopPosition = (lineVector[i].getRoute().size()) * (travelRatio - 1);
                    }


                    //qDebug() << lineVector[i].getRoute().size();
                    qDebug() << "JoureyPos: " << position;
                    vehicle *newVehicle = new vehicle(blankVeh.getFullJourney()[position], lineVector[i].getId());


                    newVehicle->setLine(lineVector[i]);
                    newVehicle->setJourneyPos(position, 0);
                    newVehicle->getJourney();

                    if(travelRatio > 1){
                        newVehicle->reverseVectors();
                        newVehicle->setWayback(true);
                    }
                    newVehicle->setStopNum();
                    newVehicle->setGraphics();
                    drawStuff(newVehicle->getGraphics());
                    vehicleVector.append(newVehicle);
                }
            }
        }
    }
    //exit(0);

    /*
    for (QJsonValue vehVal : vehicles) {
        QJsonObject vehObj = vehVal.toObject();
        int number = vehObj.find("number")->toInt();
        coordinate position(vehObj.find("x")->toDouble(),vehObj.find("y")->toDouble());
        vehicleVector.append(new vehicle(position, number));
        int i = 0;
        for(busLine line : lineVector){
            if(line.getId() == number){
                vehicleVector[vehicleVector.size() - 1]->setLine(line);
                lineVector[i].setColor(vehicleVector[vehicleVector.size() - 1]->getColor());
            }
            i++;
        }
        vehicleVector[vehicleVector.size() - 1]->getJourney();

        vehicleVector[vehicleVector.size() - 1]->setGraphics();
        drawStuff(vehicleVector[vehicleVector.size() - 1]->getGraphics());

    }*/
}

void MainWindow::initScene()
{
    myScene = new scene(ui->graphicsView);
    ui->graphicsView->setScene(myScene);
    coordinate testCoord(150, 150);
    deserialize();
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    timerStart();

}






