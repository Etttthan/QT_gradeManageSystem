#ifndef WELCOMEWINDOW_H
#define WELCOMEWINDOW_H

#include <mainwindow.h>
#include "studentwindow.h"
#include <QWidget>
#include <QString>
#include <QDebug>
#include <QImage>
#include <QPalette>
#include <QPixmap>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

namespace Ui {
class welcomewindow;
}

class welcomewindow : public QWidget
{
    Q_OBJECT

public:
    explicit welcomewindow(QWidget *parent = nullptr);
    ~welcomewindow();
    MainWindow w;
    studentWindow s;
    //定时器，动态改变头像
    void timerEvent(QTimerEvent *);
    void handleLogin();
signals:
    void succeed_login_T();
    void succeed_login_S(QString student_ID);

private:
    Ui::welcomewindow *ui;

    QString login_name;
    QString login_password;
};

#endif // WELCOMEWINDOW_H
