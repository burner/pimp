#ifndef CONTACTSMAINWIDGET
#define CONTACTSMAINWIDGET

#include <ui_contactsmainwidget.h>

class ContactsMainWidget : public QWidget {
	Q_OBJECT
	public:
		ContactsMainWidget(QWidget* parent = NULL);

	private:
		Ui::ContactsMainWidget ui;

};
#endif
