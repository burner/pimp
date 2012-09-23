#ifndef CONFIGMAINNWIDGET
#define CONFIGMAINNWIDGET

#include <QWidget>
#include <settingsdialog.hpp>
#include <ui_configmainwidget.h>

class ConfigMainWidget : public QWidget {
	Q_OBJECT
	public:
		ConfigMainWidget(SettingsDialog* parent = NULL);

	private:
		Ui::ConfigMainWidget ui;
		SettingsDialog* par;
};
#endif
