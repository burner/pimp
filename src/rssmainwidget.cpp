#include <rssmainwidget.hpp>
#include <newfeeddialog.hpp>
#include <debug.hpp>
#include <assert.h>
#include <mrss.h>

RssMainWidget::RssMainWidget(QWidget* parent) : QWidget(parent) {
	ui.setupUi(this);
	ui.feedView->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.feedView->setSelectionBehavior(QAbstractItemView::SelectRows);
	QObject::connect(ui.newFeedButton, SIGNAL(clicked()), this, 
		SLOT(newFeed()));
	QObject::connect(ui.removeFeedButton, SIGNAL(clicked()), this, 
		SLOT(onRemoveClick()));
	QObject::connect(ui.getFeedsButton, SIGNAL(clicked()), this, 
		SLOT(getFeeds()));
	db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName("rssmemory.sqlite");
	db.open();
	this->init();

	auto selectionModel = ui.feedView->selectionModel();
	assert(selectionModel != NULL);
	QObject::connect(selectionModel, 
		SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, 
		SLOT(selectFeedEntryChanged(QModelIndex,QModelIndex)));

	auto entryModel = ui.feedEntryView->selectionModel();
	assert(entryModel != NULL);
	QObject::connect(entryModel, 
		SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, 
		SLOT(selectFeedEntriesChanged(QModelIndex,QModelIndex)));

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

		feedEntryModel = new QSqlTableModel(this);
		feedEntryModel->setEditStrategy(QSqlTableModel::OnFieldChange);
		feedEntryModel->setTable("feedentries");
		feedEntryModel->select();

		ui.feedEntryView->setModel(feedEntryModel);
	}
}

void RssMainWidget::selectFeedEntriesChanged(QModelIndex newFeed, QModelIndex
		oldFeed) {
	auto record = feedEntryModel->record(newFeed.row());
	auto field = record.field(2);
	debug()<<field.value().toString();
	ui.feedDisplay->load(field.value().toString());
	int readCnt = record.value("read").toInt() + 1;
	record.setValue("read", readCnt);
	feedEntryModel->setRecord(newFeed.row(), record);
	feedEntryModel->submitAll();
}

void RssMainWidget::selectFeedEntryChanged(QModelIndex newFeed, QModelIndex
		oldFeed) {
	auto record = feedModel->record(newFeed.row());
	debug()<<newFeed.row()<<" "<<oldFeed.row();
	auto field = record.field("id");
	debug()<<field.value();
	debug()<<record.field(1).value();
	//debug()<<QString("feed == %1").arg(field.value().toInt());
	feedEntryModel->setFilter(QString("feed = %1").
		arg(field.value().toInt()));
	debug()<<feedEntryModel->filter();
	if(!feedEntryModel->select()) {
		debug()<<db.lastError().text();
	} else {
		for(int i = 0; i < feedModel->rowCount(); i++) {
			auto name = feedModel->record(i).value("description").toString();
			debug()<<i<<name;
		}
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
		+ QLatin1String("pubData varchar, description varchar, read integer, feed integer)"))) {
		critical()<<q.lastError().text();
		return false;
	}

	return true;
}

bool RssMainWidget::addFeed(QSqlQuery& q, const QString& name, 
		const QString& url) {
	if(!q.prepare(QString("insert into feeds(name, url, unread) values(:name, :url, :count)"))) {
		critical()<<q.lastError().text();
		return false;
	}
	q.bindValue(QString(":name"), name);
	q.bindValue(QString(":url"), url);
	q.bindValue(QString(":count"), QVariant(0));
	q.exec();
	feedEntryModel->select();
	return true;
}

void RssMainWidget::onRemoveClick() {
	auto idx = ui.feedView->currentIndex();
	debug()<<idx.row();
	feedModel->removeRows(idx.row(),1);
	feedModel->select();
}

void RssMainWidget::getFeeds() {
	debug();
	QSqlQuery q("select id, url from feeds");
	while(q.next()) {
		QString id = q.value(0).toString();
		QString url = q.value(1).toString();
		getFeed(url, q.value(0).toInt());
		debug()<<id<<url;
	}
	debug()<<q.lastError().text();
	feedEntryModel->select();
}

void RssMainWidget::getFeed(const QString& url, const int feed) {
	mrss_t *data;
	mrss_error_t ret;
	//mrss_hour_t *hour;
	//mrss_day_t *day;
	//mrss_category_t *category;
	mrss_item_t *item;
	CURLcode code;

	// parse url
    ret = mrss_parse_url_with_options_and_error(url.toLocal8Bit().data(), 
		&data, NULL, &code);

	debug()<<ret;


	item = data->item;
	while(item) {
		QSqlQuery exists;
		if(!exists.prepare(QLatin1String("SELECT * FROM feedentries WHERE feed = :feed AND title = :title"))) {
			critical()<<"something went wrong";
		}
		exists.bindValue(":feed", QVariant(feed));
		exists.bindValue(":title", QString(item->title));
		exists.exec();
		/*if(!exists.exec()) {
			critical()<<db.lastError().text();
		}*/
		critical()<<db.lastError().text()<<exists.lastQuery();
		if(!exists.next()) {
			debug()<<"here";
			QSqlQuery insert;
			insert.prepare(
				QLatin1String("INSERT INTO feedentries(title, link, pubData, description, read, feed) ") +
				QLatin1String("VALUES(:title, :link, :pubData, :desc, 0, :feed)"));

			insert.bindValue(QString(":title"), QString(item->title));
			insert.bindValue(QString(":link"), QString(item->link));
			insert.bindValue(QString(":pubData"), QString(item->pubDate));
			insert.bindValue(QString(":desc"), QString(item->description));
			insert.bindValue(QString(":feed"), QVariant(feed));
			if(!insert.exec()) {
				critical()<<db.lastError().text()<<insert.lastQuery();
			}
			//debug()<<"title:"<< item->title;
			//debug()<<"link:"<< item->link;
			//debug()<<"description:"<< item->description;
			//debug()<<"author:"<< item->author;
			//debug()<<"comments:"<< item->comments;
			//debug()<<"pubDate:"<< item->pubDate;
		}
		item = item->next;
	}
	db.commit();
	mrss_free (data);
}
