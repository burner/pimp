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
	QString str;
	switch(type) {
		case QtDebugMsg:
			str = QString("[   Debug: ");
			break;
		case QtWarningMsg:
			str = QString("[ Warning: ");
			break;
		case QtCriticalMsg:
			str = QString("[Critical: ");
			break;
		case QtFatalMsg:
			str = QString("[   Fatal:");
			break;
	}
	str.append(QTime::currentTime().toString());
	str.append(" ");
	str.append(msg);
	
	emit instance->messageEmit(str);
}
