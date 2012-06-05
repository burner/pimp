#ifndef CALENDARMAINWIDGET
#define CALENDARMAINWIDGET

#include <QWidget>
#include <ui_calendarmainwidget.h>

class CalendarMainWidget : public QWidget {
	Q_OBJECT
	public:
		CalendarMainWidget(QWidget* parent = NULL);

	private:
		Ui::CalendarMainWidget ui;

};
#endif
