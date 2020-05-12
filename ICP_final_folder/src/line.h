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
    void unSetDetour();
    bool getDetour();
    void unClose();
    bool getJustSetDet() const;
    void setJustSetDet(bool value);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    street *lineStreet;
    bool chosen = false;
    bool closed = false;
    bool detour = false;
    bool justSetDet = false;

};

#endif // LINE_H
