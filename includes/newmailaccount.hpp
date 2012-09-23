#ifndef NEWMAILACCOUNTNWIDGET
#define NEWMAILACCOUNTNWIDGET

#include <QWidget>
#include <ui_mailaccount.h>

class NewMailAccount : public QWidget {
	Q_OBJECT
	public:
		NewMailAccount(QWidget* parent = NULL);

	private:
		Ui::MailAccountWidget ui;

	public slots:
		void write();
};
#endif
