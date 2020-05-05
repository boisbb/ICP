#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QGraphicsItem>
#include <QTimer>

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
    void moveVeh();
    void zoom_in();
    void zoom_out();
    void speed_up();
    void slow_down();

private:
    Ui::MainWindow *ui;
    void initScene();
    void drawStuff(QVector<QGraphicsItem*> items);
    void timerStart();


    QTime sceneTime = QTime::currentTime();
    double interval = 500;
    QVector<busLine> lineVector;
    QVector<street> streetVector;
    QVector<stop> stopVector;
    QVector<vehicle> vehicleVector;
    scene *myScene;
    QTimer *timer = new QTimer(this);
    void deserialize();
};
#endif // MAINWINDOW_H
