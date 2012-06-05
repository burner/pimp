#ifndef LOGGINGMAINWIDGET
#define LOGGINGMAINWIDGET

#include <ui_loggingmainwidget.h>

class LoggingMainWidget : public QWidget {
	Q_OBJECT
	public:
		LoggingMainWidget(QWidget* parent = NULL);

	private:
		Ui::LoggingMainWidget ui;

};
#endif
