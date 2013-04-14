#include <stdlib.h>
#include <mainwindow/mainwindow.hpp>
#include <vte/vte.h>

#include <logger.hpp>

static gint cb(GtkWidget *w, GdkEventAny *e, gpointer d) {
	LOG("here");
}

MainWindow::MainWindow() {
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
	g_signal_connect(term, "child_exited", G_CALLBACK(cb), this);
}

void MainWindow::quitPimp() {
	Gtk::Main::quit();
	exit(0);
}

void MainWindow::termExit() {

}
