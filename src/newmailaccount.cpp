#include <newmailaccount.hpp>
#include <debug.hpp>

NewMailAccount::NewMailAccount(QWidget* parent) : QWidget(parent) {
	ui.setupUi(this);
}

void NewMailAccount::write() {
	LOG();
}
