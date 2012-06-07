#include <rssmainwidget.hpp>
#include <newfeeddialog.hpp>
#include <debug.hpp>

RssMainWidget::RssMainWidget(QWidget* parent) : QWidget(parent) {
	ui.setupUi(this);
	QObject::connect(ui.newFeedButton, SIGNAL(clicked()), this, SLOT(newFeed()));
	db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName("rssmemory.sqlite");
	db.open();
	this->init();
	ui.feedView->setColumnHidden(feedModel->fieldIndex("id"),true);
	ui.feedView->setColumnHidden(feedModel->fieldIndex("url"),true);
}

void RssMainWidget::init() {
	bool initDBsucc = initDB(db);
	if(!initDBsucc) {
		debug()<<"Rss database init failed, that means the"
			<<"rss widget might not work";
		return;
	} else {
		debug()<<"Rss database init worked";	
		feedModel = new QSqlTableModel(this);
		feedModel->setEditStrategy(QSqlTableModel::OnFieldChange);
		feedModel->setTable("feeds");
		feedModel->select();

		ui.feedView->setModel(feedModel);

		feedEntryModel = new QSqlRelationalTableModel(ui.feedEntryView);
	}
}

void RssMainWidget::newFeed() {
	debug()<<"here";
	NewFeedDialog newFeed(this);
	newFeed.exec();	
}

void RssMainWidget::insertNewFeed(const QString name, const QString url) {
	QSqlDatabase db = QSqlDatabase::database("QSQLITE");
 	debug()<<name<<url;
	QSqlQuery query;
	this->addFeed(query, name, url);
	db.commit();
	feedModel->select();
}

bool RssMainWidget::initDB(QSqlDatabase& db) {
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
			"create table feeds(id integer primary key, name varchar, url varchar, unread integer)"))) {
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

bool RssMainWidget::addFeed(QSqlQuery& q, const QString& name, const QString& url) {
	if (!q.prepare(QString("insert into feeds(name, url, unread) values(:name, :url, :count)"))) {
		critical()<<q.lastError().text();
		return false;
	}
	q.bindValue(QString(":name"), name);
	q.bindValue(QString(":url"), url);
	q.bindValue(QString(":count"), QVariant(0));
	q.exec();
	return true;
}
