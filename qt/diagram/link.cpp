#include <QtGui>
#include <QStyleOptionGraphicsItem>

#include "link.h"
#include "node.h"

Link::Link(Node *fromNode, Node *toNode)
{
    myFromNode = fromNode;
    myToNode = toNode;

    myFromNode->addLink(this);
    myToNode->addLink(this);

    setFlags(QGraphicsItem::ItemIsSelectable);
    setZValue(-1);

    setColor(Qt::darkRed);
    trackNodes();
}

Link::~Link()
{
    myFromNode->removeLink(this);
    myToNode->removeLink(this);
}

Node *Link::fromNode() const
{
    return myFromNode;
}

Node *Link::toNode() const
{
    return myToNode;
}

void Link::setColor(const QColor &color)
{
    setPen(QPen(color, 1.0));
}

QColor Link::color() const
{
    return pen().color();
}

void Link::trackNodes()
{
    setLine(QLineF(myFromNode->pos(), myToNode->pos()));
}

namespace {
void drawArrowLine(QPainter &painter, const QPointF &p1, const QPointF &p2) // from p1 to p2
{
    painter.drawLine(p1, p2);
    if (p1 == p2)
        return;

    QPointF pm((p1.x()+p2.x())/2, (p1.y()+p2.y())/2); // p1和p2的中点
    int width = 10;     // 箭头宽度
    int length = 12;    // 箭头长度
    QPointF pa, pb, pc;  // pa为箭头顶点, pb, pc为两边的顶点
    double sin1, cos1, sin2, cos2;
    if (p1.x() == p2.x()) {         // 垂直直线
        cos1 = 0;
        sin1 = p1.y() < p2.y() ? 1 : -1;
        cos2 = 1;
        sin2 = 0;
    } else if (p1.y() == p2.y()) {  // 水平直线
        cos1 = p1.x() < p2.x() ? 1 : -1;
        sin1 = 0;
        cos2 = 0;
        sin2 = 1;
    } else {                        // 斜直线
        // 直线斜率
        double k1 = ((double) (p2.y() - p1.y())) / ((double) (p2.x() - p1.x()));
        double k2 = -1 / k1;    // 法线斜率

        // k = tan, cos = +-sqrt(1/(1+k*k)), sin = +-sqrt(k*k/(1+k*k));
        cos1 = (p1.x() < p2.x() ? 1 : -1) * sqrt(1 / (1 + k1*k1));
        sin1 = (p1.y() < p2.y() ? 1 : -1) * sqrt((k1 * k1) / (1 + k1*k1));
        cos2 = sqrt(1 / (1 + k2*k2));
        sin2 = (k2 > 0 ? 1 : -1) * sqrt((k2 * k2) / (1 + k2*k2));
    }

    pa.setX(cos1*length+pm.x());
    pa.setY(sin1*length+pm.y());
    pb.setX(cos2*width/2+pm.x());
    pb.setY(sin2*width/2+pm.y());   // (pb.y - pm.y) / (width/2) = sin2
    pc.setX(-cos2*width/2+pm.x());
    pc.setY(-sin2*width/2+pm.y());  // (pm.y - pc.y) / (width/2) = sin2

    QPointF points[3];
    points[0] = pa;
    points[1] = pb;
    points[2] = pc;
    painter.drawPolygon(points, 3);
}
}

void Link::paint(QPainter *painter,
                 const QStyleOptionGraphicsItem *option,
                 QWidget * /* widget */)
{
    QPen pen(color());
    if (option->state & QStyle::State_Selected) {
        pen.setStyle(Qt::DotLine);
        pen.setWidth(2);
    }
    painter->setPen(pen);
    painter->setBrush(color());

    drawArrowLine(*painter, myFromNode->pos(), myToNode->pos());
}
