#include "line.h"
#include "street.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QPen>


/**
 * @brief event handler pro zachycení klikání na přímku
 * @param event
 */

void line::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        chosen = !chosen;
        event->ignore();
    }
    else if(event->button() == Qt::RightButton){

        QPen pen;
        if(justSetDet)
            pen.setColor(QColor(160,160,160));
        else
            pen.setColor(QColor(255, 255, 0));
        justSetDet = !justSetDet;
        pen.setWidth(2);
        setPen(pen);
    }
    //lineStreet-
}

/**
 * @brief getter boolu, který indikuje, že zrovna byla zmáčknutá přímka
 * @return vrací true pokud byl, jinak vrací false
 */

bool line::getJustSetDet() const
{
    return justSetDet;
}

/**
 * @brief setter boolu, který indikuje, že zrovna byla zmáčknutá přímka
 * @param value hodnota k nastavení
 */

void line::setJustSetDet(bool value)
{
    if(justSetDet){
        QPen pen;
        pen.setColor(QColor(120,0,0));
        setPen(pen);
    }

    justSetDet = value;

}

/**
 * @brief nastavení ulice přímky
 * @param value ulice k natavení
 */

void line::setLineStreet(street *value)
{
    lineStreet = value;
}

/**
 * @brief vybere přímku
 */

void line::Choose()
{
    QPen pen;
    if(chosen && !lineStreet->getClosedDown())
        pen.setColor(QColor(255,0,0));
    else if(!lineStreet->getClosedDown())
        pen.setColor(QColor(160, 160, 160));
    else if(lineStreet->getClosedDown()){
        pen.setColor(QColor(255, 0, 0));
        pen.setStyle(Qt::DashDotLine);
    }

    pen.setWidth(2);
    this->setPen(pen);
}

/**
 * @brief odebere linku
 */

void line::unChoose()
{
    chosen = false;

    QPen pen;
    if(detour)
            pen.setColor(QColor(255, 255, 0));
    else if(!lineStreet->getDelayed() && !lineStreet->getClosedDown())
        pen.setColor(QColor(160, 160, 160));
    else if(lineStreet->getDelayed())
        pen.setColor(QColor(150,20,0));
    else if(lineStreet->getClosedDown()){
        pen.setColor(QColor(160, 160, 160));
        pen.setStyle(Qt::DashDotLine);
    }
    pen.setWidth(2);
    setPen(pen);
}

/**
 * @brief zjistí zda byla vybrána daná přímka
 * @return vrátí true pokud byla vybrána, jinak false
 */

bool line::getChosen()
{
    return chosen;
}


/**
 * @brief nastaví přímku jako zavřenou
 */

void line::setClosed()
{
    QPen pen;
    if(!closed){
        closed = !closed;
        pen.setColor(QColor(255, 0, 0));
        pen.setStyle(Qt::DashDotLine);
    }
    else{
        closed = !closed;
        pen.setColor(QColor(255, 0, 0));
        pen.setStyle(Qt::SolidLine);
    }
    pen.setWidth(2);
    setPen(pen);
}

/**
 * @brief nastaví přímku jako objížďku
 */

void line::setDetour()
{


    detour = !detour;
}

/**
 * @brief odnastaví přímku jako objížďku
 */

void line::unSetDetour()
{
    detour = false;
    QPen pen;
    pen.setColor(QColor(160, 160, 160));

    setPen(pen);

}

/**
 * @brief zjistí, zda je přímka objížďkou
 * @return true pokude je objížďkou, jinak false
 */

bool line::getDetour()
{
    return detour;
}

/**
 * @brief otevře zpět přímku - ulici
 */

void line::unClose()
{
    QPen pen;
    closed = !closed;
    if(chosen)
        pen.setColor(QColor(255, 0, 0));
    else
        pen.setColor(QColor(160, 160, 160));
    pen.setWidth(2);
    pen.setStyle(Qt::SolidLine);
    setPen(pen);
}
