#include <exception.hpp>

EnforceException::EnforceException(std::string ss) : s(ss) {}
const char* EnforceException::what() const throw() { return s.c_str(); }

UnknownMediaTypeException::UnknownMediaTypeException(std::string ss) : s(ss) {}
const char* UnknownMediaTypeException::what() const throw() { 
	return s.c_str(); 
}

OutOfBoundException::OutOfBoundException(std::string ss) : s(ss) {}
const char* OutOfBoundException::what() const throw() { 
	return s.c_str(); 
}
