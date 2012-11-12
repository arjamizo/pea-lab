#include "GraphWidget.h"
#include <QGraphicsItem>
#include <QTimerEvent>
#include <QKeyEvent>
#include <QWheelEvent>
#include <utility>
#include <list>
#include <iostream>
#include "Vertex.h"
#include <math.h>

using namespace std;

GraphWidget::GraphWidget(int maxWidthInLeafes, QWidget *parent)
    : QGraphicsView(parent),N(maxWidthInLeafes)
    //,exchange(exchange)
{
    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    //scene->setSceneRect(-200, -200, 400, 400);
    scale(qreal(0.8), qreal(0.8));
    setMinimumSize(400, 400);
//         fitInView();
    setScene(scene);
    i=0;
    add(new Vertex(11*i,0));
    i++;
}

void GraphWidget::add(QGraphicsItem *n) {
    scene->addItem(n);
}
void GraphWidget::timerEvent(QTimerEvent *event) {
    add(new Vertex(11*i,0));
    i++;
    cout<<i<<endl;
    //update();
    viewport()->update();
    //QMutexLocker locker(&mutex);
    //locker.unlock();
}

void GraphWidget::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Up:
        //centerNode->moveBy(0, -20);
        timerEvent(0);
        break;
    }
}
void GraphWidget::scaleView(qreal scaleFactor) {
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}
void GraphWidget::zoomIn() {
    scaleView(qreal(1.2));
}

void GraphWidget::zoomOut() {
    scaleView(1 / qreal(1.2));
}

void GraphWidget::wheelEvent(QWheelEvent *event) {
    scaleView(pow((double)2, -event->delta() / 240.0));
}
