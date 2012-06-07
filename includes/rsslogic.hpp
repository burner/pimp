#include <QtSql>

bool initDB();
bool addFeed(QSqlQuery& q, const QString& name, const QString& url);
