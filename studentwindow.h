#ifndef STUDENTWINDOW_H
#define STUDENTWINDOW_H

//#include <mainwindow.h>
#include <QWidget>
#include <QMainWindow>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlError>
#include <QSqlRecord>
#include <QMessageBox>
#include <QVector>
#include <QDebug>
#include <QString>
#include <QMap>
#include <QMapIterator>
#include <QMovie>
#include <QModelIndex>
#include "statistic.h"

namespace Ui {
class studentWindow;
}

class studentWindow : public QWidget
{
    Q_OBJECT

public:
    explicit studentWindow(QWidget *parent = nullptr);
    ~studentWindow();
    QString student_ID;
    void getAndShow(QString student_ID);

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::studentWindow *ui;
    Ui::Statistic *Stat;
    QSqlTableModel *model;
    QString getAverage();
};

#endif // STUDENTWINDOW_H
