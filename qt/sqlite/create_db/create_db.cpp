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

    database.close();
    return 0;
}
