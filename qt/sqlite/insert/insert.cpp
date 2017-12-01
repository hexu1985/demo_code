#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

int main(int argc, char *argv[])
{
    QSqlDatabase database;
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else {
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName("../test.db");
    }

    if (!database.open()) {
        qDebug() << "Error: Failed to connect database." << database.lastError().text();
        return 1;
    }

    QSqlQuery sql_query;
    QString insert_sql = "insert into student values (?, ?, ?)";
    int max_id = 0;
    sql_query.prepare(insert_sql);
    sql_query.addBindValue(max_id+1);
    sql_query.addBindValue("Wang");
    sql_query.addBindValue(25);
    if(!sql_query.exec()) {
        qDebug() << sql_query.lastError();
    } else {
        qDebug() << "inserted Wang!";
    }

    if(!sql_query.exec("INSERT INTO student VALUES(3, \"Li\", 23)")) {
        qDebug() << sql_query.lastError();
    } else {
        qDebug() << "inserted Li!";
    }

    database.close();
    return 0;
}
