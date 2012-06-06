#include <rssmainwidget.hpp>
#include <rsslogic.hpp>
#include <debug.hpp>

RssMainWidget::RssMainWidget(QWidget* parent) : QWidget(parent) {
	ui.setupUi(this);
}

void RssMainWidget::init() {
	bool initDBsucc = initDB();
	if(!initDBsucc) {
		debug()<<"Rss database init failed, that means the rss widget might not work";
	} else {
		debug()<<"Rss database init worked";	
	}
}
