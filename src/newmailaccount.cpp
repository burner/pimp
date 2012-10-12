#include <newmailaccount.hpp>
#include <debug.hpp>
#include <settings.hpp>

NewMailAccount::NewMailAccount(SettingsDialog* parent) : QWidget(parent),
		par(parent) {
	ui.setupUi(this);
}

void NewMailAccount::write() {
	EmailSettings set;
	set.emailadr = ui.emailAddressLine->text().toStdString();
	set.username = ui.usernameLine->text().toStdString();
	set.password = ui.passwordLine->text().toStdString();

	set.incommingType = ui.incommingType->currentText().toStdString();
	set.incommingPort = ui.incommingPort->text().toInt();
	set.incommingUrl = ui.incommingUrl->text().toStdString();
	set.incommingSASL = ui.incommingSASL->checkState();
	set.incommingSASLFallback = ui.incommingSASLFallback->checkState();
	set.incommingTLS = ui.incommingTLS->checkState();
	set.incommingTLSrequired = ui.incommingTLSrequired->checkState();
	set.incommingRootpath = ui.incommingRootpath->text().toStdString();

	set.outgoingType = ui.outgoingType->currentText().toStdString();
	set.outgoingPort = ui.outgoingPort->text().toInt();
	set.outgoingUrl = ui.outgoingUrl->text().toStdString();
	set.outgoingSASL = ui.outgoingSASL->checkState();
	set.outgoingSASLFallback = ui.outgoingSASLFallback->checkState();
	set.outgoingTLS = ui.outgoingTLS->checkState();
	set.outgoingTLSrequired = ui.outgoingTLSrequired->checkState();
	set.outgoingRootpath = ui.outgoingRootpath->text().toStdString();

	Settings::newEmailInfo(set);
	emit par->loadEmailAccounts();
}
