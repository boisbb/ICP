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


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initScene();


    /*
        Ke kolečku pristoupis nasledovne: v cyklu ofc abys prosel vsechny vozidla
        vehicleVector[0].getGraphics()[0];
        tzn.: connect(vehicleVector[i].getGraphics()[0], Nejakej signal, this, SLOT(stisknuteVozidlo(vehicleVector[i]));
    */

    connect(ui->button_plus, &QPushButton::clicked, this, &MainWindow::zoom_in);
    connect(ui->button_minus,&QPushButton::clicked, this, &MainWindow::zoom_out);
    connect(ui->speed_up, &QPushButton::clicked, this, &MainWindow::speed_up);
    connect(ui->slow_down, &QPushButton::clicked, this, &MainWindow::slow_down);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onValueChange(int val)
{
    qDebug() << "value" << val;
}

void MainWindow::moveVeh()
{
    /// moving vehicles
    vehicleVector[0].move();

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
    //qDebug() << interval;
    for(int i = 0; i < vehicleVector.size(); i++){
        vehicleVector[i].speedUp();
    }
    timer->setInterval(interval);
}

void MainWindow::slow_down()
{
    interval *= 2;
    for(int i = 0; i < vehicleVector.size(); i++){
        vehicleVector[i].slowDown();
    }
    timer->setInterval(interval);
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
    QFile input("../examples/map_base.json");
    if(input.open(QIODevice::ReadWrite)){
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
       lineVector[lineVector.size() - 1].getStopTimes();
    }

    // VEHICLES /
    for (QJsonValue vehVal : vehicles) {
        QJsonObject vehObj = vehVal.toObject();
        int number = vehObj.find("number")->toInt();
        coordinate position(vehObj.find("x")->toDouble(),vehObj.find("y")->toDouble());
        vehicleVector.append(vehicle(position, number));
        int i = 0;
        for(busLine line : lineVector){
            if(line.getId() == number){
                vehicleVector[vehicleVector.size() - 1].setLine(line);
                lineVector[i].setColor(vehicleVector[vehicleVector.size() - 1].getColor());
            }
            i++;
        }
        vehicleVector[vehicleVector.size() - 1].getJourney();

        vehicleVector[vehicleVector.size() - 1].setGraphics();
        drawStuff(vehicleVector[vehicleVector.size() - 1].getGraphics());

    }

    ui->graphicsView->scale(0.5, 0.5);


}

void MainWindow::initScene()
{
    myScene = new scene(ui->graphicsView);
    ui->graphicsView->setScene(myScene);
    coordinate testCoord(150, 150);
    deserialize();



    /*
    street testStreet(coordinate(100.0, 200.0), coordinate(400.0, 500.0), "testStreet");
    testStreet.setGraphics();
    this->drawStuff(testStreet.getGraphics());


    stop testStop1("testStop1", coordinate(100, 200));
    testStop1.setStreet(testStreet);
    testStop1.setGraphics();
    this->drawStuff(testStop1.getGraphics());

    stop testStop2("testStop2", coordinate(250, 350));
    testStop2.setStreet(testStreet);
    testStop2.setGraphics();
    this->drawStuff(testStop2.getGraphics());

    stop testStop3("testStop3", coordinate(400, 500));
    testStop3.setStreet(testStreet);
    testStop3.setGraphics();
    this->drawStuff(testStop3.getGraphics());


    QVector<QString> testStops;
    testStops.append("testStop1");
    testStops.append("testStop2");
    testStops.append("testStop3");
    busLine testLine(10);
    testLine.addStop(testStop1);
    testLine.addStop(testStop2);
    testLine.addStop(testStop3);



    vehicle testVehicle(coordinate(100.0, 200.0), 10);
    testVehicle.setGraphics();
    testVehicle.setLine(testLine);
    testVehicle.getJourney();
    vehicleVector.append(testVehicle);
    drawStuff(vehicleVector.at(0).getGraphics());


    //auto line = line();

    QJsonDocument doc;
    QJsonObject objStops;
    QJsonObject objVehicle;
    QJsonObject objLine;
    QJsonObject objStreets;
    QJsonArray stopArr;
    QJsonArray stopStreets;
    stopStreets.append(QJsonValue("testStreet"));
    stopArr.append(QJsonObject({
                               {"name", testStop1.getStopName()},
                               {"x", testStop1.getCoord()->getX()},
                               {"y", testStop1.getCoord()->getY()},
                               {"street name", stopStreets},
                           }));

    stopArr.append(QJsonObject({
                               {"name", testStop2.getStopName()},
                               {"x", testStop2.getCoord()->getX()},
                               {"y", testStop2.getCoord()->getY()},
                               {"street name", stopStreets},
                           }));

    stopArr.append(QJsonObject({
                               {"name", testStop3.getStopName()},
                               {"x", testStop3.getCoord()->getX()},
                               {"y", testStop3.getCoord()->getY()},
                               {"street name", stopStreets},
                           }));


    QJsonObject stops{{"stops", stopArr}};

    QJsonArray streetArr;
    streetArr.append(QJsonObject({
                                     {"start x", testStreet.getStart().getX()},
                                     {"start y", testStreet.getStart().getY()},
                                     {"end x", testStreet.getEnd().getX()},
                                     {"end y", testStreet.getEnd().getY()},
                                     {"name", testStreet.getName()},
                                 }));

    QJsonArray lineArr;
    QJsonArray lineStops;
    lineStops.append(QJsonValue("testStop1"));
    lineArr.append(QJsonObject({
                                   {"number", 10},
                                   {"stops", lineStops}
                               }));

    QJsonArray vehicleArr;
    vehicleArr.append(QJsonObject({
                                          {"x", 100},
                                          {"y", 200},
                                          {"number", 10}
                                      }));



    QJsonObject streets{{"streets", streetArr}};
    QJsonObject lines{{"lines", lineArr}};
    QJsonObject vehicles{{"vehicles", vehicleArr}};
    QJsonArray all;
    all.append(stops);
    all.append(streets);
    all.append(lines);
    all.append(vehicles);

    //QJsonObject allObj{{"map", all}};




    QFile input("../examples/map.json");
    if(input.open(QIODevice::ReadWrite)){
        qDebug() << "Created";
    }



    doc.setArray(all);
    input.write(doc.toJson());
    QJsonDocument newdoc;
    //QString data = input.readAll();

    //qDebug() << doc.toJson(QJsonDocument::Compact);
    //newdoc = QJsonDocument::fromJson(data.toUtf8());
    //QJsonObject newobject = newdoc.object();
    //QJsonArray array = newobject.find("coords").value().toArray();
    //QJsonArray array = value.toArray();

    //qDebug() << array[1].toObject().value("x").toDouble();
    //qDebug() << newdoc.toJson();
    //qDebug() << testCoord.getX();
    //qDebug() << testCoord.getY();

*/
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    timerStart();

}






