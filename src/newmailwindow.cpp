#include <newmailwindow.hpp>
#include <debug.hpp>

NewMailWindow::NewMailWindow(QWidget* parent) : QMainWindow(parent) {
	ui.setupUi(this);

	QObject::connect(ui.sendButton, SIGNAL(clicked()), this, 
		SLOT(sendButtonClick()));
	QObject::connect(ui.action_Quit, SIGNAL(triggered()), this, 
		SLOT(closeCheck()));
}


void NewMailWindow::sendButtonClick() {
	debug()<<"Here";
	LOG("%s", "here also");
}

void NewMailWindow::closeCheck() {
	LOG("here");
	close();
}
