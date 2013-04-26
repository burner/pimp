#ifndef G2CPP_VIMDIALOG_HPP
#define G2CPP_VIMDIALOG_HPP

#include <gtkmm.h>

using namespace Gtk;

class vimdialog {
	const char* glade_file = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
"<interface>"
"  <!-- interface-requires gtk+ 3.0 -->"
"  <object class=\"GtkDialog\" id=\"dialog1\">"
"    <property name=\"can_focus\">False</property>"
"    <property name=\"border_width\">5</property>"
"    <property name=\"type_hint\">dialog</property>"
"    <child internal-child=\"vbox\">"
"      <object class=\"GtkBox\" id=\"vbox\">"
"        <property name=\"can_focus\">False</property>"
"        <property name=\"orientation\">vertical</property>"
"        <property name=\"spacing\">1</property>"
"        <child internal-child=\"action_area\">"
"          <object class=\"GtkButtonBox\" id=\"dialog_action_area1\">"
"            <property name=\"can_focus\">False</property>"
"            <property name=\"layout_style\">end</property>"
"            <child>"
"              <object class=\"GtkButton\" id=\"closeButton\">"
"                <property name=\"label\" translatable=\"yes\">_Close</property>"
"                <property name=\"visible\">True</property>"
"                <property name=\"can_focus\">True</property>"
"                <property name=\"receives_default\">True</property>"
"                <property name=\"use_underline\">True</property>"
"              </object>"
"              <packing>"
"                <property name=\"expand\">False</property>"
"                <property name=\"fill\">True</property>"
"                <property name=\"position\">0</property>"
"              </packing>"
"            </child>"
"            <child>"
"              <object class=\"GtkButton\" id=\"okButton\">"
"                <property name=\"label\" translatable=\"yes\">_Ok</property>"
"                <property name=\"visible\">True</property>"
"                <property name=\"can_focus\">True</property>"
"                <property name=\"receives_default\">True</property>"
"                <property name=\"use_underline\">True</property>"
"              </object>"
"              <packing>"
"                <property name=\"expand\">False</property>"
"                <property name=\"fill\">True</property>"
"                <property name=\"position\">1</property>"
"              </packing>"
"            </child>"
"          </object>"
"          <packing>"
"            <property name=\"expand\">False</property>"
"            <property name=\"fill\">True</property>"
"            <property name=\"pack_type\">end</property>"
"            <property name=\"position\">0</property>"
"          </packing>"
"        </child>"
"        <child>"
"          <placeholder/>"
"        </child>"
"      </object>"
"    </child>"
"    <action-widgets>"
"      <action-widget response=\"0\">closeButton</action-widget>"
"      <action-widget response=\"0\">okButton</action-widget>"
"    </action-widgets>"
"  </object>"
"</interface>"
;
protected:
	Glib::RefPtr<Gtk::Builder> _builder;
	Gtk::Dialog* dialog1;
	Gtk::Box* vbox;
	Gtk::ButtonBox* dialog_action_area1;
	Gtk::Button* closeButton;
	Gtk::Button* okButton;

public:
	inline vimdialog() {
		_builder = Gtk::Builder::create_from_string(glade_file);
		_builder->get_widget("dialog1", dialog1);
		_builder->get_widget("vbox", vbox);
		_builder->get_widget("dialog_action_area1", dialog_action_area1);
		_builder->get_widget("closeButton", closeButton);
		_builder->get_widget("okButton", okButton);
	}

	inline operator Dialog*() {
		return dialog1;
	}
};

#endif
