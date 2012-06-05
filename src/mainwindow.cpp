#include <QDebug>

#include <main.hpp>
#include <mainwindow.hpp>
#include <mailmainwidget.hpp>
#include <summarymainwidget.hpp>
#include <instantmainwidget.hpp>
#include <ircmainwidget.hpp>
#include <todomainwidget.hpp>
#include <calendarmainwidget.hpp>
#include <contactsmainwidget.hpp>
#include <loggingmainwidget.hpp>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
	ui.setupUi(this);
	QObject::connect(ui.actionGetAll, SIGNAL(triggered()),
		this, SLOT(getAll()));

	// add tab widgets
	ui.tabWidget->addTab(new SummaryMainWidget(), tr("&Summary"));
	ui.tabWidget->addTab(new MailMainWidget(), tr("&Mail"));
	ui.tabWidget->addTab(new CalendarMainWidget(), tr("&Calendar"));
	ui.tabWidget->addTab(new ContactsMainWidget(), tr("C&ontacts"));
	ui.tabWidget->addTab(new InstantMainWidget(), tr("&Instant"));
	ui.tabWidget->addTab(new IrcMainWidget(), tr("I&rc"));
	ui.tabWidget->addTab(new TodoMainWidget(), tr("&Todo"));
	ui.tabWidget->addTab(new LoggingMainWidget(), tr("&Logggin"));
}

void MainWindow::getAll() {
	return;
}
