#include <rsslogic.hpp>
#include <debug.hpp>

bool initDB() {
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName("rssmemory.sqlite");

	if(!db.open()) {
		critical()<<db.lastError().text();
		return false;
	}

	QStringList tables = db.tables();
	if(tables.contains("feeds") && tables.contains("feedentries")) {
		debug()<<"feed and feedentries tables allready exists";
		return true;
	}

	QSqlQuery q;
    if(!q.exec(QLatin1String(
			"create table feeds(id integer primary key, title varchar, url varchar, unread integer)"))) {
		critical()<<q.lastError().text();
		return false;
	}

    if(!q.exec(QLatin1String(
			"create table feedentries(id integer primary key, title varchar, link varchar, ")
			+ QLatin1String("pubData varchar, description varchar)"))) {
		critical()<<q.lastError().text();
		return false;
	}

	return true;
}
