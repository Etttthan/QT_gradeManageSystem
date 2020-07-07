#ifndef PUBLIC_FUCTION_H
#define PUBLIC_FUCTION_H


#include <QSqlQuery>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QVector>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <QMap>
#include <QApplication>
static bool createConnection()
{

    //打开数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("demo.db");
    if( !db.open())
        {
            qDebug() <<"can not create sql connection";
        }


    QSqlQuery query(db);

    //创建数据库表
    query.exec("CREATE TABLE login(ID INT PRIMARY KEY NOT NULL, password VCHAR NOT NULL)");

    query.exec("CREATE TABLE student(ID INT PRIMARY KEY NOT NULL, Name VCHAR NOT NULL,"
                                     "CLASS INT)");

    query.exec("CREATE TABLE teacher(ID INT PRIMARY KEY NOT NULL, Name VCHAR NOT NULL,"
                                     "CLASS INT)");

    query.exec("CREATE TABLE course(courseID INT PRIMARY KEY NOT NULL, Name VCHAR NOT NULL,"
                                     "TID INT)");
    query.exec("CREATE TABLE sc(ID INT  NOT NULL, courseID INT  NOT NULL,"
                                   "Grade INT,PRIMARY KEY(ID,courseID))");

    query.exec("create view stusc as select sc.ID,sc.courseID,Grade,student.Name,course.Name as courseName from sc,course,student where sc.ID=student.ID and course.courseID=sc.courseID;");

    query.exec("INSERT INTO login values(30001,\"123456\")");
    query.exec("INSERT INTO login values(30002,\"123456\")");
    query.exec("INSERT INTO login values(10001,\"123456\")");
    query.exec("INSERT INTO course values(1,\"Chinese\",10001)");
    query.exec("INSERT INTO course values(2,\"Math\",10001)");
    query.exec("INSERT INTO course values(3,\"English\",10001)");
    query.exec("INSERT INTO course values(4,\"Physics\",10001)");
    query.exec("INSERT INTO course values(5,\"Chemistry\",10001)");
    query.exec("INSERT INTO student values(30001,\"bill\",306)");
    query.exec("INSERT INTO student values(30002,\"wzn\",306)");
    query.exec("INSERT INTO teacher values(10001,\"zhou\",306)");
    query.exec("INSERT INTO sc values(30001,1,95)");
    query.exec("INSERT INTO sc values(30001,2,90)");
    query.exec("INSERT INTO sc values(30001,3,89)");
    query.exec("INSERT INTO sc values(30001,4,91)");
    query.exec("INSERT INTO sc values(30001,5,85)");
    query.exec("INSERT INTO sc values(30002,1,90)");
    return 0;
}




/*static double getGPA_singleStudent( QString _database_Table_Name)
{
    int all_credits=0;        //总学分
    double  sum_creditMUTIgrades=0; //总学分乘以成绩

    QSqlTableModel model_help;

    model_help.setTable(_database_Table_Name);
    model_help.select();

    QSqlQuery query;
    query.exec(QString("SELECT * FROM '%1'").arg(_database_Table_Name));
    query.first();

    for(int i=0;i<model_help.rowCount();i++)
    {
        if(query.value(4).toString() != "")
        {

            all_credits = all_credits +query.value(3).toInt();

            sum_creditMUTIgrades = sum_creditMUTIgrades+query.value(3).toInt()*query.value(4).toDouble();
        }
        query.next();
    }

    double new_GPA = (sum_creditMUTIgrades/all_credits)/100*4;  //GPA算法
    return new_GPA;
}*/




#endif // PUBLIC_FUCTIONS_H
