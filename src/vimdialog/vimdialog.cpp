#include <sstream>
#include <fstream>
#include <QProcess>
#include <vimdialog/vimdialog.hpp>
#include <vimdialog/uniquename.hpp>
#include <logger.hpp>

VimDialog::VimDialog(QTextEdit* te) : textEdit(te), lineEdit(nullptr),
		filename(QString::fromStdString(UniqueName::getName())) {}

VimDialog::VimDialog(QLineEdit* le) : textEdit(nullptr), lineEdit(le),
		filename(QString::fromStdString(UniqueName::getName())) {}

void VimDialog::run() {
	QProcess vim;
	QStringList args;
	args.push_back("-e");
	args.push_back("vim");
	args.push_back(filename);

	QString termStr = "roxtern";
	vim.start(termStr, args);
	vim.waitForFinished(1000*60*60);
	vim.kill();

}

void VimDialog::writeOldToFile() {
	if(lineEdit) {
		std::ofstream file(filename.toStdString().c_str(), std::ios::trunc);
		file<<lineEdit->text().toStdString();
	} else if(textEdit) {
		std::ofstream file(filename.toStdString().c_str(), std::ios::trunc);
		file<<textEdit->toPlainText().toStdString();
	} else {
		WARN("entry and textview are null");
	}
}

void VimDialog::readFileToWidget() {
	std::ifstream f(filename.toStdString().c_str(), std::ios::in);
	std::stringstream ss;

	std::string line;
	char endchar = lineEdit ? ' ' : '\n';
	while(getline(f, line)) {
		ss<<line<<endchar;
	}

	QString newText = QString::fromStdString(ss.str());
	if(newText.size() != 0) {
		newText.resize(newText.size()-1);
	}
	if(lineEdit) {
		lineEdit->setText(newText);
	} else if(textEdit) {
		textEdit->setText(newText);
	} else {
		WARN("entry and textview null");
	}
	remove(filename.toStdString().c_str());
	
	delete this;
}
