#include <QProcess>
#include <vimdialog/vimdialog.hpp>
#include <vimdialog/uniquename.hpp>

VimDialog::VimDialog(QTextEdit* te) : textEdit(te), lineEdit(nullptr) {}
VimDialog::VimDialog(QLineEdit* le) : textEdit(nullptr), lineEdit(le) {}

void VimDialog::run() {
	QProcess vim;
	QStringList args;
	args.push_back("-e");
	args.push_back("vim");
	//QString fn = QString::fromStdString(UniqueName::getName());
	args.push_back(QString::fromStdString(UniqueName::getName()));
	QString termStr = "roxtern";
	vim.start(termStr, args);
	vim.waitForFinish(1000*60*60);
	vim.kill();

}
