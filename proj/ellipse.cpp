/*!
 * @file
 * @brief Tento soubor obsahuje implementaci třídy ellipse
 *
 * @author Boris Burkalo (xburka00), Jan Klusáček (xklusa14)
 */
#include "ellipse.h"
#include <QDebug>

/**
 * @brief TODO funkce pro nastavení vozidla
 * @param ellVeh vozidlo
 */
void ellipse::setVehicle(vehicle *ellVeh)
{
    ellipseVehicle = ellVeh;
}

/**
 * @brief funkce, sloužící pro zachycení eventu kliknutí na vozidlo
 * @param event event - kliknutí
 * @details pokud se ve scéně klikne na vozidlo, pak se mu nastvaví flag clicked
 */
void ellipse::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    static bool clicked = false;

    if(ellipseVehicle){
        //TODO překlikávání když bude víc vozidel
        if(ellipseVehicle->getClicked()){
            ellipseVehicle->setClicked(false);
        }
        else{
            ellipseVehicle->setClicked(true);
        }
    }
}
