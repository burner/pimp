#ifndef DEBUG
#define DEBUG

#include <QDebug>
#include <boost/format.hpp>
#include <boost/variant.hpp>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

typedef boost::variant<
bool, char,short,int,long,long long,
unsigned char, unsigned short, unsigned int, unsigned long, 
unsigned long long, float,double,long double,
std::string&, char*, std::string, const char*> ptype; 

struct Log {
	const char* file;
	int line;
	bool warn;
	public:
	Log(const char* f, int l);
	Log(const char* f, int l, bool w);

	void operator()();
	void operator()(std::string form);
	void operator()(std::string form, ptype a);
	void operator()(std::string form, ptype a, ptype b);
	void operator()(std::string form, ptype a, ptype b, ptype c);
	void operator()(std::string form, ptype a, ptype b, ptype c, ptype d);
	void operator()(std::string form, ptype a, ptype b, ptype c, ptype d,
			ptype e);
	void operator()(std::string form, ptype a, ptype b, ptype c, ptype d,
			ptype e, ptype f);
	void operator()(std::string form, ptype a, ptype b, ptype c, ptype d,
			ptype e, ptype f, ptype g);
	void operator()(std::string form, ptype a, ptype b, ptype c, ptype d,
			ptype e, ptype f, ptype g, ptype h);
	void operator()(std::string form, ptype a, ptype b, ptype c, ptype d,
			ptype e, ptype f, ptype g, ptype h, ptype i);
};

const QString stripFileName(const char*);
const QString prettyPrintFileLineInfo(const QString&, int line);

void doLogging(std::string&);

#ifndef RELEASE
//#define LOG (__FILE__,__LINE__); std::cout<<LOGTMPSTRING<<std::endl; qDebug()<<QString(LOGTMPSTRING.c_str());
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

#endif
