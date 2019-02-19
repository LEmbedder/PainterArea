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

    //设置画笔顶帽
    penCapLabel = new QLabel("画笔顶帽:");
    penCapComboBox = new QComboBox;
    penCapComboBox->addItem("SurareCap",Qt::SquareCap);
    penCapComboBox->addItem("FlatCap",Qt::FlatCap);
    penCapComboBox->addItem("RoundCap",Qt::RoundCap);
    connect(penCapComboBox,SIGNAL(activated(int)),this,SLOT(ShowPenCap(int)));

    //设置画笔连接点
    penJoinLabel = new QLabel("画笔连接点");
    penJoinComboBox = new QComboBox;
    penJoinComboBox->addItem("BevelJoin",Qt::BevelJoin);
    penJoinComboBox->addItem("MiterJoin",Qt::MiterJoin);
    penJoinComboBox->addItem("RoundJoin",Qt::RoundJoin);
    connect(penJoinComboBox,SIGNAL(activated(int)),this,SLOT(ShowPenJoin(int)));

    //设置填充模式
    fillRuleLabel = new QLabel("填充模式");
    fillRuleComboBox = new QComboBox;
    fillRuleComboBox->addItem("odd Even",Qt::OddEvenFill);
    fillRuleComboBox->addItem("Winding",Qt::WindingFill);
    connect(fillRuleComboBox,SIGNAL(activated(int)),this,SLOT(ShowFillRule()));
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
    rightLayout->addWidget(penCapLabel,4,0);
    rightLayout->addWidget(penCapComboBox,4,1);
    rightLayout->addWidget(penJoinLabel,5,0);
    rightLayout->addWidget(penJoinComboBox,5,1);
    rightLayout->addWidget(fillRuleLabel,6,0);
    rightLayout->addWidget(fillRuleComboBox,6,1);
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
    Qt::PenCapStyle cap = Qt::PenCapStyle(penCapComboBox->itemData(penCapComboBox->currentIndex(),Qt::UserRole).toInt());
    Qt::PenJoinStyle join=Qt::PenJoinStyle(penJoinComboBox->itemData(penJoinComboBox->currentIndex(),Qt::UserRole).toInt());
    paintArea->setPen(QPen(color,value,style,cap,join));

}

void MainWidget::ShowPenColor()
{
    QColor color = QColorDialog::getColor(static_cast<int>(Qt::blue));
    penColorFrame->setPalette(QPalette(color));
    int value = penWidthSpinBox->value();
    Qt::PenStyle style = Qt::PenStyle(penStyleComboBox->itemData(penStyleComboBox->currentIndex(),Qt::UserRole).toInt());
    Qt::PenCapStyle cap = Qt::PenCapStyle(penCapComboBox->itemData(penCapComboBox->currentIndex(),Qt::UserRole).toInt());
    Qt::PenJoinStyle join=Qt::PenJoinStyle(penJoinComboBox->itemData(penJoinComboBox->currentIndex(),Qt::UserRole).toInt());
    paintArea->setPen(QPen(color,value,style,cap,join));
}

void MainWidget::ShowPenStyle(int styleValue)
{
    QColor color = penColorFrame->palette().color(QPalette::Window);
    int value = penWidthSpinBox->value();
    Qt::PenStyle style = Qt::PenStyle(penStyleComboBox->itemData(styleValue,Qt::UserRole).toInt());
    Qt::PenCapStyle cap = Qt::PenCapStyle(penCapComboBox->itemData(penCapComboBox->currentIndex(),Qt::UserRole).toInt());
    Qt::PenJoinStyle join=Qt::PenJoinStyle(penJoinComboBox->itemData(penJoinComboBox->currentIndex(),Qt::UserRole).toInt());
    paintArea->setPen(QPen(color,value,style,cap,join));
}

void MainWidget::ShowPenCap(int capValue)
{
    QColor color = penColorFrame->palette().color(QPalette::Window);//color(参数含义？)
    int value = penWidthSpinBox->value();
    Qt::PenStyle style = Qt::PenStyle(penStyleComboBox->itemData(penStyleComboBox->currentIndex(),Qt::UserRole).toInt());
    Qt::PenCapStyle cap = Qt::PenCapStyle(penCapComboBox->itemData(capValue,Qt::UserRole).toInt());
    Qt::PenJoinStyle join=Qt::PenJoinStyle(penJoinComboBox->itemData(penJoinComboBox->currentIndex(),Qt::UserRole).toInt());
    paintArea->setPen(QPen(color,value,style,cap,join));
}

void MainWidget::ShowPenJoin(int joinValue)
{
    QColor color = penColorFrame->palette().color(QPalette::Window);
    int value = penWidthSpinBox->value();
    Qt::PenStyle style = Qt::PenStyle(penStyleComboBox->itemData(penStyleComboBox->currentIndex(),Qt::UserRole).toInt());
    Qt::PenCapStyle cap = Qt::PenCapStyle(penCapComboBox->itemData(penCapComboBox->currentIndex(),Qt::UserRole).toInt());
    Qt::PenJoinStyle join=Qt::PenJoinStyle(penJoinComboBox->itemData(joinValue,Qt::UserRole).toInt());
    paintArea->setPen(QPen(color,value,style,cap,join));

}

void MainWidget::ShowSpreadStyle()
{

}

void MainWidget::ShowFillRule()
{
    Qt::FillRule rule = Qt::FillRule(fillRuleComboBox->itemData(fillRuleComboBox->currentIndex(),Qt::UserRole).toInt());
    paintArea->SetFillRule(rule);
}

void MainWidget::ShowBrushColor()
{

}

void MainWidget::ShowBrush(int)
{

}
