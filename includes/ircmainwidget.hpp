#ifndef IRCMAINWIDGET
#define IRCMAINWIDGET

#include <QWidget>
#include <ui_ircmainwidget.h>

class IrcMainWidget : public QWidget {
	Q_OBJECT
	public:
		IrcMainWidget(QWidget* parent = NULL);

	private:
		Ui::IrcMainWidget ui;

};
#endif
