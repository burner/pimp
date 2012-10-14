#include <calendarmainwidget.hpp>
#include <contactsmainwidget.hpp>
#include <debug.hpp>
#include <instantmainwidget.hpp>
#include <ircmainwidget.hpp>
#include <loggingmainwidget.hpp>
#include <mailmainwidget.hpp>
#include <main.hpp>
#include <mainwindow.hpp>
#include <rssmainwidget.hpp>
#include <summarymainwidget.hpp>
#include <todomainwidget.hpp>
#include <settingsdialog.hpp>
#include <twitter/tmainwindow.h>

#include <QIcon>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
	ui.setupUi(this);
	QObject::connect(ui.actionGetAll, SIGNAL(triggered()),
		this, SLOT(getAll()));
	QObject::connect(ui.action_Settings, SIGNAL(triggered()),
		this, SLOT(configDialog()));

	// add tab widgets
	auto logger = new LoggingMainWidget(this);
	ui.tabWidget->addTab(new SummaryMainWidget(), QIcon(":/icons/lazy"), 
		tr("&Summary"));
	ui.tabWidget->addTab(new MailMainWidget(), QIcon(":/icons/letter"), 
		tr("&Mail"));
	ui.tabWidget->addTab(new CalendarMainWidget(), QIcon(":/icons/book"), 
		tr("&Calendar"));
	ui.tabWidget->addTab(new ContactsMainWidget(), QIcon(":/icons/people"), 
		tr("C&ontacts"));
	ui.tabWidget->addTab(new InstantMainWidget(), QIcon(":/icons/hands"), 
		tr("&Instant"));
	ui.tabWidget->addTab(new TMainWindow(), QIcon(":/icons/smile"), 
		tr("T&witter"));
	ui.tabWidget->addTab(new IrcMainWidget(), QIcon(":/icons/trash"), 
		tr("I&rc"));
	auto rssWidget = new RssMainWidget(this);
	ui.tabWidget->addTab(rssWidget, QIcon(":/icons/rss"), tr("&RSS"));
	ui.tabWidget->addTab(new TodoMainWidget(), QIcon(":/icons/wrench"), 
		tr("&Todo"));
	ui.tabWidget->addTab(logger, QIcon(":/icons/dog"), tr("&Logggin"));
}

void MainWindow::getAll() {
	debug()<<"getAll stub";
	return;
}

void MainWindow::configDialog() {
	auto sd = new SettingsDialog(this);	
	sd->showConditional();
}
