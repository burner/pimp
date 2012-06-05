#ifndef LOGGINGMAINWIDGET
#define LOGGINGMAINWIDGET

#include <ui_loggingmainwidget.h>

class LoggingMainWidget : public QWidget {
	Q_OBJECT
	public:
		LoggingMainWidget(QWidget* parent = NULL);

		static LoggingMainWidget* getInstance();
		static void loggingFunction(QtMsgType type, const char* msg);

	private:
		static LoggingMainWidget* instance;
		Ui::LoggingMainWidget ui;

	signals:
		void messageEmit(const QString& msg);

};
#endif
