#ifndef _GV
#define _GV
#include <QtGui/QGraphicsView>
#include <QtGui/QGraphicsScene>
//#include "vertex.h"
#include <math.h>
#include <QtGui/QWheelEvent>
#include <list>
#include <utility>
#include <QtCore/QMutexLocker>
#include <iostream>

#include <QtCore/QMutex>
extern QMutex mutex;
using namespace std;
class GraphWidget : public QGraphicsView {
    Q_OBJECT
public:
    int N;
    int i;
    QGraphicsScene *scene;
//     list<pair<int, int> > &exchange;
    GraphWidget(list<pair<int,int> > &exchange, int maxWidthInLeafes=32, QWidget *parent=0);
    void add(QGraphicsItem *n);
    void timerEvent(QTimerEvent *event);

    void scaleView(qreal scaleFactor);
    void keyPressEvent(QKeyEvent *event);
    void zoomIn();
    void zoomOut();
    void wheelEvent(QWheelEvent *event);
};
#endif
