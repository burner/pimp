#include <newfeeddialog.hpp>
#include <rssmainwidget.hpp>

NewFeedDialog::NewFeedDialog(QWidget* parent) : QDialog(parent) {
	ui.setupUi(this);
	QObject::connect(ui.okButton, SIGNAL(clicked()), this, SLOT(onOKClick()));
	QObject::connect(ui.cancelButton, SIGNAL(clicked()), this, 
		SLOT(onCancelClick()));

	QObject::connect(this, SIGNAL(createNewFeed(const QString, const QString)), 
		static_cast<RssMainWidget*>(parent), 
		SLOT(insertNewFeed(const QString, const QString)));
}


void NewFeedDialog::onOKClick() {
	emit createNewFeed(ui.feedNameLineEdit->text(), ui.feedUrlLineEdit->text());
	emit accept();
}

void NewFeedDialog::onCancelClick() {
	emit reject();
}
