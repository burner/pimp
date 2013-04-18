#ifndef VIMDIALOG_HPP
#define VIMDIALOG_HPP

#include <g2cpp_vimdialog.glade.hpp>

class VimDialog : public vimdialog {
public:
	VimDialog(Gtk::Entry*);
	VimDialog(Gtk::TextView*);

	void show();
private:
	Gtk::Entry* entry;
	Gtk::TextView* textView;
};

#endif
