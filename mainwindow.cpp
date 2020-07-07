#include "statistic.h"
#include "public_fuction.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1440,900);
    this->setWindowTitle(QStringLiteral("学生成绩管理系统"));
    this->setWindowIcon(QIcon(":/accountTeacher.png"));

    Statistic *statisticShow = new Statistic;
    statisticShow->hide();

    model = new QSqlTableModel;
    model->setTable("student");
    model->select();
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->setModel(model);

    ui->comboBox->addItem(QStringLiteral("按学号"));


    /*QObject::connect(ui->pushButton_8,&QPushButton::clicked,[=]()
    {
        ui->label_11->setText("state changed");
    });*/
    QObject::connect(ui->btn_statisticShow,&QPushButton::clicked,[=]()
    {
        int row=0;
        float i=1;
        QSqlQuery query;
        query.exec("SELECT * FROM stusc");
        while(query.seek(row)){
            statisticShow->xList.append(i);
            statisticShow->yList.append(query.value(2).toFloat());
            i=i+1;
            row++;
        }

        statisticShow->show();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()     //pushButton  提交信息修改按钮
{
    if (model->tableName() == "stusc"){
        int rows = model->rowCount();
        QString sid,cid,grade;
        QModelIndex index=model->index(rows-1,0);//rowNum,columnNum为行列号
        sid= model->data(index).toString();
        index=model->index(rows-1,1);//rowNum,columnNum为行列号
        cid= model->data(index).toString();
        index=model->index(rows-1,2);//rowNum,columnNum为行列号
        grade= model->data(index).toString();
        QString sql="INSERT INTO sc values("+sid+","+cid+","+grade+")";
        QSqlQuery query;
        if(query.exec(sql)){
            QMessageBox::warning(this,tr("change"),QStringLiteral("修改已被提交!"));
        }

    }
    else {
    //事务操作
        model->database().transaction();//database()  返回模型的数据库连接
                      //transaction()  如果驱动程序支持事务  则在数据库上开始事务  操作成功返回true  否则返回false
        if(model->submitAll())//submitAll()  提交所有挂起的更改并在成功时返回true
        {
            model->database().commit();
               //commit() 如果驱动程序支持事务并且transaction（）已启动，则将事务提交到数据库  操作成功返回true  否则返回false
            QMessageBox::warning(this,tr("change"),QStringLiteral("修改已被提交!"));  //弹出提示窗口
                                    //参数一  QWidegt对象   参数二 窗口名   参数三 提示文本
        }
        else
        {
            model->database().rollback();
               //如果驱动程序支持事务并且transaction（）已启动，则回滚数据库上的事务  操作成功返回true  否则返回false。
            QMessageBox::warning(this,tr("tableModel"),QStringLiteral("数据库错误! %1").arg(model->database().lastError().text()));
                    //参数三是提示文本  这里利用Qt类自带的Error提示信息  用arg（）函数转化为QString
        }

        if(model->tableName() == "student")
        {
            //获取当前学生的ID
            QSqlQuery query;
            query.exec("SELECT * FROM student");
            query.seek(row_add);
            QString new_add_ID = query.value(0).toString();
            QString sql="INSERT INTO login values("+new_add_ID+",\"123456\")";
            query.exec(sql);
        }
        model->select();
    }
}

void MainWindow::on_pushButton_4_clicked()  //pushButton_4  撤销修改按钮
{
    model->revertAll();  //revertAll()  还原所有挂起的更改
}

void MainWindow::on_btn_queryTable_clicked()  //btn_queryTable  查询按钮
{
    if(ui->lineEdit->text()!=""){
        model->setFilter(QString("courseName = '%1'").arg(ui->lineEdit->text()));
        model->select();
    }
    if(ui->lineEdit_2->text()!=""){
        model->setFilter(QString("ID = '%1'").arg(ui->lineEdit_2->text()));
        model->select();
    }
}

void MainWindow::on_lineEdit_textChanged(){
    ui->lineEdit->setEnabled(true);
    ui->lineEdit_2->setEnabled(true);
    if((ui->lineEdit->text()!="")&&(ui->lineEdit_2->text()=="")){
        ui->lineEdit_2->setEnabled(false);
    }
    if((ui->lineEdit_2->text()!="")&&(ui->lineEdit->text()=="")){
        ui->lineEdit->setEnabled(false);
    }
}

void MainWindow::on_lineEdit_2_textChanged(){
    ui->lineEdit->setEnabled(true);
    ui->lineEdit_2->setEnabled(true);
    if((ui->lineEdit->text()!="")&&(ui->lineEdit_2->text()=="")){
        ui->lineEdit_2->setEnabled(false);
    }
    if((ui->lineEdit_2->text()!="")&&(ui->lineEdit->text()=="")){
        ui->lineEdit->setEnabled(false);
    }
}

void MainWindow::on_pushButton_8_clicked()  //pushButton_8  更新/显示所有学生成绩
{
    static int flag=0;
    int selected_row = ui->tableView->currentIndex().row();
    if(flag==0){
        ui->lineEdit->setEnabled(true);
        ui->lineEdit_2->setEnabled(true);
        flag=1;
        ui->comboBox->addItem(QStringLiteral("按成绩"));
        if(selected_row==-1){
            model->setTable("stusc");
            model->select();
        }
        else{
            model->setTable("stusc");
            model->select();
            QSqlQuery query;
            query.exec("SELECT * FROM student");
            query.seek(selected_row);
            model->setFilter(QObject::tr("ID = '%1'").arg(query.value(0).toString()));
            model->select();
        }
    }
    else if(flag==1){
        ui->lineEdit->setEnabled(false);
        ui->lineEdit_2->setEnabled(false);
        ui->comboBox->removeItem(1);
        flag=0;
        model->setTable("student");
        model->select();
    }
}

void MainWindow::on_pushButton_6_clicked(){

    if (ui->comboBox->currentIndex()==0){
        model->sort(0, Qt::AscendingOrder);
        model->select();
    }
    else if (ui->comboBox->currentIndex()==1){
        model->sort(2, Qt::AscendingOrder);
        model->select();
    }
}

void MainWindow::on_pushButton_5_clicked(){

    if (ui->comboBox->currentIndex()==0){
        model->sort(0, Qt::DescendingOrder);
        model->select();
    }
    else if (ui->comboBox->currentIndex()==1){
        model->sort(2, Qt::DescendingOrder);
        model->select();
    }
}

void MainWindow::on_pushButton_2_clicked()  //pushButton_2  添加学生信息
{
    int rows = model->rowCount();//rowCount() 如果数据库支持返回查询的大小则返回当前查询的行数，否则返回客户端上当前缓存的行数


        int id = -1;
        row_add=rows;
        model->insertRow(rows);//在rows这一行插入一行
        model->setData(model->index(rows,0),id);

}

void MainWindow::on_pushButton_3_clicked()  //pushButton_3  删除选中行
{
    int selected_row = ui->tableView->currentIndex().row();//获取当前选择的行号


    int is_delete = QMessageBox::warning(this,QStringLiteral("删除"),QStringLiteral("你确定删除当前行?"),QMessageBox::Yes,QMessageBox::No);
    if(is_delete == QMessageBox::Yes)
    {
        //如果删除的是学生，则需要将与之关联的其他信息也删除
        if(model->tableName() == "student")
        {
            //获取当前学生的ID
            QSqlQuery query;
            query.exec("SELECT * FROM student");//exec（） 执行查询中的SQL
            query.seek(selected_row);//seek（） 检索位置索引处的记录
            QString current_selected_ID_delete = query.value(0).toString();
                    //value(0) 获取index为0的数据值   toString() 将其转化为QString
/*
            //删除选课表
            query.exec(QString("DROP TABLE '%1'").arg("IDNAMESTUDENT"+current_selected_ID_delete));*/
        }
        //提交
        model->removeRow(selected_row);
        model->submitAll();
    }
    else {
        //撤回
        model->revertAll();
    }

}

