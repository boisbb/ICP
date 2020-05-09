#ifndef LINE_H
#define LINE_H

#include <QGraphicsLineItem>

class street;

class line : public QGraphicsLineItem
{
public:
    void setLineStreet(street *value);
    void unChoose();
    bool getChosen();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    street *lineStreet;
    bool chosen = false;

};

#endif // LINE_H
