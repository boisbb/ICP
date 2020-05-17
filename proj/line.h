#ifndef LINE_H
#define LINE_H

#include <QGraphicsLineItem>

class street;

class line : public QGraphicsLineItem
{
public:
    void setLineStreet(street *value);
    void Choose();
    void unChoose();
    bool getChosen();
    void setClosed();
    void setDetour();
    void unSetDetour();
    bool getDetour();
    void unClose();
    bool getJustSetDet() const;
    void setJustSetDet(bool value);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    /**
     * @brief ulice přímky
     */
    street *lineStreet;
    /**
     * @brief určuje, zda je přímka vybraná
     */
    bool chosen = false;
    /**
     * @brief určuje, zda je přímka zavřená
     */
    bool closed = false;
    /**
     * @brief určuje, zda je přímka objížďkou
     */
    bool detour = false;
    /**
     * @brief určuje, zda byl přímka právě pro objížďku
     */
    bool justSetDet = false;

};

#endif // LINE_H
