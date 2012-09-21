#include <QApplication>
#include <QDebug>
#include <iostream>
#include <vmime/vmime.hpp>
#include <vmime/platforms/posix/posixHandler.hpp>

#include <mainwindow.hpp>
#include <settings.hpp>

int main(int argc, char** argv) {
	vmime::platform::setHandler<vmime::platforms::posix::posixHandler>();
	Settings::instance();

	// The setting stuff
	QCoreApplication::setOrganizationName("PIMP_Foundation");
	QCoreApplication::setOrganizationDomain("github.com/burner/pimp");
	QCoreApplication::setApplicationName("PIMP");

	QApplication app(argc, argv);
	auto mainWindow = new MainWindow;
	mainWindow->show();

	return app.exec();
}
