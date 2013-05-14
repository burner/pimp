#include <QIcon>
#include <QThread>

#include <logger.hpp>

#include <mainwindow/mainwindow.hpp>
#include <mailwidget/mailmainwidget.hpp>
#include <vimdialog/vimdialog.hpp>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
	ui.setupUi(this);

	connect(ui.actionGetAll, &QAction::triggered, 
		this, &MainWindow::getAll
	);

	connect(ui.action_Settings, &QAction::triggered,
		this, &MainWindow::vimTest
	);
	connect(ui.action_VimEdit, &QAction::triggered,
		this, &MainWindow::vimEdit
	);

	// add tab widgets
	ui.tabWidget->addTab(new MailMainWidget(), QIcon(":/icons/letter"), 
		tr("&Mail"));
	/*
	auto logger = new LoggingMainWidget(this);
	ui.tabWidget->addTab(new SummaryMainWidget(), QIcon(":/icons/lazy"), 
		tr("&Summary"));
	ui.tabWidget->addTab(new CalendarMainWidget(), QIcon(":/icons/book"), 
		tr("&Calendar"));
	ui.tabWidget->addTab(new ContactsMainWidget(), QIcon(":/icons/people"), 
		tr("C&ontacts"));
	ui.tabWidget->addTab(new InstantMainWidget(), QIcon(":/icons/hands"), 
		tr("&Instant"));
	ui.tabWidget->addTab(new IrcMainWidget(), QIcon(":/icons/trash"), 
		tr("I&rc"));
	auto rssWidget = new RssMainWidget(this);
	ui.tabWidget->addTab(rssWidget, QIcon(":/icons/rss"), tr("&RSS"));
	ui.tabWidget->addTab(new TodoMainWidget(), QIcon(":/icons/wrench"), 
		tr("&Todo"));
	ui.tabWidget->addTab(logger, QIcon(":/icons/dog"), tr("&Logggin"));
	*/
}

void MainWindow::getAll() {
	LOG("getAll");
	return;
}

void MainWindow::vimEdit() {
	LOG("vim test");
	//QThread* t = new QThread;
	VimDialog* vd = new VimDialog(new QLineEdit(this));
	vd->process();
	//vd->moveToThread(t);
	//connect(t, &QThread::started, vd, &VimDialog::process);
	//connect(vd, SIGNAL(finished()), t, SLOT(quit()));
	//connect(vd, SIGNAL(finished()), vd, SLOT(deleteLater()));
	//connect(t, SIGNAL(finished()), t, SLOT(deleteLater()));
	//t->start();
	return;
}

void MainWindow::vimTest() {
	LOG("vim test");
	//QThread* t = new QThread;
	VimDialog* vd = new VimDialog(new QLineEdit(this));
	vd->process();
	//vd->moveToThread(t);
	//connect(t, &QThread::started, vd, &VimDialog::process);
	//connect(vd, SIGNAL(finished()), t, SLOT(quit()));
	//connect(vd, SIGNAL(finished()), vd, SLOT(deleteLater()));
	//connect(t, SIGNAL(finished()), t, SLOT(deleteLater()));
	//t->start();
	return;
}
