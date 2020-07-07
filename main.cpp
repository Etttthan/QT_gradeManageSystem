#include "mainwindow.h"
#include "welcomewindow.h"
#include "studentwindow.h"
#include "public_fuction.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    createConnection();//连接数据库
    MainWindow w;
    studentWindow s;
    welcomewindow *login = new welcomewindow;

    login->show();
    login->setWindowTitle(QStringLiteral("学生成绩管理系统"));
    login->setFixedSize(600,400);
    login->setWindowIcon(QIcon(":/mainIcon2.png"));

    //登录成功，则显示主界面

    QObject::connect(login,&welcomewindow::succeed_login_T,&login->w,&MainWindow::show);
    QObject::connect(login,&welcomewindow::succeed_login_S,&login->s,&studentWindow::getAndShow);
    return a.exec();
}
