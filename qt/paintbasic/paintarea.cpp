#include "paintarea.h"
#include <fstream>

using namespace std;

PaintArea::PaintArea(QWidget *parent)
{
    shape = Line;

    QPalette p = palette();
    p.setColor(QPalette::Window,Qt::white);
    setPalette(p);
    setAutoFillBackground(true);
    
    setMinimumSize(400,400);
}

void PaintArea::setShape(Shape s)
{
    shape = s;
    update();
}

void PaintArea::setPen(QPen p)
{
    pen = p;
    update();
}

void PaintArea::setBrush(QBrush b)
{
    brush = b;
    update();
}

void drawArrowLine(QPainter &painter, const QPoint &p1, const QPoint &p2) // from p1 to p2
{
    ofstream clog("/tmp/log.txt");
    clog << "p1: (" << p1.x() << ", " << p1.y() << ")\n";
    clog << "p2: (" << p2.x() << ", " << p2.y() << ")\n";

    painter.drawLine(p1, p2);
    if (p1 == p2)
        return;

    QPoint pm((p1.x()+p2.x())/2, (p1.y()+p2.y())/2); // p1和p2的中点
    clog << "pm: (" << pm.x() << ", " << pm.y() << ")\n";
    int width = 10;     // 箭头宽度
    int length = 12;    // 箭头长度
    QPoint pa, pb, pc;  // pa为箭头顶点, pb, pc为两边的顶点
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
        clog << "k1: " << k1 << ", k2: " << k2 << '\n';
        // k = tan, cos = +-sqrt(1/(1+k*k)), sin = +-sqrt(k*k/(1+k*k));
        cos1 = (p1.x() < p2.x() ? 1 : -1) * sqrt(1 / (1 + k1*k1));
        sin1 = (p1.y() < p2.y() ? 1 : -1) * sqrt((k1 * k1) / (1 + k1*k1));
        cos2 = sqrt(1 / (1 + k2*k2));
        sin2 = (k2 > 0 ? 1 : -1) * sqrt((k2 * k2) / (1 + k2*k2));
    }
    clog << "cos1: " << cos1 << ", sin1: " << sin1 << '\n';
    clog << "cos2: " << cos2 << ", sin2: " << sin2 << '\n';

    pa.setX(cos1*length+pm.x());
    pa.setY(sin1*length+pm.y());
    pb.setX(cos2*width/2+pm.x());
    pb.setY(sin2*width/2+pm.y());   // (pb.y - pm.y) / (width/2) = sin2
    pc.setX(-cos2*width/2+pm.x());
    pc.setY(-sin2*width/2+pm.y());  // (pm.y - pc.y) / (width/2) = sin2
    clog << "pa: (" << pa.x() << ", " << pa.y() << ")\n";
    clog << "pb: (" << pb.x() << ", " << pb.y() << ")\n";
    clog << "pc: (" << pc.x() << ", " << pc.y() << ")\n";

    QPoint points[3];
    points[0] = pa;
    points[1] = pb;
    points[2] = pc;
    painter.drawPolygon(points, 3);
//    painter.drawLine(pa, pb);
//    painter.drawLine(pb, pc);
//    painter.drawLine(pc, pa);
}

void PaintArea::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setPen(pen);
    p.setBrush(brush);
    
    QRect rect(50,100,300,200);
    
    static const QPoint points[4] = {
         QPoint(150, 100),
         QPoint(300, 150),
         QPoint(350, 250),
         QPoint(100, 300)
     };
     
    int startAngle = 30 * 16;
    int spanAngle = 120 * 16;
     
    QPainterPath path;
    path.addRect(150,150,100,100);
    path.moveTo(100,100);
    path.cubicTo(300,100,200,200,300,300);
    path.cubicTo(100,300,200,200,100,100);
    
    switch(shape)
    {
    case Line:
        p.drawLine(rect.topLeft(),rect.bottomRight());
        break;
    case Rectangle:
        p.drawRect(rect);
        break;
    case RoundRect:
        p.drawRoundRect(rect);
        break;
    case Ellipse:
        p.drawEllipse(rect);
        break;
    case Polygon:
        p.drawPolygon(points,4);
        break;
    case Polyline:
        p.drawPolyline(points,4);
        break;
    case Points:
        p.drawPoints(points,4);
        break;
    case Arc:
        p.drawArc(rect,startAngle,spanAngle);
        break;
    case Path:
        p.drawPath(path);
        break;
    case Text:
        p.drawText(rect,Qt::AlignCenter,tr("Hello Qt!"));
        break;
    case Pixmap:
        p.drawPixmap(150,150,QPixmap(":/images/butterfly.png"));
        break;
    case ArrowLine:
        drawArrowLine(p, QPoint(0,0), QPoint(100, 100));
        drawArrowLine(p, QPoint(200,200), QPoint(100, 100));
        drawArrowLine(p, QPoint(0,200), QPoint(100, 100));
        drawArrowLine(p, QPoint(200,0), QPoint(100, 100));
        drawArrowLine(p, QPoint(0,100), QPoint(100, 100));
        drawArrowLine(p, QPoint(200,100), QPoint(100, 100));
        drawArrowLine(p, QPoint(100,0), QPoint(100, 100));
        drawArrowLine(p, QPoint(100,200), QPoint(100, 100));
        break;
    default:
    	break;
    }
}
