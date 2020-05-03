#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QGraphicsItem>

#include "busline.h"
#include "coordinate.h"
#include "stop.h"
#include "street.h"
#include "vehicle.h"

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

private:
    Ui::MainWindow *ui;
    void initScene();


    QVector<busLine> lineVector;
    QVector<street> streetVector;
    QVector<stop> stopVector;
    QVector<vehicle> vehicleVector;
};
#endif // MAINWINDOW_H
