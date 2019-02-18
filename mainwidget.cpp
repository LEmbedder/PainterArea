#include "mainwidget.h"
#include <QColorDialog>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    paintArea = new PaintArew;
    //设置形状
    shapeLabel = new QLabel("形状");
    shapeComboBox = new QComboBox;
    shapeComboBox->addItem("line",PaintArew::Line);
    shapeComboBox->addItem("Rectangle",PaintArew::Rectangle);
    shapeComboBox->addItem("RoundRect",PaintArew::RoundRect);
    shapeComboBox->addItem("Ellipse",PaintArew::Ellipse);
    shapeComboBox->addItem("Polygon",PaintArew::Polygon);
    shapeComboBox->addItem("Polyline",PaintArew::Polyline);
    shapeComboBox->addItem("Points",PaintArew::Points);
    shapeComboBox->addItem("Arc",PaintArew::Arc);
    shapeComboBox->addItem("Path",PaintArew::Path);
    shapeComboBox->addItem("Text",PaintArew::Text);
    shapeComboBox->addItem("Pixmap",PaintArew::Pixmap);
    connect(shapeComboBox,SIGNAL(activated(int)),this,SLOT(ShowShape(int)));

    //设置画笔颜色
    penColorLabel = new QLabel("画笔颜色");
    penColorFrame = new QFrame;
    penColorFrame->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    penColorFrame->setAutoFillBackground(true);
    penColorFrame->setPalette(QPalette(Qt::blue));
    penColorBtn = new QPushButton("更改");
    connect(penColorBtn,SIGNAL(clicked(bool)),this,SLOT(ShowPenColor()));

    //设置画笔线宽
    penWidthLabel = new QLabel("画笔线宽");
    penWidthSpinBox = new QSpinBox;
    penWidthSpinBox->setRange(0,20);
    connect(penWidthSpinBox,SIGNAL(valueChanged(int)),this,SLOT(ShowPenWidth(int)));

    //设置画笔风格
    penStyleLabel = new QLabel("画笔风格");
    penStyleComboBox = new QComboBox;
    penStyleComboBox->addItem("SoledLine",static_cast<int>(Qt::SolidLine));
    penStyleComboBox->addItem("DashLine",static_cast<int>(Qt::DashLine));
    penStyleComboBox->addItem("DotLine",static_cast<int>(Qt::DotLine));
    penStyleComboBox->addItem("DashDotLine",static_cast<int>(Qt::DashDotLine));
    penStyleComboBox->addItem("DashDotDotLine",static_cast<int>(Qt::DashDotDotLine));
    penStyleComboBox->addItem("CustomDashLine",static_cast<int>(Qt::CustomDashLine));
    connect(penStyleComboBox,SIGNAL(activated(int)),this,SLOT(ShowPenStyle(int)));

    //右边控制区域
    rightLayout = new QGridLayout;
    rightLayout->addWidget(shapeLabel,0,0);
    rightLayout->addWidget(shapeComboBox,0,1);
    rightLayout->addWidget(penColorLabel,1,0);
    rightLayout->addWidget(penColorFrame,1,1);
    rightLayout->addWidget(penColorBtn,1,2);
    rightLayout->addWidget(penWidthLabel,2,0);
    rightLayout->addWidget(penWidthSpinBox,2,1);
    rightLayout->addWidget(penStyleLabel,3,0);
    rightLayout->addWidget(penStyleComboBox,3,1);
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(paintArea);
    mainLayout->addLayout(rightLayout);
}



MainWidget::~MainWidget()
{

}

void MainWidget::ShowShape(int value)
{
    PaintArew::Shape shape = PaintArew::Shape(shapeComboBox->itemData(value,Qt::UserRole).toInt());
    paintArea->setShap(shape);
}

void MainWidget::ShowPenWidth(int value)
{
    QColor color = penColorFrame->palette().color(QPalette::Window);
    Qt::PenStyle style = Qt::PenStyle(penStyleComboBox->itemData(penStyleComboBox->currentIndex(),Qt::UserRole).toInt());
//    Qt::PenCapStyle cap = Qt::PenCapStyle(penCapComboBox->itemData(penCapComboBox->currentIndex(),Qt::UserRole).toInt());
//    Qt::PenJoinStyle join=Qt::PenJoinStyle(penJoinComboBox->itemData(penJoinComboBox->currentIndex(),Qt::UserRole).toInt());
    paintArea->setPen(QPen(color,value,style));

}

void MainWidget::ShowPenColor()
{
    QColor color = QColorDialog::getColor(static_cast<int>(Qt::blue));
    penColorFrame->setPalette(QPalette(color));
    int value = penWidthSpinBox->value();
    Qt::PenStyle style = Qt::PenStyle(penStyleComboBox->itemData(penStyleComboBox->currentIndex(),Qt::UserRole).toInt());
    //Qt::PenCapStyle cap = Qt::PenCapStyle(penCapComboBox->itemData(penCapComboBox->currentIndex(),Qt::UserRole).toInt());
    //Qt::PenJoinStyle join=Qt::PenJoinStyle(penJoinComboBox->itemData(penJoinComboBox->currentIndex(),Qt::UserRole).toInt());
    paintArea->setPen(QPen(color,value,style));
}

void MainWidget::ShowPenStyle(int styleValue)
{
    QColor color = penColorFrame->palette().color(QPalette::Window);
    int value = penWidthSpinBox->value();
    Qt::PenStyle style = Qt::PenStyle(penStyleComboBox->itemData(styleValue,Qt::UserRole).toInt());
    //Qt::PenCapStyle cap = Qt::PenCapStyle(penCapComboBox->itemData(penCapComboBox->currentIndex(),Qt::UserRole).toInt());
    //Qt::PenJoinStyle join=Qt::PenJoinStyle(penJoinComboBox->itemData(penJoinComboBox->currentIndex(),Qt::UserRole).toInt());
    paintArea->setPen(QPen(color,value,style));
}

void MainWidget::ShowPenCap(int)
{

}

void MainWidget::ShowPenJoin(int)
{

}

void MainWidget::ShowSpreadStyle()
{

}

void MainWidget::ShowFillRule()
{

}

void MainWidget::ShowBrushColor()
{

}

void MainWidget::ShowBrush(int)
{

}
