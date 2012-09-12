#ifndef NEWMAILWINDOW
#define NEWMAILWINDOW

#include <QMainWindow>
#include <ui_newmailwindow.h>

class NewMailWindow : public QMainWindow {
	Q_OBJECT
	public:
		NewMailWindow(QWidget* parent = NULL);

	private:
		Ui::NewMailWindow ui;

	private slots:
		void sendButtonClick();

};
#endif
