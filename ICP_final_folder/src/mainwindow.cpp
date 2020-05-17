/*!
 * @file
 * @brief Souží k práci s vzhledem celého programu
 *
 * @author Boris Burkalo (xburka00), Jan Klusáček (xklusa14)
 */


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
#include <QLabel>
#include <QString>
#include <QGraphicsScene>
#include <QDateTimeEdit>
#include <line.h>
#include "ellipse.h"
#include <QDialog>

/**
 * @brief Konstruktor MainWindow
 * @param parent rodič
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initScene();


    connect(ui->close_down, &QPushButton::clicked, this, &MainWindow::close_down);
    connect(ui->set_detour,&QPushButton::clicked, this, &MainWindow::set_detour);
    connect(ui->reset, &QPushButton::clicked, this, &MainWindow::reset);
    connect(ui->button_plus, &QPushButton::clicked, this, &MainWindow::zoom_in);
    connect(ui->button_minus,&QPushButton::clicked, this, &MainWindow::zoom_out);
    connect(ui->speed_up, &QPushButton::clicked, this, &MainWindow::speed_up);
    connect(ui->slow_down, &QPushButton::clicked, this, &MainWindow::slow_down);
    connect(ui->time_changer, &QPushButton::clicked, this, &MainWindow::time_change);
    connect(ui->delay_plus, &QPushButton::clicked, this, &MainWindow::delay_plus);
    connect(ui->delay_minus, &QPushButton::clicked, this, &MainWindow::delay_minus);
    connect(ui->delay_reset, &QPushButton::clicked, this, &MainWindow::delay_reset);
}
/**
 * @brief Destruktor MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief funkce na ukazování informací o zvolené trase
 *
 * @param veh vozidlo, na ktéré uživatel kliknul a chce o něm vědět bližší informace
 * @param was říká nám jeslti už byly informace jednou vykreslené (aby se nepřekreslovaly pokaždé)
 *
 */

void MainWindow::showInfo(vehicle *veh, bool was)
{
    static bool was_here = false;
        if(was){
            was_here = true;
        }
        else{
            was_here = false;
        }
        if(!was_here){

            was_here = true;
            auto *info_box = new QGraphicsScene(ui->route_info);
            ui->route_info->setScene(info_box);

            auto linka = info_box->addText("Linka:");
            linka->setDefaultTextColor(QColor(0,0,0));
            linka->setPos(-500, 0);

            QString number = QString::number(veh->getNumber());
            auto cislo = info_box->addText(number);
            cislo->setDefaultTextColor(QColor(0,0,0));
            cislo->setPos(-450, 0);

            auto route = info_box->addLine(-60,12,330, 12);
            route->setPos(-350, 0);


            QVector<double> stopRatio = veh->getStopRatio();
            QPen pen;
            pen.setColor(veh->getColor());
            pen.setWidth(2);
            int counter = 0;
            for (double ratio : stopRatio) {
                QVector<stop*> current_stop = veh->getStopVec();
                if(!veh->getWayBack()){
                    double width = 390;
                    ellipse *stopEll = new ellipse();
                    stopEll->setRect(-410 + ratio * width - 2, 12 - 2, 4, 4);
                    info_box->addItem(stopEll);
                    stopEll->setStop(*current_stop[counter], veh->getLine());
                    stopEll->setBrush(QBrush(QColor(0, 0, 0), Qt::SolidPattern));


                    auto stop_name = info_box->addText(current_stop[counter]->getStopName());
                    stop_name->setDefaultTextColor(QColor(0,0,0));
                    stop_name->setPos(-415 + ratio * width - 2, 12 - 2);
                    stopEll->setVehicle(veh);
                    stop_name->setRotation(-90);
                    stop_name->setScale(0.5);
                }
                else{
                    double width = 390;
                    ellipse *stopEll = new ellipse();
                    stopEll->setRect(-20 - ratio * width - 2, 12 - 2, 4, 4);
                    stopEll->setVehicle(veh);
                    stopEll->setStop(*current_stop[current_stop.size() - 1 - counter], veh->getLine());
                    info_box->addItem(stopEll);
                    stopEll->setBrush(QBrush(QColor(0, 0, 0), Qt::SolidPattern));

                    auto stop_name = info_box->addText(current_stop[veh->get_stops_number()-1-counter]->getStopName());
                    stop_name->setDefaultTextColor(QColor(0,0,0));
                    stop_name->setPos(-25 - ratio * width - 2, 12 - 2);
                    stop_name->setRotation(-90);
                    stop_name->setScale(0.5);
                }
                counter++;
            }


            ui->route_info->setRenderHint(QPainter::Antialiasing);
            infoVehicle = new QGraphicsEllipseItem((-410 + ((double) veh->getJourneyPos()/(double) veh->getFullJourney().size()) * 390) - 4, 12 - 4, 8, 8);
            info_box->addItem(infoVehicle);
            infoVehicle->setBrush(QBrush(veh->getColor(), Qt::SolidPattern));
            }
            else{
                if(!veh->getWayBack())
                    infoVehicle->setRect((-410 + ((double) veh->getJourneyPos()/(double) veh->getFullJourney().size()) * 390) - 4, 12 - 4, 8, 8);
                else
                    infoVehicle->setRect((-20 - ((double) veh->getJourneyPos()/(double) veh->getFullJourney().size()) * 390) -4, 12 - 4, 8, 8);
        }

}

/**
 * @brief Zjistí, zda je nějaké vozidlo vybrané a obarví ho.
 * @param streetInst instance třídy ulice
 */

void MainWindow::isChosen(street* streetInst)
{
    if(dynamic_cast<class line*>(streetInst->getGraphics()[0])->getChosen()){
        if(chosenStreets.size() != 0 && chosenStreets[0]->getName().compare(streetInst->getName())){
            dynamic_cast<class line*>(chosenStreets[0]->getGraphics()[0])->unChoose();

            chosenStreets.append(streetInst);
            dynamic_cast<class line*>(chosenStreets[1]->getGraphics()[0])->Choose();

            chosenStreets.remove(0);
        }
        else if(chosenStreets.size() == 0){
            chosenStreets.append(streetInst);
            dynamic_cast<class line*>(chosenStreets[0]->getGraphics()[0])->Choose();
        }
    }
    else {
        if(chosenStreets.size() != 0 && !chosenStreets[0]->getName().compare(streetInst->getName())){
            if(!dynamic_cast<class line*>(chosenStreets[0]->getGraphics()[0])->getChosen())
                chosenStreets.remove(0);
            dynamic_cast<class line*>(streetInst->getGraphics()[0])->unChoose();
        }
    }
}

/**
 * @brief funkce na posunování vozidla
 * @details mimo jiné funkce kontroluje, jeslti nebylo kliknuté na nějaké vozidlo a případně volá funkci \ref showInfo pro zobrazení informací
 */

void MainWindow::moveVeh()
{


    justClicked = false;



    static bool was_here = false;
    static vehicle *prev;
    static bool was = false;
    /// moving vehicles

    int counter = 0;
    int i = 0;
    QVector<int> toBeDestr;
    //zjistí počet vybraných vozidel
    for (vehicle *veh : vehicleVector) {

        if(veh->destruct()){
            toBeDestr.append(i);
        }

        if(veh->getClicked()){
            justClicked = true;
            ++counter;
        }
        i++;

        veh->move(sceneTime);
    }

    for(int dest : toBeDestr){
        vehicleVector.remove(dest);
    }

    //vozidlo je rozklikntué
    if(counter == 1){
        was_here = false;
        justClicked = false;
        for (vehicle *veh : vehicleVector) {
            //veh->move(sceneTime);
            if(veh->getClicked()){
                MainWindow::showInfo(veh, was);
                //do prev nastaví vozidlo které je zrovna rozkliknuté
                //když se klikne na další tak se tomuto vozidlu zruší flag clicked
                was = true;
                prev = veh;

                for(int i = 0; i < veh->get_stops_number(); i++){
                    QGraphicsItem *stop = veh->getStopVec()[i]->getGraphics()[0];
                    dynamic_cast<QGraphicsEllipseItem*>(stop)->setBrush(QBrush(veh->getLine()->getColor(), Qt::SolidPattern));
                }
            }
        }
    }
    //jedno vozidlo je rozkliknuté a klikne se na další
    else if(counter > 1){
        //zrušení flagu předchozího vozidla
        if(prev){
            prev->setClicked(false);
            was = false;
            //Tady odmazat zvýrazněné zastávky přes prev
            for(int i = 0; i < prev->get_stops_number(); i++){
                QGraphicsItem *stop = prev->getStopVec()[i]->getGraphics()[0];
                dynamic_cast<QGraphicsEllipseItem*>(stop)->setBrush(QBrush(QColor(0, 0, 0), Qt::SolidPattern));
            }
        }
    }
    //Žádné vozidlo není rozkliknuté
    else{
        if(!was_here){
            was_here = true;
            was = false;
            //Tady odmazat zvýrazněné zastávky přes prev
            if(prev){
                for(int i = 0; i < prev->get_stops_number(); i++){
                    QGraphicsItem *stop = prev->getStopVec()[i]->getGraphics()[0];
                    dynamic_cast<QGraphicsEllipseItem*>(stop)->setBrush(QBrush(QColor(0, 0, 0), Qt::SolidPattern));
                }
            }

            auto *info_box = new QGraphicsScene(ui->route_info);
            ui->route_info->setScene(info_box);
            auto text_box = info_box->addText("klikněte na autobus pro zobrazení podrobností");
            text_box->setDefaultTextColor(QColor(160, 160, 160));
        }

    }

    for(busLine *line : lineVector){
        line->getStopTime(0)[0];
        for(int i = 0; i < line->getStopTime(0)[sceneTime.hour()].size(); i++){
            if(sceneTime > *line->getStopTime(0)[sceneTime.hour()][i] && sceneTime < line->getStopTime(0)[sceneTime.hour()][i]->addSecs(1)){

                /* vehicle creation */
                int number = line->getId();
                coordinate position(line->getRoute()[0]->getCoord()->getX(), line->getRoute()[0]->getCoord()->getY());
                vehicleVector.append(new vehicle(position, number));

                int i = 0;
                for(busLine *line : lineVector){
                    if(line->getId() == number){
                        vehicleVector[vehicleVector.size() - 1]->setLine(line);
                    }
                    i++;
                }

                vehicleVector[vehicleVector.size() - 1]->getJourney();
                vehicleVector[vehicleVector.size() - 1]->setWayback(false);
                vehicleVector[vehicleVector.size() - 1]->setStopNum();

                vehicleVector[vehicleVector.size() - 1]->setGraphics();
                drawStuff(vehicleVector[vehicleVector.size() - 1]->getGraphics());

                //started = true;
            }
        }
    }

    if(!justClicked){
        for(street *Street : streetVector){
            isChosen(Street);
        }
    }



    sceneTime = sceneTime.addMSecs(500);
    ui->clock->setText(sceneTime.toString());


}
/**
 * @brief slot propojený s tlačítekm "+", slouží k přiblížení mapy
 */
void MainWindow::zoom_in()
{
    ui->graphicsView->scale(1.25, 1.25);
}

/**
 * @brief slot propojený s tlačítkem "-", slouží k oddálění mapy
 */
void MainWindow::zoom_out()
{
    ui->graphicsView->scale(0.8, 0.8);
}

/**
 * @brief slot propojený s tlačítkem "speed up", slouží ke zrychlení času
 */
void MainWindow::speed_up()
{
    //zrychlení

    interval /= 2;
    speed /= 1.2;
    timer->setInterval(interval);
}

/**
 * @brief slot propojený s tlačítkem "slow down", slouží ke zpomalení času
 */
void MainWindow::slow_down()
{
    interval *= 2;
    speed *= 1.2;
    timer->setInterval(interval);
}

/**
 * @brief slot probojený s tlačítkem "set time", slouží ke změně času
 */
void MainWindow::time_change()
{



    sceneTime = ui->timeEdit->time();
    for (int i = vehicleVector.size() - 1; i >= 0; i--) {
        delete vehicleVector[i]->getGraphics()[0];
        vehicleVector.remove(i);
    }

    spawnVehicles();
}

/**
 * @brief Slot propojený se zvětšovnáním zpoždění
 */

void MainWindow::delay_plus()
{
    if(chosenStreets.size() > 0){
        if(!chosenStreets[0]->getDelayed()){
            chosenStreets[0]->setDelayed(true);
            chosenStreets[0]->setDelay(chosenStreets[0]->getDelay() + 1000);
        }
        else{
            chosenStreets[0]->setDelay(chosenStreets[0]->getDelay() + 1000);
        }
    }
}

/**
 * @brief Slot propojený se zmenšováním zpoždění
 */

void MainWindow::delay_minus()
{
    if(chosenStreets.size() > 0){
        if(chosenStreets[0]->getDelayed() && chosenStreets[0]->getDelay() == 1000){
                chosenStreets[0]->setDelayed(false);
        }
        else if(chosenStreets[0]->getDelayed()){
            chosenStreets[0]->setDelay(chosenStreets[0]->getDelay() - 1000);
        }
    }
}

/**
 * @brief slot propojený se resetem zpoždění
 */

void MainWindow::delay_reset()
{
    if(chosenStreets.size() > 0){
        chosenStreets[0]->setDelay(0);
        chosenStreets[0]->setDelayed(false);
    }

}

/**
 * @brief slot spojení s uzavřením ulice
 */

void MainWindow::close_down()
{


    if(chosenStreets.size() > 0){
        chosenStreets[0]->setClosedDown(!chosenStreets[0]->getClosedDown());
        dynamic_cast<line*>(chosenStreets[0]->getGraphics()[0])->setClosed();
    }
}

/**
 * @brief slot spojený s nastavením objížďky
 */

void MainWindow::set_detour()
{
    if(chosenStreets.size() != 0)
    {
        QVector<street*> detourStreets;
        for(street *Street : streetVector){
            if(dynamic_cast<line*>(Street->getGraphics()[0])->getJustSetDet()){
                detourStreets.append(Street);
            }
        }

        for (busLine *lineS : lineVector) {
            int startIdx = 0;
            int continueIdx = 0;
            int idx = 0;
            for (stop *lineStop : lineS->getRoute()) {
                if(lineStop->getStreets()[0] == chosenStreets[0]){
                    QVector<stop*> swp = lineS->getRoute();
                    lineS->deleteStops();

                    for(int j = 0; !swp[j]->getStreets()[0]->getClosedDown(); j++){
                        if(swp[j]->getStreets()[0]->getEnd().getX() == detourStreets[0]->getStart().getX()
                        && swp[j]->getStreets()[0]->getEnd().getY() == detourStreets[0]->getStart().getY()){
                            startIdx = idx;
                        }
                        idx++;
                    }

                    for (int x = idx; x < swp.size(); x++){
                        if(!swp[x]->getStreets()[0]->getClosedDown()
                        && (swp[x]->getStreets()[0]->getStart().getX() == detourStreets[detourStreets.size() - 1]->getEnd().getX()
                        && swp[x]->getStreets()[0]->getStart().getY() == detourStreets[detourStreets.size() - 1]->getEnd().getY())){
                            continueIdx = idx;
                            break;
                        }
                        else if(!swp[x]->getStreets()[0]->getClosedDown()
                            && (swp[x]->getStreets()[0]->getStart().getX() == detourStreets[detourStreets.size() - 1]->getStart().getX()
                            && swp[x]->getStreets()[0]->getStart().getY() == detourStreets[detourStreets.size() - 1]->getStart().getY())){
                            continueIdx = idx;
                            //swp[x]
                            coordinate swpStart = detourStreets[detourStreets.size() - 1]->getStart();
                            detourStreets[detourStreets.size() - 1]->setStart(swp[x]->getStreets()[0]->getEnd());
                            detourStreets[detourStreets.size() - 1]->setEnd(swpStart);
                            detourStreets[detourStreets.size() - 1]->reverseStops();
                            break;
                        }
                        idx++;
                    }



                    for (int j = 0; j <= startIdx; ++j) {
                        //if(j < startIdx){
                        lineS->addStop(swp[j]);
                    }

                    for (int k = 0; k < detourStreets.size(); k++){
                        for(stop *streetStop : detourStreets[k]->getStop()){
                            lineS->addStop(streetStop);
                            dynamic_cast<line*>(lineS->getRoute()[lineS->getRoute().size() - 1]->getStreets()[0]->getGraphics()[0])->setDetour();

                        }
                    }

                    for (int l = continueIdx; l < swp.size(); l++){
                        lineS->addStop(swp[l]);
                    }

                    for(vehicle* vehPtr : vehicleVector){
                        if(vehPtr->getNumber() == lineS->getId()){

                            vehPtr->flushStops();
                            vehPtr->getJourney();
                            if(vehPtr->getWayBack()){
                                vehPtr->reverseVectors();
                            }
                            vehPtr->setStopNum();
                        }
                    }

                    for(street *strDet : streetVector){
                        dynamic_cast<line*>(strDet->getGraphics()[0])->setJustSetDet(false);
                    }


                }
            }
        }
    }
    else{
        QDialog *dialog = new QDialog;
        dialog->setWindowTitle("Error");
        QLabel *diaLabel = new QLabel(dialog);
        diaLabel->setMargin(20);
        diaLabel->setText("Street has to be chosen and closed before choosing detour.");
        diaLabel->adjustSize();
        dialog->show();
        for(street* streetS : streetVector){
            if(dynamic_cast<line*>(streetS->getGraphics()[0])->getJustSetDet()){
                dynamic_cast<line*>(streetS->getGraphics()[0])->unSetDetour();
            }
        }
    }

    for(street* streetS : streetVector){
        dynamic_cast<line*>(streetS->getGraphics()[0])->setJustSetDet(false);
    }


}


/* Nefunguje uplne*/

/**
 * @brief slot spojená s resetem uzavřením ulice
 */

void MainWindow::reset()
{


    if(chosenStreets.size() != 0)
    {
        if(chosenStreets[0]->getClosedDown()){
            for (busLine *line : lineVector) {
                bool thisOne = false;
                for(int i = 0; i < line->getOriginalStops().size(); i++){
                    if(line->getOriginalStops()[i]->getStreets()[0]->getName() == chosenStreets[0]->getName()){
                        chosenStreets[0]->setClosedDown(false);
                        dynamic_cast<class line*>(chosenStreets[0]->getGraphics()[0])->setClosed();
                        thisOne = true;
                    }
                }

                if(thisOne){
                    for (int i = 0; i < line->getRoute().size(); i++) {
                        if(dynamic_cast<class line*>(line->getRoute()[i]->getStreets()[0]->getGraphics()[0])->getDetour()){
                            dynamic_cast<class line*>(line->getRoute()[i]->getStreets()[0]->getGraphics()[0])->unSetDetour();
                        }
                    }

                    line->removeStops();
                    for (int i = 0; i < line->getOriginalStops().size(); i++) {
                        line->addStop(line->getOriginalStops()[i]);
                    }

                    for (vehicle *veh : vehicleVector) {
                        if(veh->getNumber() == line->getId()){
                            veh->flushStops();
                            veh->getJourney();
                            veh->setStopNum();

                        }
                    }
                    break;


                }

            }
        }

    }
}


/**
 * @brief funkce propojená s eventem změny velikosti okna, slouží ke změně velikosti obsahu
 * @param event event - změna velikosti okna (resize)
 * @details změna probíhá na základě roztažení do šířky, jelikož při kdybyUnchom scalovali i podle výšky, tak se mapa roztáhne nerovnoměrně což nechceme
 * @details změna se počítá jako poměr staré šířky k nové šířce
 */
void MainWindow::resizeEvent(QResizeEvent *event)
{


    static QSize old = QWidget::size();
    QSize size = QWidget::size();

    float width = (float)size.rwidth()/(float)old.rwidth();

    ui->graphicsView->scale(width, width);
    ui->route_info->scale(width, width);

    QList<QGraphicsItem*> items = ui->route_info->items();
    if(items.size()>1){
        for(QGraphicsItem *item : items){
            if(dynamic_cast<QGraphicsTextItem*>(item)){
              item->setScale(0.5);
            }
        }
    }
    old = size;
    QWidget::resizeEvent(event);

}

/**
 * @brief funcke sloužící k vykreslení objektů hlavní scény (mapy)
 * @param items vektor všech itemů které chceme vykreslit
 */
void MainWindow::drawStuff(QVector<QGraphicsItem*> items)
{
    for(QGraphicsItem* item : items){
        myScene->addItem(item);
    }
}

/**
 * @brief funkce, která zapne časovač
 * @details mimo jiné funkce spojuje slot \ref moveVeh, a při tiku posunje vozidla v mapě
 */
void MainWindow::timerStart()
{
    timer->setInterval(interval);
    connect(timer, SIGNAL(timeout()), this, SLOT(moveVeh()));
    timer->start(100);
}

void MainWindow::closeEvent(QCloseEvent *event)
{

    for (vehicle *Veh : vehicleVector) {
        if(Veh != nullptr){
            delete Veh->getGraphics()[0];
            delete Veh->getCoords();
            delete Veh;
        }
    }

    for (stop *Stop : stopVector) {
        delete Stop->getGraphics()[0];
        delete Stop->getCoord();
        delete Stop;
    }

    for (street *Street : streetVector) {
        delete Street->getGraphics()[0];
        delete Street;
    }

    for (busLine *line : lineVector) {

        delete line;
    }

    event->accept();

}

/**
 * @brief funkce pro vytvoření objektů mapového schématu na základě vstupních dat
 */
void MainWindow::deserialize()
{

    QFile timetable("../examples/timetable2.json");
    if(!timetable.open(QIODevice::ReadWrite))
        exit(1);

    QString timetableString = timetable.readAll();

    QJsonDocument timetableDoc;
    timetableDoc = QJsonDocument::fromJson(timetableString.toUtf8());
    QJsonArray timetableArray = timetableDoc.array();

    QFile input("../examples/map_base2.json");
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
        streetVector.append(new street(start, end, name));
        streetVector[streetVector.size() - 1]->setGraphics();
        drawStuff(streetVector[streetVector.size() - 1]->getGraphics());


    }

    /* STOPS */
    for(QJsonValue stopVal : stops){
        QJsonObject stopObj = stopVal.toObject();
        QString name = stopObj.find("name").value().toString();
        coordinate stopCoord = coordinate(stopObj.find("x").value().toDouble(), stopObj.find("y").value().toDouble());
        QJsonArray streetArray = stopObj.find("street name")->toArray();

        stopVector.append(new stop(stopObj.find("name").value().toString(), stopCoord));
        stopVector[stopVector.size() - 1]->setGraphics();
        drawStuff(stopVector[stopVector.size() - 1]->getGraphics());

        for (street *streetStop : streetVector) {
            for (QJsonValue streetName : streetArray) {
                if(streetStop->getName() == streetName.toString()){
                    stopVector[stopVector.size() - 1]->setStreet(streetStop);
                }
            }

        }
    }


    for (street *streetS : streetVector) {
        for (stop *stopS : stopVector) {
            if(stopS->getStreets()[0]->getName() == streetS->getName()){
                streetS->addStop(stopS);
            }
        }
    }


    // LINES /
    for (QJsonValue lineVal : lines) {
       QJsonObject lineObj = lineVal.toObject();
       int number = lineObj.find("number")->toInt();
       QJsonArray stops = lineObj.find("stops")->toArray();
       lineVector.append(new busLine(number));
       for (stop *lineStop : stopVector) {
            for(QJsonValue stopName : stops){
                if(stopName.toString() == lineStop->getStopName()){
                    lineVector[lineVector.size() - 1]->addStop(lineStop);
                    lineVector[lineVector.size() - 1]->addOriginalStops(*lineStop);
                }
            }
       }
       QJsonObject testObj;
       for (int i = 0; i < timetableArray.size(); i++) {
           testObj = timetableArray[i].toObject();
           if(testObj.find(QString::number(lineVector[lineVector.size() - 1]->getId())) != testObj.end()){
               lineVector[lineVector.size() - 1]->generateStopTimes(testObj.find(QString::number(lineVector[lineVector.size() - 1]->getId())).value().toArray());
           }
       }

       lineVector[lineVector.size() - 1]->setOriginalStopVec();
    }



    spawnVehicles();

    ui->graphicsView->scale(0.41, 0.41);
}

/**
 * @brief funkce sloužící k vytvoření vozidel v daný čas
 */
void MainWindow::spawnVehicles(){
    // VEHICLES /
    for (int i = 0; i < lineVector.size(); ++i) {
        vehicle blankVeh(*lineVector[i]->getRoute()[0]->getCoord(), -200);
        blankVeh.setLine(lineVector[i]);
        blankVeh.getJourney();
        QTime duration = lineVector[i]->getDuration(blankVeh.getFullJourney().size());
        QTime swpSceneTime = sceneTime.addSecs((-duration.second() - duration.minute() * 60 - duration.hour() * 3600)*2);

        QVector<QVector<QTime*>> stopTimes = lineVector[i]->getStopTime(0);
        if(swpSceneTime < sceneTime){
            for (int k = swpSceneTime.hour(); k <= sceneTime.hour(); ++k) {
                for (int j = 0; j < stopTimes[k].size(); ++j) {
                    if(*stopTimes[k][j] > swpSceneTime && *stopTimes[k][j] < sceneTime){
                        QTime travelledTime = sceneTime.addSecs(-stopTimes[k][j]->hour() * 3600 -stopTimes[k][j]->minute() * 60 -stopTimes[k][j]->second());
                        double travelledMinsToDouble = travelledTime.minute() + (double)((double)travelledTime.second() / 60.0);
                        double durationMinsToDouble = duration.minute() + (double)((double)duration.second() / 60.0);
                        double travelRatio = travelledMinsToDouble / durationMinsToDouble;

                        int position = blankVeh.getFullJourney().size() * travelRatio;


                        if(travelRatio > 1){
                            position = blankVeh.getFullJourney().size() * (travelRatio - 1);
                        }

                        vehicle *newVehicle = new vehicle(blankVeh.getFullJourney()[position], lineVector[i]->getId());


                        newVehicle->setLine(lineVector[i]);
                        newVehicle->setJourneyPos(position);
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
        else{

            for (int k = swpSceneTime.hour(); k <= 23; ++k) {
                for (int j = 0; j < stopTimes[k].size(); ++j) {
                    if(*stopTimes[k][j] > swpSceneTime && *stopTimes[k][j] < QTime(23,59,59)){
                        QTime travelledTime = sceneTime.addSecs(-stopTimes[k][j]->hour() * 3600 -stopTimes[k][j]->minute() * 60 -stopTimes[k][j]->second());


                        double travelledMinsToDouble = travelledTime.minute() + (double)((double)travelledTime.second() / 60.0);
                        double durationMinsToDouble = duration.minute() + (double)((double)duration.second() / 60.0);

                        double travelRatio = travelledMinsToDouble / durationMinsToDouble;

                        int position = blankVeh.getFullJourney().size() * travelRatio;


                        if(travelRatio > 1){
                            position = blankVeh.getFullJourney().size() * (travelRatio - 1);
                        }

                        vehicle *newVehicle = new vehicle(blankVeh.getFullJourney()[position], lineVector[i]->getId());


                        newVehicle->setLine(lineVector[i]);
                        newVehicle->setJourneyPos(position);
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

            for (int k = 0; k <= sceneTime.hour(); ++k) {
                for (int j = 0; j < stopTimes[k].size(); ++j) {
                    if(*stopTimes[k][j] >= QTime(0,0,0) && *stopTimes[k][j] < sceneTime){
                        QTime travelledTime = sceneTime.addSecs(-stopTimes[k][j]->hour() * 3600 -stopTimes[k][j]->minute() * 60 -stopTimes[k][j]->second());


                        double travelledMinsToDouble = travelledTime.minute() + (double)((double)travelledTime.second() / 60.0);
                        double durationMinsToDouble = duration.minute() + (double)((double)duration.second() / 60.0);
                        double travelRatio = travelledMinsToDouble / durationMinsToDouble;

                        int position = blankVeh.getFullJourney().size() * travelRatio;


                        if(travelRatio > 1){
                            position = blankVeh.getFullJourney().size() * (travelRatio - 1);
                        }

                        vehicle *newVehicle = new vehicle(blankVeh.getFullJourney()[position], lineVector[i]->getId());


                        newVehicle->setLine(lineVector[i]);
                        newVehicle->setJourneyPos(position);
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
    }
}

/**
 * @brief funkce sloužící k vytvoření celého okna
 */
void MainWindow::initScene()
{
    myScene = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(myScene);
    coordinate testCoord(150, 150);
    deserialize();
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    timerStart();

}





