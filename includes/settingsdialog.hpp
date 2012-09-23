#ifndef SETTINGSDIALOG
#define SETTINGSDIALOG

#include <QDialog>
#include <QWidget>
#include <QTreeWidgetItem>
#include <ui_config.h>

class SettingsDialog : public QDialog {
	Q_OBJECT
	public:
		SettingsDialog(QWidget* parent = NULL);
		void showConditional();

	private:
		Ui::Config ui;
		static bool started;
		QWidget* activeWidget;

		QTreeWidgetItem* summaryTopItem;
		QTreeWidgetItem* emailTopItem;
		QTreeWidgetItem* calendarTopItem;
		QTreeWidgetItem* contactTopItem;
		QTreeWidgetItem* rssTopItem;
		QTreeWidgetItem* todoTopItem;


	private slots:
		void onResetClick();
		void onExitClick();
		void onAcceptClick();

	public slots:
		void setNewMailAccountWidget();

};
#endif
