#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
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

#include"ui_mainwindow.h"
#include"statistic.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_btn_queryTable_clicked();

    void on_lineEdit_textChanged();

    void on_lineEdit_2_textChanged();

private:
    Ui::MainWindow *ui;
    Ui::Statistic *Stat;
    QSqlTableModel *model;
    QString current_select_studentID_add; //当前选择查看的学生的数据库表名
    QMap <int,int> rows_studentID;    //当前行号与当前行学生的ID的哈希表（排序后与数据库表有可能不同）
    int row_add;

};


#endif // MAINWINDOW_H
