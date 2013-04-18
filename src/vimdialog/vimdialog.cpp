#include <vimdialog/vimdialog.hpp>
#include <logger.hpp>

VimDialog::VimDialog(Gtk::Entry* e) : entry(e), textView(nullptr) {
	LOG();
}

VimDialog::VimDialog(Gtk::TextView* t) : entry(nullptr), textView(t) {
	LOG();
}

void VimDialog::show() {
	LOG();
	dialog1->show();
}
