/*!
 * @file
 * @brief Tento soubor obsahuje funkci main
 *
 * @author Boris Burkalo (xburka00), Jan Klusáček (xklusa14)
 */
#include "mainwindow.h"

#include <QApplication>
/**
 * @brief hlavní funkce, která spouští program
 * @param argc
 * @param argv
 * @return kód chyby, v případě úspěchu 0
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
