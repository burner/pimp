#include <stdlib.h>
#include <vte/vte.h>

#include <mainwindow/mainwindow.hpp>
#include <vimdialog/vimdialog.hpp>

#include <logger.hpp>

MainWindow::MainWindow() {
	auto startVimAccel = Gtk::AccelGroup::create();
	Gtk::Window * tWin = window1;
	tWin->add_accel_group(startVimAccel);

	tWin->signal_key_press_event().connect(sigc::mem_fun(
		this, &MainWindow::spawnVimOnCurrent), false
	);

	pimpCloseMenuItem->signal_activate().connect(sigc::ptr_fun(
		&MainWindow::quitPimp
	));
}

void MainWindow::quitPimp() {
	Gtk::Main::quit();
	exit(0);
}

bool MainWindow::spawnVimOnCurrent(GdkEventKey* const& event) {
	if(event->keyval == GDK_KEY_m && (event->state & GDK_CONTROL_MASK)) {
		LOG("Control-M was pressed");
		Gtk::Widget* focus = window1->get_focus();
		if(dynamic_cast<Gtk::TextView*>(focus) != nullptr) {
			LOG("text view");
			auto vd = new VimDialog(dynamic_cast<Gtk::TextView*>(focus));
			vd->show();
		} else if(dynamic_cast<Gtk::Entry*>(focus) != nullptr) {
			LOG("entry");
			auto vd = new VimDialog(dynamic_cast<Gtk::Entry*>(focus));
			vd->show();
		}
		return false;
	}
	return false;
}
