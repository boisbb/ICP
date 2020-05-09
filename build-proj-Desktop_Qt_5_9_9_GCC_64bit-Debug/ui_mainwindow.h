/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_4;
    QPushButton *speed_up;
    QPushButton *slow_down;
    QPushButton *delay_plus;
    QPushButton *delay_minus;
    QPushButton *delay_reset;
    QPushButton *button_plus;
    QPushButton *button_minus;
    QTimeEdit *timeEdit;
    QPushButton *time_changer;
    QGraphicsView *graphicsView;
    QLabel *clock;
    QVBoxLayout *verticalLayout_2;
    QGraphicsView *route_info;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(619, 459);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        speed_up = new QPushButton(centralwidget);
        speed_up->setObjectName(QStringLiteral("speed_up"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(speed_up->sizePolicy().hasHeightForWidth());
        speed_up->setSizePolicy(sizePolicy);

        verticalLayout_4->addWidget(speed_up);

        slow_down = new QPushButton(centralwidget);
        slow_down->setObjectName(QStringLiteral("slow_down"));
        sizePolicy.setHeightForWidth(slow_down->sizePolicy().hasHeightForWidth());
        slow_down->setSizePolicy(sizePolicy);

        verticalLayout_4->addWidget(slow_down, 0, Qt::AlignTop);

        delay_plus = new QPushButton(centralwidget);
        delay_plus->setObjectName(QStringLiteral("delay_plus"));

        verticalLayout_4->addWidget(delay_plus);

        delay_minus = new QPushButton(centralwidget);
        delay_minus->setObjectName(QStringLiteral("delay_minus"));

        verticalLayout_4->addWidget(delay_minus);

        delay_reset = new QPushButton(centralwidget);
        delay_reset->setObjectName(QStringLiteral("delay_reset"));

        verticalLayout_4->addWidget(delay_reset);

        button_plus = new QPushButton(centralwidget);
        button_plus->setObjectName(QStringLiteral("button_plus"));
        sizePolicy.setHeightForWidth(button_plus->sizePolicy().hasHeightForWidth());
        button_plus->setSizePolicy(sizePolicy);

        verticalLayout_4->addWidget(button_plus, 0, Qt::AlignBottom);

        button_minus = new QPushButton(centralwidget);
        button_minus->setObjectName(QStringLiteral("button_minus"));
        sizePolicy.setHeightForWidth(button_minus->sizePolicy().hasHeightForWidth());
        button_minus->setSizePolicy(sizePolicy);

        verticalLayout_4->addWidget(button_minus);

        timeEdit = new QTimeEdit(centralwidget);
        timeEdit->setObjectName(QStringLiteral("timeEdit"));
        sizePolicy.setHeightForWidth(timeEdit->sizePolicy().hasHeightForWidth());
        timeEdit->setSizePolicy(sizePolicy);

        verticalLayout_4->addWidget(timeEdit);

        time_changer = new QPushButton(centralwidget);
        time_changer->setObjectName(QStringLiteral("time_changer"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(time_changer->sizePolicy().hasHeightForWidth());
        time_changer->setSizePolicy(sizePolicy1);

        verticalLayout_4->addWidget(time_changer);


        gridLayout->addLayout(verticalLayout_4, 0, 1, 1, 1);

        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(graphicsView, 0, 0, 1, 1);

        clock = new QLabel(centralwidget);
        clock->setObjectName(QStringLiteral("clock"));
        QFont font;
        font.setFamily(QStringLiteral("Ubuntu"));
        font.setPointSize(14);
        clock->setFont(font);
        clock->setLayoutDirection(Qt::RightToLeft);
        clock->setFrameShape(QFrame::Box);
        clock->setFrameShadow(QFrame::Plain);
        clock->setTextFormat(Qt::AutoText);
        clock->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(clock, 2, 1, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        route_info = new QGraphicsView(centralwidget);
        route_info->setObjectName(QStringLiteral("route_info"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(route_info->sizePolicy().hasHeightForWidth());
        route_info->setSizePolicy(sizePolicy3);
        route_info->setMinimumSize(QSize(0, 130));
        route_info->setMaximumSize(QSize(16777215, 90));

        verticalLayout_2->addWidget(route_info, 0, Qt::AlignTop);


        gridLayout->addLayout(verticalLayout_2, 2, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        speed_up->setText(QApplication::translate("MainWindow", "speed up", Q_NULLPTR));
        slow_down->setText(QApplication::translate("MainWindow", "slow down", Q_NULLPTR));
        delay_plus->setText(QApplication::translate("MainWindow", "Delay +", Q_NULLPTR));
        delay_minus->setText(QApplication::translate("MainWindow", "Delay -", Q_NULLPTR));
        delay_reset->setText(QApplication::translate("MainWindow", "Reset Delay", Q_NULLPTR));
        button_plus->setText(QApplication::translate("MainWindow", "+", Q_NULLPTR));
        button_minus->setText(QApplication::translate("MainWindow", "-", Q_NULLPTR));
        time_changer->setText(QApplication::translate("MainWindow", "Nastavit \304\215as", Q_NULLPTR));
        clock->setText(QApplication::translate("MainWindow", "HODINY", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
