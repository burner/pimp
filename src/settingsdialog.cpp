#include <settingsdialog.hpp>
#include <debug.hpp>

bool SettingsDialog::started = false;

SettingsDialog::SettingsDialog(QWidget* parent) : QDialog(parent) {
	ui.setupUi(this);
	QObject::connect(ui.acceptButton, SIGNAL(clicked()), this, 
		SLOT(onAcceptClick()));
	QObject::connect(ui.resetButton, SIGNAL(clicked()), this, 
		SLOT(onResetClick()));
	QObject::connect(ui.exitButton, SIGNAL(clicked()), this, 
		SLOT(onExitClick()));
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
