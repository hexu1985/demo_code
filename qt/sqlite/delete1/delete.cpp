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
    QString delete_sql = "delete from student where id = ?";
    sql_query.prepare(delete_sql);
    sql_query.addBindValue(1);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        qDebug()<<"deleted!";
    }

    database.close();
    return 0;
}
