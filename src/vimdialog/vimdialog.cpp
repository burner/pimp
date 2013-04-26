#include <QProcess>
#include <vimdialog/vimdialog.hpp>

VimDialog::VimDialog(QTextEdit* te) : textEdit(te), lineEdit(nullptr) {}
VimDialog::VimDialog(QLineEdit* le) : textEdit(nullptr), lineEdit(le) {}

void VimDialog::run() {
	QProcess vim;

}
