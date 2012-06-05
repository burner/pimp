#include <loggingmainwidget.hpp>
#include <stdio.h>
#include <QTime>

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
	QString str = QString("[%7s %9s] %s").arg(type == QtDebugMsg ? "Debug" :
		type == QtWarningMsg ? "Warning" : type == QtCriticalMsg ? "Critical" :
		type == QtFatalMsg ? "Fatal" : "Unknown",
		QTime::currentTime().toString(), msg);
	printf("here\n");
	
	emit instance->messageEmit(str);
}
