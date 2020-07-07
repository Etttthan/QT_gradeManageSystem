#include "statistic.h"
#include "ui_statistic.h"
#include <QPainter>
#include <QPointF>
#include <QPen>
Statistic::Statistic(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Statistic)
{
    ui->setupUi(this);
    x = -10;
    m_count = 0;
    creatData();
    update();
    //在这里展示数据
}

Statistic::~Statistic()
{
    delete ui;
}

void Statistic::creatData()
{
    /*
    x += 0.2;
    m_count += 1;
    if(m_count%2)
    {
        xList.append(x);
        yList.append(qSin(x));
    }
    else
    {
        xList.append(x);
        yList.append(qSin(x));
        update();
    }
    if(m_count == 100)
    {
        xList.clear();
        yList.clear();
        m_count = 0;
        x = -10;
    }*/
    /*
    int i;
    for(i=0;i<10;i++){
        xList.append(i);
        if (i%2==0) {
            yList.append(75+i);
            //update();
        }
        else {
            yList.append(85-i);
        }
    }*/
}
void Statistic::paintEvent(QPaintEvent *)
{
    int i;
    QPainter painter(this);
    QPen pen(Qt::black, 0.02, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);
    painter.setViewport(50, 50, width()-100, height()-100);
    painter.setWindow(0, 100, 10, -100);//x,y,width,height
    painter.fillRect(0, 100, 10, -100, Qt::white);

    painter.drawLine(QPointF(0, 1), QPointF(10, 1));   // x
    painter.drawLine(QPointF(0, 0), QPointF(0, 100));     // y
    for( i = 0; i < yList.count(); i++)
    {
        if(i == 0)
            painter.drawPoint(QPointF(xList[i], yList[i]));
        else
            painter.drawLine(QPointF(xList[i-1], yList[i-1]), QPointF(xList[i], yList[i]));
    }
}
