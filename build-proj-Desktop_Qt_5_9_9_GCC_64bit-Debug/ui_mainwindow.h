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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QGraphicsView *graphicsView_2;
    QVBoxLayout *verticalLayout_4;
    QPushButton *speed_up;
    QPushButton *slow_down;
    QPushButton *button_plus;
    QPushButton *button_minus;
    QGraphicsView *graphicsView;
    QLabel *clock;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(619, 459);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        graphicsView_2 = new QGraphicsView(centralwidget);
        graphicsView_2->setObjectName(QStringLiteral("graphicsView_2"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(graphicsView_2->sizePolicy().hasHeightForWidth());
        graphicsView_2->setSizePolicy(sizePolicy);
        graphicsView_2->setMaximumSize(QSize(16777215, 90));

        verticalLayout_2->addWidget(graphicsView_2);


        gridLayout->addLayout(verticalLayout_2, 2, 0, 1, 1);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        speed_up = new QPushButton(centralwidget);
        speed_up->setObjectName(QStringLiteral("speed_up"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(speed_up->sizePolicy().hasHeightForWidth());
        speed_up->setSizePolicy(sizePolicy1);

        verticalLayout_4->addWidget(speed_up);

        slow_down = new QPushButton(centralwidget);
        slow_down->setObjectName(QStringLiteral("slow_down"));
        sizePolicy1.setHeightForWidth(slow_down->sizePolicy().hasHeightForWidth());
        slow_down->setSizePolicy(sizePolicy1);

        verticalLayout_4->addWidget(slow_down, 0, Qt::AlignTop);

        button_plus = new QPushButton(centralwidget);
        button_plus->setObjectName(QStringLiteral("button_plus"));
        sizePolicy1.setHeightForWidth(button_plus->sizePolicy().hasHeightForWidth());
        button_plus->setSizePolicy(sizePolicy1);

        verticalLayout_4->addWidget(button_plus, 0, Qt::AlignBottom);

        button_minus = new QPushButton(centralwidget);
        button_minus->setObjectName(QStringLiteral("button_minus"));
        sizePolicy1.setHeightForWidth(button_minus->sizePolicy().hasHeightForWidth());
        button_minus->setSizePolicy(sizePolicy1);

        verticalLayout_4->addWidget(button_minus);


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
        clock->setLayoutDirection(Qt::LeftToRight);
        clock->setFrameShape(QFrame::Box);
        clock->setFrameShadow(QFrame::Plain);

        gridLayout->addWidget(clock, 2, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        speed_up->setText(QApplication::translate("MainWindow", "speed up", Q_NULLPTR));
        slow_down->setText(QApplication::translate("MainWindow", "slow down", Q_NULLPTR));
        button_plus->setText(QApplication::translate("MainWindow", "+", Q_NULLPTR));
        button_minus->setText(QApplication::translate("MainWindow", "-", Q_NULLPTR));
        clock->setText(QApplication::translate("MainWindow", "HODINY", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
