#include <QApplication>
#include <QStyleFactory>
#include <iostream>

#include <mainwindow/mainwindow.hpp>

#include <logger.hpp>
#include <unit.hpp>

int main(int argc, char** argv) {
	Unit::runTests();
	QApplication app(argc, argv);
	
	// The setting stuff
	QCoreApplication::setOrganizationName("PIMP_Foundation");
	QCoreApplication::setOrganizationDomain("github.com/burner/pimp");
	QCoreApplication::setApplicationName("PIMP");

	auto mainWindow = new MainWindow;
	mainWindow->show();

	return app.exec();
}
