#ifndef STATISTIC_H
#define STATISTIC_H

#include <QWidget>

namespace Ui {
class Statistic;
}

class Statistic : public QWidget
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *);
public:
    explicit Statistic(QWidget *parent =0);
    ~Statistic();
    int m_count;
    float x;
    QTimer* m_Timer;
    QList<float> xList;
    QList<float> yList;
    void creatData();

private:
    Ui::Statistic *ui;
};

#endif // STATISTIC_H
