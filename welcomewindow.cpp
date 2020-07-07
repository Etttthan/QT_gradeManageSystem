#include "welcomewindow.h"
#include "ui_welcomewindow.h"
//#include "studentwindow.h"
#include"public_fuction.h"

welcomewindow::welcomewindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::welcomewindow)
{
    ui->setupUi(this);
    //固定窗口大小
    this->setFixedSize(400,600);
    ui->label->setPixmap(QPixmap(":/accountUnknown.png"));
    startTimer(100);

    QObject::connect(ui->btnLogin,&QPushButton::clicked,[=]()
    {
        this->handleLogin();
    });
    QObject::connect(ui->btn_forgetPsword,&QPushButton::clicked,[=]()
        {
            QMessageBox dialog_forget_password;

            dialog_forget_password.setText(QStringLiteral("请联系管理员找回密码"));
            dialog_forget_password.setInformativeText(QStringLiteral("EMAIL:  adminSIS@zju.edu.cn\nTELE:  18888654871"));
            dialog_forget_password.setWindowTitle(QStringLiteral("忘记密码")) ;
            dialog_forget_password.setFixedSize(300,100);
            dialog_forget_password.setWindowIcon(QIcon(":/account.png"));
            dialog_forget_password.exec();
        });

}

welcomewindow::~welcomewindow()
{
    delete ui;
}

void welcomewindow::handleLogin()
{
    this->login_name=ui->lineEdit_name->text();
    this->login_password=ui->lineEdit_password->text();

    int flag;
    QSqlQuery query;
    QString userid;
    QString password;
    query.exec(QString("SELECT password FROM login WHERE ID='%1'").arg(this->login_name));
    flag=0;
    if(query.seek(0))
    {
        password = query.value(0).toString();

                if(this->login_password==password){
                    //emit succeed_login_S();       //发送信号
                    if(this->login_name[0]=='3'){
                        emit succeed_login_S(login_name);
                    }
                    else if(this->login_name[0]=='1'){
                        emit succeed_login_T();
                    }
                    this->close();
                }
                else{
                    QMessageBox dialog_login;
                    dialog_login.setText(QStringLiteral("登录密码错误，请检查是否输入错误或点击忘记密码"));
                    dialog_login.setWindowTitle(QStringLiteral("登录错误")) ;
                    dialog_login.setFixedSize(300,100);
                    dialog_login.setWindowIcon(QIcon(":/errorIcon.png"));
                    dialog_login.exec();
                }
    }


    else{
        QMessageBox dialog_login;
        dialog_login.setText(QStringLiteral("用户名不存在，请检查是否输入错误"));
        dialog_login.setWindowTitle(QStringLiteral("登录错误"));
        dialog_login.setFixedSize(300,100);
        dialog_login.setWindowIcon(QIcon(":/errorIcon.png"));
        dialog_login.exec();
    }


}

//定时器，动态改变头像
void welcomewindow::timerEvent(QTimerEvent *){
    QString temp= login_name=ui->lineEdit_name->text();
    if(temp.mid(0,1) =="3"){
        ui->label->setPixmap(QPixmap(":/accountStudent.png"));
    }else if (temp.mid(0,1) =="1"){
        ui->label->setPixmap(QPixmap(":/accountTeacher.png"));
    }else{
        ui->label->setPixmap(QPixmap(":/accountUnknown.png"));
    }
}
