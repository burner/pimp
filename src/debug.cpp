#include <debug.hpp>

const QString stripFileName(const char* file) {
	QString str(file);
	int pos = str.lastIndexOf('/');
	str.remove(0,pos+1);
	return str;
}

const QString prettyPrintFileLineInfo(const QString& file, int line) {
	auto tmp = QString("%1:%2").arg(file, QString::number(line));
	return tmp;
}
