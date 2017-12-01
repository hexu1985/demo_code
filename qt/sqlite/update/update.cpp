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
    QString update_sql = "update student set name = :name where id = :id";
    sql_query.prepare(update_sql);
    sql_query.bindValue(":name", "Qt");
    sql_query.bindValue(":id", 1);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "updated!";
    }

    database.close();
    return 0;
}
