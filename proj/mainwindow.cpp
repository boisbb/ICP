#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scene.h"

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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onValueChange(int val)
{
    qDebug() << "value" << val;
}

void MainWindow::initScene()
{
    auto *myScene = new scene(ui->graphicsView);
    ui->graphicsView->setScene(myScene);
    QGraphicsLineItem *testLine = new QGraphicsLineItem(100, 200, 400, 500);
    myScene->addItem(testLine);
    //auto line = myScene->addLine(150, 150, 50, 30);
    coordinate testCoord(150, 150);

    vehicle testVehicle(testCoord, 10);
    street testStreet(coordinate(100.0, 200.0), coordinate(400.0, 500.0), "testStreet");


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

    qDebug() << array[1].toObject().value("x").toDouble();
    //qDebug() << newdoc.toJson();
    qDebug() << testCoord.getX();
    qDebug() << testCoord.getY();


    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
}


