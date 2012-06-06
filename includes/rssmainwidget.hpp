#ifndef RSSMAINWIDGET
#define RSSMAINWIDGET

#include <QWidget>
#include <ui_rssmainwidget.h>

class RssMainWidget : public QWidget {
	Q_OBJECT
	public:
		RssMainWidget(QWidget* parent = NULL);
		void init();

	private:
		Ui::RssMainWidget ui;

};
#endif
