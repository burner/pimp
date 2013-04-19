#include <sstream>
#include <vte/vte.h>

#include <logger.hpp>
#include <unit.hpp>

#include <vimdialog/vimdialog.hpp>
#include <uniquename.hpp>

#pragma GCC diagnostic ignored "-Wpmf-conversions"

VimDialog::VimDialog(Gtk::Entry* e) : entry(e), textView(nullptr) {
	buildVimTerm();
}

VimDialog::VimDialog(Gtk::TextView* t) : entry(nullptr), textView(t) {
	buildVimTerm();
}

static void termExitCcallback(Gtk::Widget* w, gpointer Th) {
	VimDialog* This = reinterpret_cast<VimDialog*>(Th);
	This->termExit();
}

void VimDialog::buildVimTerm() {
	// make a new name
	this->filename = UniqueName::getName();

	auto term = vte_terminal_new();
	char* startterm[3] = {0,0,0};
	int pid;
	std::string cmdStr("vim");
	char* cTmp = const_cast<char*>(cmdStr.c_str());
	startterm[0] = const_cast<char*>(cTmp);
	startterm[1] = const_cast<char*>(this->filename.c_str());

	vte_terminal_fork_command_full(VTE_TERMINAL(term), VTE_PTY_DEFAULT,
		"~", &startterm[0], NULL, static_cast<GSpawnFlags>(
			G_SPAWN_DO_NOT_REAP_CHILD | G_SPAWN_SEARCH_PATH
		), NULL, NULL, &pid, NULL);

	termW = Glib::wrap(term);
	vbox->pack_start(*termW);

	g_signal_connect(term, "child_exited", G_CALLBACK(termExitCcallback), this);

	okButton->signal_clicked().connect(sigc::mem_fun(
		this, &VimDialog::termExit
	));
	dialog1->show_all();
}

void VimDialog::termExit() {
	LOG();
	std::ifstream f(this->filename.c_str(), std::ios::in);
	std::stringstream ss;

	std::string line;
	char endchar = entry ? ' ' : '\n';
	while(getline(f, line)) {
		ss<<line<<endchar;
	}

	std::string newText = ss.str();
	newText.resize(newText.size()-1);
	//LOG("\"%s\"", newText);
	if(entry) {
		entry->set_text(newText);
		remove(this->filename.c_str());
	} else if(textView) {
		textView->get_buffer()->set_text(newText);
		remove(this->filename.c_str());
	} else {
		WARN("entry and textview null");
	}
	
	dialog1->hide();
	_builder.clear();
	delete this;
}

void VimDialog::show() {
	dialog1->show();
}
