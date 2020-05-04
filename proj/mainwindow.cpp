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


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initScene();

    connect(ui->button_plus, &QPushButton::clicked, this, &MainWindow::zoom_in);
    connect(ui->button_minus,&QPushButton::clicked, this, &MainWindow::zoom_out);
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
}

void MainWindow::zoom_in()
{
    ui->graphicsView->scale(1.25, 1.25);
}

void MainWindow::zoom_out()
{
    ui->graphicsView->scale(0.75, 0.75);
}

void MainWindow::drawStuff(QVector<QGraphicsItem*> items)
{
    for(QGraphicsItem* item : items){
        myScene->addItem(item);
    }
}

void MainWindow::timerStart()
{
    timer->setInterval(50);
    connect(timer, SIGNAL(timeout()), this, SLOT(moveVeh()));
          timer->start(100);
}

void MainWindow::initScene()
{
    myScene = new scene(ui->graphicsView);
    ui->graphicsView->setScene(myScene);
    coordinate testCoord(150, 150);




    street testStreet(coordinate(100.0, 200.0), coordinate(400.0, 500.0), "testStreet");
    testStreet.setGraphics();
    this->drawStuff(testStreet.getGraphics());


    stop testStop1("testStop1", coordinate(100, 200), "testStreet");
    testStop1.setStreet(testStreet);
    testStop1.setGraphics();
    this->drawStuff(testStop1.getGraphics());

    stop testStop2("testStop2", coordinate(250, 350), "testStreet");
    testStop2.setStreet(testStreet);
    testStop2.setGraphics();
    this->drawStuff(testStop2.getGraphics());

    stop testStop3("testStop3", coordinate(400, 500), "testStreet");
    testStop3.setStreet(testStreet);
    testStop3.setGraphics();
    this->drawStuff(testStop3.getGraphics());


    QVector<QString> testStops;
    testStops.append("testStop1");
    testStops.append("testStop2");
    testStops.append("testStop3");
    busLine testLine(10, testStops);
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
    QJsonObject obj;
    QJsonArray arr;

    arr.append(QJsonObject({
               {"x", testCoord.getX()},
               {"y", testCoord.getY()}
               }));
    arr.append(QJsonObject({
               {"x", testCoord.getX()},
               {"y", testCoord.getY()}
               }));


    QJsonObject coord{{"coords", arr}};


    QFile input("../proj/map.json");
    if(input.open(QIODevice::ReadWrite)){
        qDebug() << "Created";
    }



    //doc.setObject(coord);
    //input.write(doc.toJson());
    QJsonDocument newdoc;
    QString data = input.readAll();

    //qDebug() << doc.toJson(QJsonDocument::Compact);
    newdoc = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject newobject = newdoc.object();
    QJsonArray array = newobject.find("coords").value().toArray();
    //QJsonArray array = value.toArray();

    //qDebug() << array[1].toObject().value("x").toDouble();
    //qDebug() << newdoc.toJson();
    //qDebug() << testCoord.getX();
    //qDebug() << testCoord.getY();


    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    timerStart();
}






