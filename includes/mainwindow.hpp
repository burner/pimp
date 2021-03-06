#ifndef MAINWINDOW
#define MAINWINDOW

#include <QMainWindow>
#include <ui_mainwindow.h>

class MainWindow : public QMainWindow {
	Q_OBJECT
	public:
		MainWindow(QWidget* parent = NULL);

	private:
		Ui::MainWindow ui;

	private slots:
		void getAll();
		void configDialog();

};
#endif
