#include <gtkmm.h>

#include "g2cpp_mainwindow.glade.hpp"

int main(int argc, char** argv) {
	Gtk::Main kit(argc, argv);
	mainwindow g;
	Gtk::Window* w = g;
	Gtk::Main::run(*w);
	return 0;
}
