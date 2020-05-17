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
 * <b>delay +</b> - tlačítko na přidání zácpy na dané ulici (vyžaduje zakliknutou ulici)<br>
 * <b>delay -</b> - tlačítko na odebrání zácpy na dané ulici (vyžaduje zakliknutou ulici)<br>
 * <b>reset delay</b> - tlačítko na nastavení normálního provozu una dané ulici (vyžaduje zakliknutou ulici)<br>
 * <b>close down</b> - tlačítko sloužící pro uzavření ulice (vyžaduje zakliknutou ulici)<br>
 * <b>set detour</b> - tlačítko sloužící pro nastavení objížďky (objížďka se musí manuálně navolit, narozdíl od volení ulice levým tlačítkem se objídka volí pravým tlačítkem <br>
 * <b>reset</b> - tlačítko sloužící pro zrušení objížďek a zavřených ulic<br>
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
 * @image html infobox.png
 * <b>Jízdní řád dané zastávky (první číslo je hodina):</b><br>
 * Zobrazí se při kliknutí na zastávku v info boxu
 * @image html timetable.png
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    return a.exec();
}
