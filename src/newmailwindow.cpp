#include <newmailwindow.hpp>
#include <debug.hpp>

NewMailWindow::NewMailWindow(QWidget* parent) : QMainWindow(parent) {
	ui.setupUi(this);
	ui.webView->page()->setContentEditable(true);

	// init the zoom slider correctly
    ui.zoomSlider->setMaximumWidth(150);
    ui.zoomSlider->setRange(25, 400);
    ui.zoomSlider->setSingleStep(25);
    ui.zoomSlider->setPageStep(100);
    ui.zoomSlider->setValue(100);

	QObject::connect(ui.sendButton, SIGNAL(clicked()), this, 
		SLOT(sendButtonClick()));
	QObject::connect(ui.action_Quit, SIGNAL(triggered()), this, 
		SLOT(closeCheck()));
    QObject::connect(ui.zoomOutButton, SIGNAL(clicked()), this,
		SLOT(zoomOut()));
    QObject::connect(ui.zoomInButton, SIGNAL(clicked()), this,
		SLOT(zoomIn()));
    QObject::connect(ui.zoomSlider, SIGNAL(valueChanged(int)), 
		SLOT(changeZoom(int)));
}


void NewMailWindow::sendButtonClick() {
	debug()<<"Here";
	LOG("%s", "here also");
}

void NewMailWindow::closeCheck() {
	LOG("here");
	close();
}

void NewMailWindow::zoomOut() {
	int percent = static_cast<int>(ui.webView->zoomFactor() * 100);
	if(percent > 25) {
		percent -= 25;
		percent = 25 * (int((percent + 25 - 1) / 25));
		qreal factor = static_cast<qreal>(percent) / 100;
		LOG("zoom factor %f", static_cast<double>(factor));
		ui.webView->setZoomFactor(factor);
		ui.zoomOutButton->setEnabled(percent > 25);
		ui.zoomInButton->setEnabled(true);
		ui.zoomSlider->setValue(percent);
	}
}

void NewMailWindow::zoomIn() {
	int percent = static_cast<int>(ui.webView->zoomFactor() * 100);
	if(percent < 400) {
		percent += 25;
		percent = 25 * (int(percent / 25));
		qreal factor = static_cast<qreal>(percent) / 100;
		LOG("zoom factor %f", static_cast<double>(factor));
		ui.webView->setZoomFactor(factor);
		ui.zoomInButton->setEnabled(percent < 400);
		ui.zoomOutButton->setEnabled(true);
		ui.zoomSlider->setValue(percent);
	}
}

void NewMailWindow::changeZoom(int percent) {
    ui.zoomOutButton->setEnabled(percent > 25);
    ui.zoomInButton->setEnabled(percent < 400);
    qreal factor = static_cast<qreal>(percent) / 100;
	LOG("zoom factor %f", static_cast<double>(factor));
    ui.webView->setZoomFactor(factor);

    ui.zoomSlider->setValue(percent);
}
