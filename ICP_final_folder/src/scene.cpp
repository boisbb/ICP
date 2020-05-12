#include "scene.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>

scene::scene(QObject *parent) : QGraphicsScene(parent)
{

}

void scene::mousePressEvent(QGraphicsSceneMouseEvent *event){



    QGraphicsScene::mousePressEvent(event);
}


void scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){

    QGraphicsScene::mouseMoveEvent(event);

}

void scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){

    QGraphicsScene::mouseReleaseEvent(event);
}
