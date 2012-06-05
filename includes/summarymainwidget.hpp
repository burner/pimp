#ifndef SUMMARYMAINWIDGET
#define SUMMARYMAINWIDGET

#include <QWidget>
#include <ui_summarymainwidget.h>

class SummaryMainWidget : public QWidget {
	Q_OBJECT
	public:
		SummaryMainWidget(QWidget* parent = NULL);

	private:
		Ui::SummaryMainWidget ui;

};
#endif
