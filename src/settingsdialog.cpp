#include <QTreeWidget>
#include <settingsdialog.hpp>
#include <debug.hpp>
#include <settings.hpp>
#include <configmainwidget.hpp>
#include <newmailaccount.hpp>

bool SettingsDialog::started = false;

SettingsDialog::SettingsDialog(QWidget* parent) : QDialog(parent) {
	ui.setupUi(this);
	activeWidget = new ConfigMainWidget(this);
	ui.rightLayout->insertWidget(0, activeWidget);
	QObject::connect(ui.acceptButton, SIGNAL(clicked()), this, 
		SLOT(loadEmailAccounts()));
	QObject::connect(ui.resetButton, SIGNAL(clicked()), this, 
		SLOT(onResetClick()));
	QObject::connect(ui.exitButton, SIGNAL(clicked()), this, 
		SLOT(onExitClick()));

	ui.treeWidget->setColumnCount(1);
	summaryTopItem = new QTreeWidgetItem(ui.treeWidget,
		QStringList("Summary"));
	emailTopItem = new QTreeWidgetItem(ui.treeWidget,
		QStringList("Email"));
	calendarTopItem = new QTreeWidgetItem(ui.treeWidget,
		QStringList("Calendar"));
	contactTopItem = new QTreeWidgetItem(ui.treeWidget,
		QStringList("Contact"));
	todoTopItem = new QTreeWidgetItem(ui.treeWidget,
		QStringList("Todo"));

	ui.treeWidget->addTopLevelItem(summaryTopItem);

	ui.treeWidget->addTopLevelItem(emailTopItem);
	this->loadEmailAccounts();

	ui.treeWidget->addTopLevelItem(calendarTopItem);
	ui.treeWidget->addTopLevelItem(contactTopItem);
	ui.treeWidget->addTopLevelItem(todoTopItem);
	
}

void SettingsDialog::loadEmailAccounts() {
	LOG();
	qDeleteAll(emailTopItem->takeChildren());
	for(auto it : Settings::emailAddress()) {
		LOG("%s", it);
		new QTreeWidgetItem(emailTopItem, QStringList(
			QString::fromStdString(it))
		);
	}
}

void SettingsDialog::showConditional() {
	if(!started) {
		SettingsDialog::started = true;
		this->show();
	} else {
		LOG("idiot setting dialog can be started only once");
	}
}

void SettingsDialog::onExitClick() {
	SettingsDialog::started = false;
	this->close();
}

void SettingsDialog::onResetClick() {
}

void SettingsDialog::onAcceptClick() {
}

void SettingsDialog::setNewMailAccountWidget() {
	ui.rightLayout->removeWidget(activeWidget);
	delete activeWidget;
	activeWidget = new NewMailAccount(this);
	ui.rightLayout->insertWidget(0, activeWidget);
	QObject::connect(ui.acceptButton, SIGNAL(clicked()), activeWidget, 
		SLOT(write()));
}
