#include <stdlib.h>
#include <mainwindow/mainwindow.hpp>

MainWindow::MainWindow() {
	pimpCloseMenuItem->signal_activate().connect(sigc::ptr_fun(
		&MainWindow::quitPimp
	));
}

void MainWindow::quitPimp() {
	Gtk::Main::quit();
	exit(0);
}
