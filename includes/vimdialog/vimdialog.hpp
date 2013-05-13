#ifndef VIMDIALOG
#define VIMDIALOG

#include <string>
#include <QObject>
#include <QSemaphore>
#include <QProcess>
#include <QLineEdit>
#include <QTextEdit>

class VimDialog : public QObject {
Q_OBJECT
public:
	VimDialog(QTextEdit*);
	VimDialog(QLineEdit*);
	void process();

public slots:
	void readFileToWidget(int, QProcess::ExitStatus);

private:
	QProcess* vim;
	QTextEdit* textEdit;
	QLineEdit* lineEdit;
	std::string filename;
	QThread* threadToDel;
	QSemaphore wait;

	void writeOldToFile();
	//void readFileToWidget();
};
#endif
