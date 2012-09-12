#ifndef EXCEPTION
#define EXCEPTION

#include <QtCore>
#include <boost/format.hpp>
#include <string>
#include <exception>

class EnforceException : public std::exception {
	std::string s;
	public:
	EnforceException(std::string ss);
	const char* what() const throw();
};

template<typename T> 
T enforce(T value, const std::string& msg, const char* file = __FILE__, int
		line = __LINE__) {
	if(!value) {
		throw EnforceException((boost::format("%s:%d %s")%file%line%msg).str());
	} else {
		return value;
	}
}
#endif
