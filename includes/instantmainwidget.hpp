#ifndef INSTANTMAINWIDGET
#define INSTANTMAINWIDGET

#include <QWidget>
#include <ui_instantmainwidget.h>

class InstantMainWidget : public QWidget {
	Q_OBJECT
	public:
		InstantMainWidget(QWidget* parent = NULL);

	private:
		Ui::InstantMainWidget ui;

};
#endif
