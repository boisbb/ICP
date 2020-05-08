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
private slots:
    void onValueChange(int val);
    void showInfo(vehicle veh, bool check, bool was);
    void moveVeh();
    void zoom_in();
    void zoom_out();
    void speed_up();
    void slow_down();
    void time_change();

protected:
    virtual void resizeEvent(QResizeEvent *event);

private:
    Ui::MainWindow *ui;
    void initScene();
    void drawStuff(QVector<QGraphicsItem*> items);
    void timerStart();
    void see_info();//v dolním místě bude ukazovat informace o zvoleném vozidle
    void draw_stops(QGraphicsScene *scene);


    QTime sceneTime = QTime(QTime::currentTime().hour(),QTime::currentTime().minute(), round(QTime::currentTime().second()));
    double interval = 500;
    double speed = 1000;
    QVector<busLine> lineVector;
    QVector<street> streetVector;
    QVector<stop> stopVector;
    QVector<vehicle*> vehicleVector;
    scene *myScene;
    QTimer *timer = new QTimer(this);
    void deserialize();
    void spawnVehicles();
    QGraphicsEllipseItem *infoVehicle;
};
#endif // MAINWINDOW_H
