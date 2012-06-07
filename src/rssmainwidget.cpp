#include <rssmainwidget.hpp>
#include <newfeeddialog.hpp>
#include <rsslogic.hpp>
#include <debug.hpp>

RssMainWidget::RssMainWidget(QWidget* parent) : QWidget(parent) {
	ui.setupUi(this);
	QObject::connect(ui.newFeedButton, SIGNAL(clicked()), this, SLOT(newFeed()));
}

void RssMainWidget::init() {
	bool initDBsucc = initDB();
	if(!initDBsucc) {
		debug()<<"Rss database init failed, that means the rss widget might not work";
	} else {
		debug()<<"Rss database init worked";	
	}
}

void RssMainWidget::newFeed() {
	debug()<<"here";
	NewFeedDialog newFeed(this);
	newFeed.exec();	
}

void RssMainWidget::insertNewFeed(const QString name, const QString url) {
 	debug()<<name<<url;
}
