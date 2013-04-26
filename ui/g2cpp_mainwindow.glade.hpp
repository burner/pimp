#ifndef G2CPP_MAINWINDOW_HPP
#define G2CPP_MAINWINDOW_HPP

#include <gtkmm.h>

using namespace Gtk;

class mainwindow {
	const char* glade_file = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
"<interface>"
"  <!-- interface-requires gtk+ 3.0 -->"
"  <object class=\"GtkImage\" id=\"image1\">"
"    <property name=\"visible\">True</property>"
"    <property name=\"can_focus\">False</property>"
"    <property name=\"stock\">gtk-close</property>"
"  </object>"
"  <object class=\"GtkImage\" id=\"image2\">"
"    <property name=\"visible\">True</property>"
"    <property name=\"can_focus\">False</property>"
"    <property name=\"stock\">gtk-about</property>"
"  </object>"
"  <object class=\"GtkWindow\" id=\"window1\">"
"    <property name=\"can_focus\">False</property>"
"    <child>"
"      <object class=\"GtkBox\" id=\"box1\">"
"        <property name=\"visible\">True</property>"
"        <property name=\"can_focus\">False</property>"
"        <property name=\"orientation\">vertical</property>"
"        <child>"
"          <object class=\"GtkMenuBar\" id=\"mainMenu\">"
"            <property name=\"visible\">True</property>"
"            <property name=\"can_focus\">False</property>"
"            <child>"
"              <object class=\"GtkMenuItem\" id=\"pimpMenuButton\">"
"                <property name=\"visible\">True</property>"
"                <property name=\"can_focus\">False</property>"
"                <property name=\"label\" translatable=\"yes\">_Pimp</property>"
"                <property name=\"use_underline\">True</property>"
"                <child type=\"submenu\">"
"                  <object class=\"GtkMenu\" id=\"menu1\">"
"                    <property name=\"visible\">True</property>"
"                    <property name=\"can_focus\">False</property>"
"                    <child>"
"                      <object class=\"GtkImageMenuItem\" id=\"pimpCloseMenuItem\">"
"                        <property name=\"label\" translatable=\"yes\">_Quit</property>"
"                        <property name=\"visible\">True</property>"
"                        <property name=\"can_focus\">False</property>"
"                        <property name=\"use_underline\">True</property>"
"                        <property name=\"image\">image1</property>"
"                        <property name=\"use_stock\">False</property>"
"                      </object>"
"                    </child>"
"                  </object>"
"                </child>"
"              </object>"
"            </child>"
"            <child>"
"              <object class=\"GtkMenuItem\" id=\"helpMenuButtom\">"
"                <property name=\"visible\">True</property>"
"                <property name=\"can_focus\">False</property>"
"                <property name=\"label\" translatable=\"yes\">_Help</property>"
"                <property name=\"use_underline\">True</property>"
"                <child type=\"submenu\">"
"                  <object class=\"GtkMenu\" id=\"helpMenu\">"
"                    <property name=\"visible\">True</property>"
"                    <property name=\"can_focus\">False</property>"
"                    <child>"
"                      <object class=\"GtkImageMenuItem\" id=\"helpAboutMenuItem\">"
"                        <property name=\"label\" translatable=\"yes\">_About</property>"
"                        <property name=\"visible\">True</property>"
"                        <property name=\"can_focus\">False</property>"
"                        <property name=\"use_underline\">True</property>"
"                        <property name=\"image\">image2</property>"
"                        <property name=\"use_stock\">False</property>"
"                      </object>"
"                    </child>"
"                  </object>"
"                </child>"
"              </object>"
"            </child>"
"          </object>"
"          <packing>"
"            <property name=\"expand\">False</property>"
"            <property name=\"fill\">True</property>"
"            <property name=\"position\">0</property>"
"          </packing>"
"        </child>"
"        <child>"
"          <object class=\"GtkNotebook\" id=\"mainTagWidget\">"
"            <property name=\"visible\">True</property>"
"            <property name=\"can_focus\">True</property>"
"            <property name=\"tab_pos\">left</property>"
"            <property name=\"scrollable\">True</property>"
"            <child>"
"              <object class=\"GtkBox\" id=\"mailMainBox\">"
"                <property name=\"visible\">True</property>"
"                <property name=\"can_focus\">False</property>"
"                <property name=\"orientation\">vertical</property>"
"                <child>"
"                  <placeholder/>"
"                </child>"
"              </object>"
"            </child>"
"            <child type=\"tab\">"
"              <object class=\"GtkLabel\" id=\"mainWidgetEmailLabel\">"
"                <property name=\"visible\">True</property>"
"                <property name=\"can_focus\">False</property>"
"                <property name=\"ypad\">3</property>"
"                <property name=\"label\" translatable=\"yes\">_Mail</property>"
"                <property name=\"use_underline\">True</property>"
"                <property name=\"angle\">90</property>"
"              </object>"
"              <packing>"
"                <property name=\"tab_fill\">False</property>"
"              </packing>"
"            </child>"
"            <child>"
"              <object class=\"GtkBox\" id=\"calendarMainBox\">"
"                <property name=\"visible\">True</property>"
"                <property name=\"can_focus\">False</property>"
"                <property name=\"orientation\">vertical</property>"
"                <child>"
"                  <placeholder/>"
"                </child>"
"              </object>"
"              <packing>"
"                <property name=\"position\">1</property>"
"              </packing>"
"            </child>"
"            <child type=\"tab\">"
"              <object class=\"GtkLabel\" id=\"mainWidgetCalendarLabel\">"
"                <property name=\"visible\">True</property>"
"                <property name=\"can_focus\">False</property>"
"                <property name=\"xpad\">7</property>"
"                <property name=\"label\" translatable=\"yes\">_Calendar</property>"
"                <property name=\"use_underline\">True</property>"
"                <property name=\"angle\">90</property>"
"              </object>"
"              <packing>"
"                <property name=\"position\">1</property>"
"                <property name=\"tab_fill\">False</property>"
"              </packing>"
"            </child>"
"            <child>"
"              <object class=\"GtkBox\" id=\"imMainBox\">"
"                <property name=\"visible\">True</property>"
"                <property name=\"can_focus\">False</property>"
"                <property name=\"orientation\">vertical</property>"
"                <child>"
"                  <placeholder/>"
"                </child>"
"              </object>"
"              <packing>"
"                <property name=\"position\">2</property>"
"              </packing>"
"            </child>"
"            <child type=\"tab\">"
"              <object class=\"GtkLabel\" id=\"mainWidgetIMLabel\">"
"                <property name=\"visible\">True</property>"
"                <property name=\"can_focus\">False</property>"
"                <property name=\"label\" translatable=\"yes\">_Instant</property>"
"                <property name=\"use_underline\">True</property>"
"                <property name=\"angle\">90</property>"
"              </object>"
"              <packing>"
"                <property name=\"position\">2</property>"
"                <property name=\"tab_fill\">False</property>"
"              </packing>"
"            </child>"
"          </object>"
"          <packing>"
"            <property name=\"expand\">True</property>"
"            <property name=\"fill\">True</property>"
"            <property name=\"position\">1</property>"
"          </packing>"
"        </child>"
"        <child>"
"          <object class=\"GtkStatusbar\" id=\"statusbar\">"
"            <property name=\"visible\">True</property>"
"            <property name=\"can_focus\">False</property>"
"            <property name=\"orientation\">vertical</property>"
"            <property name=\"spacing\">2</property>"
"          </object>"
"          <packing>"
"            <property name=\"expand\">False</property>"
"            <property name=\"fill\">True</property>"
"            <property name=\"position\">2</property>"
"          </packing>"
"        </child>"
"      </object>"
"    </child>"
"  </object>"
"</interface>"
;
protected:
	Glib::RefPtr<Gtk::Builder> _builder;
	Gtk::Image* image1;
	Gtk::Image* image2;
	Gtk::Window* window1;
	Gtk::Box* box1;
	Gtk::MenuBar* mainMenu;
	Gtk::MenuItem* pimpMenuButton;
	Gtk::Menu* menu1;
	Gtk::ImageMenuItem* pimpCloseMenuItem;
	Gtk::MenuItem* helpMenuButtom;
	Gtk::Menu* helpMenu;
	Gtk::ImageMenuItem* helpAboutMenuItem;
	Gtk::Notebook* mainTagWidget;
	Gtk::Box* mailMainBox;
	Gtk::Label* mainWidgetEmailLabel;
	Gtk::Box* calendarMainBox;
	Gtk::Label* mainWidgetCalendarLabel;
	Gtk::Box* imMainBox;
	Gtk::Label* mainWidgetIMLabel;
	Gtk::Statusbar* statusbar;

public:
	inline mainwindow() {
		_builder = Gtk::Builder::create_from_string(glade_file);
		_builder->get_widget("image1", image1);
		_builder->get_widget("image2", image2);
		_builder->get_widget("window1", window1);
		_builder->get_widget("box1", box1);
		_builder->get_widget("mainMenu", mainMenu);
		_builder->get_widget("pimpMenuButton", pimpMenuButton);
		_builder->get_widget("menu1", menu1);
		_builder->get_widget("pimpCloseMenuItem", pimpCloseMenuItem);
		_builder->get_widget("helpMenuButtom", helpMenuButtom);
		_builder->get_widget("helpMenu", helpMenu);
		_builder->get_widget("helpAboutMenuItem", helpAboutMenuItem);
		_builder->get_widget("mainTagWidget", mainTagWidget);
		_builder->get_widget("mailMainBox", mailMainBox);
		_builder->get_widget("mainWidgetEmailLabel", mainWidgetEmailLabel);
		_builder->get_widget("calendarMainBox", calendarMainBox);
		_builder->get_widget("mainWidgetCalendarLabel", mainWidgetCalendarLabel);
		_builder->get_widget("imMainBox", imMainBox);
		_builder->get_widget("mainWidgetIMLabel", mainWidgetIMLabel);
		_builder->get_widget("statusbar", statusbar);
	}

	inline operator Window*() {
		return window1;
	}
};

#endif
