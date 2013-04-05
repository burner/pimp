#include <QApplication>
#include <QDebug>
#include <QSharedMemory>
#include <QMessageBox>
#include <QPlastiqueStyle>
#include <QStyleFactory>
#include <iostream>
#include <stdlib.h>
#include <vmime/vmime.hpp>
#include <vmime/platforms/posix/posixHandler.hpp>

#include <mainwindow.hpp>
#include <settings.hpp>
#include <debug.hpp>

int main(int argc, char** argv) {
	putenv(const_cast<char*>("QT_PLUGIN_PATH=/usr/lib/kde4/plugins:$QT_PLUGIN_PATH"));
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

	QStyle *style = QStyleFactory::create("oxygen");
	if(style) {
		LOG("Oxygen loaded!");        /// @note You can leave this out if you want!
		QApplication::setStyle(style);
	}

	// The setting stuff
	QCoreApplication::setOrganizationName("PIMP_Foundation");
	QCoreApplication::setOrganizationDomain("github.com/burner/pimp");
	QCoreApplication::setApplicationName("PIMP");

	auto mainWindow = new MainWindow;
	Settings::instance();
	mainWindow->show();

	int rslt = app.exec();
	//shared.detach();
	return rslt;
}
