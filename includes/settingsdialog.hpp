#ifndef SETTINGSDIALOG
#define SETTINGSDIALOG

#include <QDialog>
#include <QWidget>
#include <ui_config.h>

class SettingsDialog : public QDialog {
	Q_OBJECT
	public:
		SettingsDialog(QWidget* parent = NULL);
		void showConditional();

	private:
		Ui::Config ui;
		static bool started;

	private slots:
		void onResetClick();
		void onExitClick();
		void onAcceptClick();

};
#endif
