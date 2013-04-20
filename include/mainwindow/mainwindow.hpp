#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <g2cpp_mainwindow.glade.hpp>

class MainWindow : public mainwindow {
public:
	MainWindow();

private:
	static void quitPimp();
	bool spawnVimOnCurrent(GdkEventKey* const&);
};
#endif
