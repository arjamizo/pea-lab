#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>
#include <QGraphicsScene>


using namespace std;
class GraphWidget : public QGraphicsView
{
    Q_OBJECT
    public:
    int N,i;
    QGraphicsScene *scene;
    GraphWidget(int maxWidthInLeafes=32, QWidget *parent=0);
    void add(QGraphicsItem *n);
    void timerEvent(QTimerEvent *event);

    void scaleView(qreal scaleFactor);
    void keyPressEvent(QKeyEvent *event);
    void zoomIn();
    void zoomOut();
    void wheelEvent(QWheelEvent *event);

    protected:
    private:
};

#endif // GRAPHWIDGET_H
