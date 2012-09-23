#include <configmainwidget.hpp>
#include <debug.hpp>

ConfigMainWidget::ConfigMainWidget(SettingsDialog* parent) : QWidget(parent),
		par(parent) {
	ui.setupUi(this);
	
	QObject::connect(ui.newMailButton, SIGNAL(clicked()), par, 
		SLOT(setNewMailAccountWidget()));
}
