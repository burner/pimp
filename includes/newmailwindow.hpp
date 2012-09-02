#ifndef NEWMAILWINDOW
#define NEWMAILWINDOW

#include <QMainWindow>
#include <QWidget>
#include <ui_newmailwindow.h>

class NewMailWindow : public QMainWindow {
	public:
		NewMailWindow(QWidget* parent = NULL);

	private:
		Ui::NewMailWindow ui;

	private slots:
		void sendClick();

};
#endif
