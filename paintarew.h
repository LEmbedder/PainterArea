#ifndef PAINTAREW_H
#define PAINTAREW_H

#include <QWidget>
#include <QPen>
#include <QBrush>
class PaintArew : public QWidget
{
    Q_OBJECT
public:
    enum Shape{Line,Rectangle,RoundRect,Ellipse,Polygon,Polyline,Points,Arc,Path,Text,Pixmap};
    explicit PaintArew(QWidget *parent = 0);
    void setShap(Shape);
    void setPen(QPen);
    void SetBrush(QBrush);
    void SetFillRule(Qt::FillRule);
    void paintEvent(QPaintEvent *);

signals:

public slots:
private:
    Shape shape;
    QPen pen;
    QBrush brush;
    Qt::FillRule fillRule;

};

#endif // PAINTAREW_H
