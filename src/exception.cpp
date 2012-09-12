#include <exception.hpp>

EnforceException::EnforceException(std::string ss) : s(ss) {}
const char* EnforceException::what() const throw() { return s.c_str(); }

