#include <QApplication>
#include <QDebug>
#include <QSharedMemory>
#include <QMessageBox>
#include <iostream>
#include <vmime/vmime.hpp>
#include <vmime/platforms/posix/posixHandler.hpp>

#include <mainwindow.hpp>
#include <settings.hpp>

int main(int argc, char** argv) {
	QApplication app(argc, argv);

	// start pimp only once
	/*QSharedMemory shared("62d60669-bb94-4a94-88bb-b964890a7e04");
    if(!shared.create(512, QSharedMemory::ReadWrite) ) {
         QMessageBox msgBox;
         msgBox.setText(QObject::tr(
			"Can't start more than one instance of the application.") );
         msgBox.setIcon( QMessageBox::Critical );
         msgBox.exec();
         return 1;
    }*/

	vmime::platform::setHandler<vmime::platforms::posix::posixHandler>();
	Settings::instance();

	// The setting stuff
	QCoreApplication::setOrganizationName("PIMP_Foundation");
	QCoreApplication::setOrganizationDomain("github.com/burner/pimp");
	QCoreApplication::setApplicationName("PIMP");

	auto mainWindow = new MainWindow;
	mainWindow->show();

	int rslt = app.exec();
	//shared.detach();
	return rslt;
}
