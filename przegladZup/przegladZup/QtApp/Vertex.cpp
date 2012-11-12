#include "Vertex.h"

 QRectF Vertex::boundingRect() const
 {
         return QRectF(0,0, 10, 10);
 }
     void Vertex::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) {
         //painter->setPen(Qt::NoPen);
         QRectF rec(posx,posy,10,10);
         QBrush brush(Qt::red);
         painter->fillRect(rec, brush);
         painter->drawRect(rec);
     }
