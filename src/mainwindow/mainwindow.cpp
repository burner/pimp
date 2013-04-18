#include <stdlib.h>
#include <mainwindow/mainwindow.hpp>
#include <vte/vte.h>

#include <vimdialog/vimdialog.hpp>

#include <logger.hpp>

#pragma GCC diagnostic ignored "-Wpmf-conversions"

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

	auto term = vte_terminal_new();
	char* startterm[2] = {0,0};
	int pid;
	startterm[0] = const_cast<char*>("vim");
	vte_terminal_fork_command_full(VTE_TERMINAL(term), VTE_PTY_DEFAULT,
		"~", &startterm[0], NULL, static_cast<GSpawnFlags>(
			G_SPAWN_DO_NOT_REAP_CHILD | G_SPAWN_SEARCH_PATH
		), NULL, NULL, &pid, NULL);

	LOG("pid %d", pid);

	Gtk::Widget* termW = Glib::wrap(term);
	mailMainBox->pack_start(*termW);
	termW->show();
	g_signal_connect(term, "child_exited", G_CALLBACK(reinterpret_cast<void(*)()>(
		&MainWindow::termExit)), this
	);
}

void MainWindow::quitPimp() {
	Gtk::Main::quit();
	exit(0);
}

void MainWindow::termExit() {
	LOG("args");
}

bool MainWindow::spawnVimOnCurrent(GdkEventKey* const& event) {
	if(event->keyval == GDK_KEY_m && (event->state & GDK_CONTROL_MASK)) {
		LOG("Control-M was pressed");
		Gtk::Widget* focus = window1->get_focus();
		if(dynamic_cast<Gtk::TextView*>(focus) != nullptr) {
			LOG("text view");
		} else if(dynamic_cast<Gtk::Entry*>(focus) != nullptr) {
			LOG("entry");
		}
		return false;
	}
	return false;
}
