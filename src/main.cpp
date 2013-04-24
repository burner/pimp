#include <QApplication>
#include <QStyleFactory>
#include <iostream>

#include <mainwindow/mainwindow.hpp>

#include <logger.hpp>

int main(int argc, char** argv) {
	QApplication app(argc, argv);
	
	// The setting stuff
	QCoreApplication::setOrganizationName("PIMP_Foundation");
	QCoreApplication::setOrganizationDomain("github.com/burner/pimp");
	QCoreApplication::setApplicationName("PIMP");

	auto mainWindow = new MainWindow;
	mainWindow->show();

	return app.exec();
}
