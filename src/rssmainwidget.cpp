#include <rssmainwidget.hpp>
#include <newfeeddialog.hpp>
#include <rsslogic.hpp>
#include <debug.hpp>

RssMainWidget::RssMainWidget(QWidget* parent) : QWidget(parent) {
	ui.setupUi(this);
	QObject::connect(ui.newFeedButton, SIGNAL(clicked()), this, SLOT(newFeed()));
	this->init();
	ui.feedView->setColumnHidden(feedModel->fieldIndex("id"),true);
	ui.feedView->setColumnHidden(feedModel->fieldIndex("url"),true);
}

void RssMainWidget::init() {
	bool initDBsucc = initDB();
	if(!initDBsucc) {
		debug()<<"Rss database init failed, that means the"
			<<"rss widget might not work";
		return;
	} else {
		debug()<<"Rss database init worked";	
		feedModel = new QSqlRelationalTableModel(ui.feedView);
		feedModel->setTable("feeds");
		if(!feedModel->select()) {
			critical()<<feedModel->lastError();
		}
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
	db.open();
 	debug()<<name<<url;
	QSqlQuery query;
	addFeed(query, name, url);
	db.close();
}
