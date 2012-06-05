#include <QApplication>
#include <QDebug>

#include <main.hpp>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
	ui.setupUi(this);
	QObject::connect(ui.actionGetAll, SIGNAL(triggered()),
		this, SLOT(getAll()));
}

void MainWindow::getAll() {
	return;
}

int main(int argc, char** argv) {
	QApplication app(argc, argv);
	auto mainWindow = new MainWindow;
	mainWindow->show();

	return app.exec();
}
