#include <QtGui/QGraphicsItem>
#include <QtGui/QPainter>
//#include <QRectF>

class Vertex: public QGraphicsItem {
    //Q_OBJECT
     public:
     int posx, posy;
     Vertex(int posx, int posy): posx(posx),posy(posy) {
     }
    QRectF boundingRect() const;
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);
};
