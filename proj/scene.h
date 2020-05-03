#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>


class scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit scene(QObject *parent = nullptr);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QGraphicsLineItem *editedLine{nullptr};
};

#endif // SCENE_H
