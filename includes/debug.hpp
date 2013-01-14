#ifndef DEBUG
#define DEBUG

#include <QDebug>
#include <iostream>
#include "format.hpp"

static const QString prettyPrintFileLineInfo(const QString& file, int line) {
	auto tmp = QString("%1:%2").arg(file, QString::number(line));
	return tmp;
}

static const QString stripFileName(const char* file) {
	QString str(file);
	int pos = str.lastIndexOf('/');
	str.remove(0,pos+1);
	return str;
}

#ifndef RELEASE
#define LOG Log(__FILE__,__LINE__)
#define WARN Log(__FILE__,__LINE__,true)
#else
#define LOG() ;
#define WARN() ;
#endif

#define debug() qDebug()<<prettyPrintFileLineInfo(stripFileName(__FILE__),__LINE__)<<"]"
#define warning() qWarning()<<prettyPrintFileLineInfo(stripFileName(__FILE__),__LINE__)<<"]"
#define critical() qCritical()<<prettyPrintFileLineInfo(stripFileName(__FILE__),__LINE__)<<"]"
#define fatal() qFatal()<<prettyPrintFileLineInfo(stripFileName(__FILE__),__LINE__)<<"]"

static std::string shortenString(const std::string& str) {
	size_t idx = str.rfind('/');
	if(idx == std::string::npos) {
		return str;
	} else {
		return str.substr(idx+1);
	}
}

struct Log {
	public:
	Log(const char* f, int l, bool w = false) {
		if(w) {
			std::cerr<<"WARN ";
		}
		std::cerr<<shortenString(f)<<':'<<l<<' ';
		debug()<<QString::fromStdString(shortenString(f))<<':'<<l<<' ';
	}

	void operator()() {
		std::cerr<<std::endl;
	}

	template<typename... Args>
	void operator()(std::string form, Args... args) {
		auto tmp = format(form, args...);
		std::cerr<<tmp<<std::endl;
		debug()<<QString::fromStdString(tmp);
	}
};
#endif
