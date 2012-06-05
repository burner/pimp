#include <loggingmainwidget.hpp>

LoggingMainWidget* LoggingMainWidget::instance;

LoggingMainWidget::LoggingMainWidget(QWidget* parent) : QWidget(parent) {
	ui.setupUi(this);
	LoggingMainWidget::instance = this;
	qInstallMsgHandler(LoggingMainWidget::loggingFunction);

	QObject::connect(LoggingMainWidget::instance, 
		SIGNAL(messageEmit(const QString&)),
		ui.loggingTextBox, SLOT(appendPlainText(const QString&)));
}


void LoggingMainWidget::loggingFunction(QtMsgType type, const char* msg) {
	QString str(msg);
	emit instance->messageEmit(str);
}
