#ifndef TODOMAINWIDGET
#define TODOMAINWIDGET

#include <ui_todomainwidget.h>

class TodoMainWidget : public QWidget {
	Q_OBJECT
	public:
		TodoMainWidget(QWidget* parent = NULL);

	private:
		Ui::TodoMainWidget ui;

};
#endif
