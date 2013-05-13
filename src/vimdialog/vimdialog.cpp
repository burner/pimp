#include <sstream>
#include <fstream>
#include <QProcess>
#include <vimdialog/vimdialog.hpp>
#include <vimdialog/uniquename.hpp>
#include <logger.hpp>
#include <dbc.hpp>

VimDialog::VimDialog(QTextEdit* te) : textEdit(te), 
		lineEdit(nullptr), 
		filename(UniqueName::getName()) {}

VimDialog::VimDialog(QLineEdit* le) : textEdit(nullptr), 
		lineEdit(le), filename(UniqueName::getName()) {}

void VimDialog::readFileToWidget(int exitCode, QProcess::ExitStatus es) {
	LOG("exit status %d", es);
	LOG("fname %s", filename.c_str());
	std::ifstream f;
	f.open(filename.c_str(), std::ios::in);
	Esr(TE(f.is_open()));
	std::stringstream ss;

	std::string line;
	char endchar = lineEdit ? ' ' : '\n';
	while(getline(f, line)) {
		LOG("%s", line);
		ss<<line<<endchar;
	}

	QString newText = QString::fromStdString(ss.str());
	if(newText.size() != 0) {
		newText.resize(newText.size()-1);
	}

	LOG("\"%s\"", ss.str());
	if(lineEdit) {
		lineEdit->setText(newText);
	} else if(textEdit) {
		textEdit->setText(newText);
	} else {
		WARN("entry and textview null");
	}
	remove(filename.c_str());
	delete this;
}

void VimDialog::process() {
	this->writeOldToFile();
	vim = new QProcess;
	QStringList args;
	args.push_back("-e");
	args.push_back("vim");
	args.push_back(QString::fromStdString(filename));

	QString termStr = "xterm";
	vim->start(termStr, args);
	LOG();
	QObject::connect(
		vim, SIGNAL(finished(int,QProcess::ExitStatus)), 
		this, SLOT(readFileToWidget(int,QProcess::ExitStatus))
	);
}

void VimDialog::writeOldToFile() {
	if(lineEdit) {
		std::ofstream file(filename.c_str(), std::ios::trunc);
		file<<lineEdit->text().toStdString();
	} else if(textEdit) {
		std::ofstream file(filename.c_str(), std::ios::trunc);
		file<<textEdit->toPlainText().toStdString();
	} else {
		WARN("entry and textview are null");
	}
}
