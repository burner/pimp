#include <mailmainwidget.hpp>
#include <debug.hpp>
#include <newmailwindow.hpp>
#include <stdio.h>

MailMainWidget::MailMainWidget(QWidget* parent) : QWidget(parent) {
	ui.setupUi(this);
	QObject::connect(ui.newMailButton, SIGNAL(clicked()), this, 
		SLOT(newMail()));
}

void MailMainWidget::newMail() {
	debug()<<"here";
	NewMailWindow* nmw = new NewMailWindow(this);
	nmw->show();
}
