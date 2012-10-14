#ifndef NEWMAILACCOUNTNWIDGET
#define NEWMAILACCOUNTNWIDGET

#include <QWidget>
#include <ui_mailaccount.h>
#include <settingsdialog.hpp>

class NewMailAccount : public QWidget {
	Q_OBJECT
	public:
		NewMailAccount(SettingsDialog* parent = NULL);

	private:
		Ui::MailAccountWidget ui;
		SettingsDialog* par;

	public slots:
		void write();
};
#endif
