#ifndef NEWFEEDDIALOG
#define NEWFEEDDIALOG

#include <QDialog>
#include <QWidget>
#include <ui_newfeeddialog.h>

class NewFeedDialog : public QDialog {
	Q_OBJECT
	public:
		NewFeedDialog(QWidget* parent = NULL);

	private:
		Ui::NewFeedDialog ui;

	private slots:
		void onOKClick();
		void onCancelClick();

	signals:
		void createNewFeed(const QString,const QString);
};
#endif
