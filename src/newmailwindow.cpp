#include <newmailwindow.hpp>
#include <debug.hpp>

NewMailWindow::NewMailWindow(QWidget* parent) : QMainWindow(parent) {
	ui.setupUi(this);

	QObject::connect(ui.sendButton, SIGNAL(clicked()), this, 
		SLOT(sendButtonClick()));
}


void NewMailWindow::sendButtonClick() {
	debug()<<"Here";
	LOG("%s", "here also");
}
