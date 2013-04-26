#ifndef MAILMAINWIDGET
#define MAILMAINWIDGET

#include <QWidget>
#include <ui_mailmainwidget.h>

class MailMainWidget : public QWidget {
	Q_OBJECT
	public:
		MailMainWidget(QWidget* parent = NULL);

	private:
		Ui::MailMainWidget ui;
};
#endif
