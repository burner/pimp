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
#include <debug.hpp>

#include <QIcon>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
	ui.setupUi(this);
	QObject::connect(ui.actionGetAll, SIGNAL(triggered()),
		this, SLOT(getAll()));

	// add tab widgets
	ui.tabWidget->addTab(new SummaryMainWidget(), QIcon(":/icons/lazy"), tr("&Summary"));
	ui.tabWidget->addTab(new MailMainWidget(), QIcon(":/icons/letter"), tr("&Mail"));
	ui.tabWidget->addTab(new CalendarMainWidget(), QIcon(":/icons/book"), tr("&Calendar"));
	ui.tabWidget->addTab(new ContactsMainWidget(), QIcon(":/icons/people"), tr("C&ontacts"));
	ui.tabWidget->addTab(new InstantMainWidget(), QIcon(":/icons/hands"), tr("&Instant"));
	ui.tabWidget->addTab(new IrcMainWidget(), QIcon(":/icons/trash"), tr("I&rc"));
	ui.tabWidget->addTab(new TodoMainWidget(), QIcon(":/icons/wrench"), tr("&Todo"));
	ui.tabWidget->addTab(new LoggingMainWidget(), QIcon(":/icons/dog"), tr("&Logggin"));
}

void MainWindow::getAll() {
	debug()<<"getAll stub";
	return;
}
