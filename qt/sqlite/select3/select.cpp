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
    QString select_max_sql = "select max(id) from student";
    int max_id = 0;
    sql_query.prepare(select_max_sql);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            max_id = sql_query.value(0).toInt();
            qDebug() << QString("max id:%1").arg(max_id);
        }
    }

    database.close();
    return 0;
}
