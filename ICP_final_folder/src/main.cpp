/*!
 * @file
 * @brief Tento soubor obsahuje funkci main
 *
 * @author Boris Burkalo (xburka00), Jan Klusáček (xklusa14)
 */
#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>
/*
 * @brief hlavní funkce, která spouští program
 * @param argc
 * @param argv
 * @return kód chyby, v případě úspěchu 0
 */

/*!
 * \mainpage
 * Legenda:
 * @image html app.png
 * <b>speedUp</b> - tlačítko na zrychlení času simulace<br>
 * <b>slowDown</b> - tlačítko na zpomalení času simulace<br>
 * <b>delay + </b> - tlačítko na přidání zácpy na dané ulici (vyžaduje zakliknutou ulici)<br>
 * <b>delay - </b> - tlačítko na odebrání zácpy na dané ulici (vyžaduje zakliknutou ulici)<br>
 * <b>reset delay </b> - tlačítko na nastavení normálního provozu una dané ulici (vyžaduje zakliknutou ulici)<br>
 * <b>+</b> - tlačítko sloužící pro zoom (zvětšení)<br>
 * <b>-</b> - tlačítko sloužící pro zoom (zmenšení)<br>
 * <b>časové okénko</b> - slouží pro nastavení času scény, musí se potvrdit tlačítkem <b>set time</b><br>
 * <b>set time</b> - tlačítko sloužící pro potvrzení nastvení času zadaného v předchozím okénku<br>
 * <br>
 * <b>hlavní okno</b> - zobrazuje mapu a spoje na ní<br>
 * <b>info box</b> - po kliknutí na autobus zobrazí bližší informace (všechny zastávky, a místo na trase, kde so zrovna autobus nachází, číslo linky)<br>
 * <b>hodiny</b> - zobrazuje simulovaný čas (při spuštění vychází z réálného času)<br>
 * <br>
 * <b>info box - detail:</b>
 * @image html DOPLNIT
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file(":/dark.qss");
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream stream(&file);
    a.setStyleSheet(stream.readAll());

    MainWindow w;
    w.show();
    return a.exec();
}
