#include <fstream>
#include <gtkmm.h>

#include <mainwindow/mainwindow.hpp>

#include <unit.hpp>

// load whatever theme is found in the current folder
static void loadOxygenTheme() {
	std::ifstream gtkSymLink("gtk-3.0");
	if(gtkSymLink) {
		auto screen = Gdk::Screen::get_default();
		auto css_provider = Gtk::CssProvider::create();
		css_provider->load_from_path("gtk-3.0/gtk.css");
		auto context = Gtk::StyleContext::create();
		context->add_provider_for_screen(screen, css_provider, 800);
	}
}

int main(int argc, char** argv) {
	Unit::runTests();
	Gtk::Main kit(argc, argv);
	loadOxygenTheme();
	MainWindow mw;
	Gtk::Window* w = mw;
	Gtk::Main::run(*w);
	return 0;
}
