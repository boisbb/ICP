/*!
 * @file
 * @brief Tento soubor obsahuje třídu \ref MainWindow
 *
 * @author Boris Burkalo (xburka00), Jan Klusáček (xklusa14)
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QGraphicsItem>
#include <QTimer>
#include <QWidget>//resize
#include <cmath>

#include "busline.h"
#include "coordinate.h"
#include "stop.h"
#include "street.h"
#include "vehicle.h"
#include "scene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void isChosen(street *streetInst);
private slots:
    void showInfo(vehicle *veh, bool was);
    void moveVeh();
    void zoom_in();
    void zoom_out();
    void speed_up();
    void slow_down();
    void time_change();
    void delay_plus();
    void delay_minus();
    void delay_reset();
    void close_down();
    void set_detour();
    void reset();

protected:
    virtual void resizeEvent(QResizeEvent *event);

private:
    /**
     * @brief celé okno
     */
    Ui::MainWindow *ui;
    void initScene();
    void drawStuff(QVector<QGraphicsItem*> items);
    void timerStart();
    void see_info();//v dolním místě bude ukazovat informace o zvoleném vozidle
    void draw_stops(QGraphicsScene *scene);
    void isChosen(street streetInst);

    /**
     * @brief čas scény, vychází z reálného času při spuštění
     */
    QTime sceneTime = QTime(QTime::currentTime().hour(),QTime::currentTime().minute(), round(QTime::currentTime().second()));

    /**
     * @brief čas v ms po kterém se aktualizuje timer
     */
    double interval = 500;

//TODO smazat
    double speed = 1000;

    /**
     * @brief vektor linek
     */
    QVector<busLine> lineVector;

    /**
     * @brief vektor ulic
     */
    QVector<street*> streetVector;

    /**
     * @brief vektor zastávek
     */
    QVector<stop> stopVector;

    /**
     * @brief vektor vozidel
     */
    QVector<vehicle*> vehicleVector;

    /**
     * @brief hlavní scéna (mapa)
     */
    scene *myScene;

    /**
     * @brief měřič času, slouží k aktualizaci scény a pohybu v ní
     */
    QTimer *timer = new QTimer(this);
    void deserialize();
    void spawnVehicles();

    /**
     * @brief vozidlo v informačním boxu dole
     */
    QGraphicsEllipseItem *infoVehicle;
    QVector<street*> chosenStreets;
    bool justClicked = false;
};
#endif // MAINWINDOW_H
