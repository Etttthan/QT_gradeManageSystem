#include "studentwindow.h"
#include "ui_studentwindow.h"
#include "public_fuction.h"
#include "statistic.h"
#include <QString>
#include <QDebug>

studentWindow::studentWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::studentWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(QStringLiteral("学生成绩查询"));
    this->setWindowIcon(QIcon(":/accountStudent.png"));
    Statistic *statisticShow = new Statistic;
    statisticShow->hide();

    model = new QSqlTableModel;
    model->setTable("stusc");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    ui->tableView->setModel(model);

    QObject::connect(ui->btn_statisticShow,&QPushButton::clicked,[=]()
    {
        int row=0;
        float i=1;
        QSqlQuery query;
        QString sql="SELECT * FROM stusc WHERE ID="+student_ID;
        query.exec(sql);
        while(query.seek(row)){
            statisticShow->xList.append(i);
            statisticShow->yList.append(query.value(2).toFloat());
            i=i+1;
            row++;
        }

        statisticShow->show();
    });

    ui->comboBox->addItem(QStringLiteral("按成绩"));
    ui->comboBox->addItem(QStringLiteral("按课程ID"));
}

void studentWindow::on_pushButton_2_clicked(){
    if(ui->lineEdit->text()!=""){
        model->setFilter(QString("courseName = '%1' and ID = '%2'").arg(ui->lineEdit->text(),this->student_ID));
        model->select();
    }
}

void studentWindow::on_pushButton_8_clicked(){
    model->setTable("stusc");
    model->setFilter(QString("ID = '%1'").arg(this->student_ID));
    model->select();
}

void studentWindow::on_pushButton_6_clicked(){
    model->setTable("stusc");
    model->setFilter(QString("ID = '%1'").arg(this->student_ID));
    if (ui->comboBox->currentIndex()==0){
        model->sort(2, Qt::AscendingOrder);
        model->select();
    }
    else if (ui->comboBox->currentIndex()==1){
        model->sort(1, Qt::AscendingOrder);
        model->select();
    }
}

void studentWindow::on_pushButton_5_clicked(){
    model->setTable("stusc");
    model->setFilter(QString("ID = '%1'").arg(this->student_ID));
    if (ui->comboBox->currentIndex()==0){
        model->sort(2, Qt::DescendingOrder);
        model->select();
    }
    else if (ui->comboBox->currentIndex()==1){
        model->sort(1, Qt::DescendingOrder);
        model->select();
    }
}

studentWindow::~studentWindow()
{
    delete ui;
}

void studentWindow::getAndShow(QString student_ID){
    this->student_ID=student_ID;
    model = new QSqlTableModel;
    model->setTable("stusc");
    model->setFilter(QString("ID = '%1'").arg(student_ID));
    model->select();
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->setModel(model);
    ui->label_5->setText(getAverage());
    this->show();
}

QString studentWindow::getAverage(){
    int sum=0;
    int i=0;
    int row=0;
    double average;
    QSqlQuery query;
    QString sql="SELECT * FROM stusc WHERE ID="+student_ID;
    query.exec(sql);
    query.seek(row);
    while(query.seek(row)){
        sum=sum+query.value(2).toInt();
        i++;
        row++;
    }
    if(i){
        average=sum/i;
    }
    else{
        average=0;
    }

    int intpart=floor(average);
    int pointpart=int((average-intpart)*100);
    QString result,result1,result2;
    result1=QString("%1").arg(intpart);
    result2=QString("%1").arg(pointpart);
    result=result1+"."+result2;

    return result;
}
