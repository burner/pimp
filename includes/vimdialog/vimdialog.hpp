#ifndef VIMDIALOG
#define VIMDIALOG

#include <QThread>
#include <QLineEdit>
#include <QTextEdit>

class VimDialog : public QThread {
Q_OBJECT
public:
	VimDialog(QTextEdit*);
	VimDialog(QLineEdit*);
	void run();

private:
	QTextEdit* textEdit;
	QLineEdit* lineEdit;
	QString filename;

	void writeOldToFile();
	void readFileToWidget();
};
#endif
