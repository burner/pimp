#include <debug.hpp>
#include <exception.hpp>
#include <boost/regex.hpp>

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

std::string format(const std::string& form, const std::vector<ptype>& vec) {
	boost::format ret(form);
	for(auto it : vec) {
		ret%it;
	}
	return ret.str();
}

void check(const std::string& form, const std::vector<ptype>& vec, 
		const char* file = __FILE__, int line = __LINE__) {
	boost::regex re("%[0-9.#-+*]*[csdioxXufFeEaAgGp]");
	auto it = boost::sregex_iterator(form.begin(), form.end(), re);
	auto end = boost::sregex_iterator();
	size_t idx = 0;
	for(; it != end && idx < vec.size(); it++, idx++) {
		auto b = it->str().back();
		//std::cout<<idx<<" "<<b<<" "<<vec[idx].type().name()<<" "<<
		//	vec[idx].which()<<" "<<it->str()<<std::endl;
		if(b == 'd' || b == 'i' || b == 'x' || b == 'X') {
			boost::format msg = 
				boost::format("ERROR wrong type %s passed for %c");
			msg % vec[idx].type().name() %b;

			enforce(vec[idx].type() == typeid(char) || 
				vec[idx].type() == typeid(short) || 
				vec[idx].type() == typeid(int) || 
				vec[idx].type() == typeid(long) || 
				vec[idx].type() == typeid(long long),
				msg.str(), file, line);
		} else if(b == 'f' || b == 'F' || b == 'e' || b == 'E' || b == 'g'
				|| b == 'G' || b == 'a' || b == 'A') {
			boost::format msg = 
				boost::format("ERROR wrong type %s passed for %c");
			msg % vec[idx].type().name() %b;

			enforce(vec[idx].type() == typeid(float) || 
				vec[idx].type() == typeid(double) || 
				vec[idx].type() == typeid(long double),
				msg.str(), file, line);
		} else if(b == 's') {
			boost::format msg = 
				boost::format("ERROR wrong type %s passed for %c");
			msg % vec[idx].type().name() %b;

			enforce(vec[idx].type() == typeid(std::string) || 
				vec[idx].type() == typeid(const char*) ||
				vec[idx].type() == typeid(std::string&),
				msg.str(), file, line);
		} else if(b == 'c') {
			boost::format msg = 
				boost::format("ERROR wrong type %s passed for %c");
			msg % vec[idx].type().name() %b;

			enforce(vec[idx].type() == typeid(char),
				msg.str(), file, line);

		}
	}
}

std::string shortenString(const std::string& str) {
	size_t idx = str.rfind('/');
	if(idx != std::string::npos) {
		std::string ret(str);
		ret.erase(0, idx+1);	
		return ret;
	} else {
		return std::string(str);
	}
}

Log::Log(const char* f, int l) : file(f) , line(l) {}

void Log::operator()() {
	std::vector<ptype> arr = {shortenString(file),line};
	std::string form("%s:%d ");
	check(form,arr,file,line);
	auto tmp = format(form, arr);
	std::cout<<tmp<<std::endl;
	qDebug()<<tmp.c_str();
}
void Log::operator()(std::string form, ptype a) {
	std::vector<ptype> arr = {shortenString(file),line,a};
	form = std::string("%s:%d ") + form;
	check(form, arr,file,line);
	auto tmp = format(form, arr);
	std::cout<<tmp<<std::endl;
	qDebug()<<tmp.c_str();
}

void Log::operator()(std::string form, ptype a, ptype b) {
	std::vector<ptype> arr = {shortenString(file),line,a,b};
	form = std::string("%s:%d ") + form;
	check(form, arr,file,line);
	auto tmp = format(form, arr);
	std::cout<<tmp<<std::endl;
	qDebug()<<tmp.c_str();
}

void Log::operator()(std::string form, ptype a, ptype b, ptype c) {
	std::vector<ptype> arr = {shortenString(file),line,a,b,c};
	form = std::string("%s:%d ") + form;
	check(form, arr,file,line);
	auto tmp = format(form, arr);
	std::cout<<tmp<<std::endl;
	qDebug()<<tmp.c_str();
}

void Log::operator()(std::string form, ptype a, ptype b, ptype c, ptype d) {
	std::vector<ptype> arr = {shortenString(file),line,a,b,c,d};
	form = std::string("%s:%d ") + form;
	check(form, arr,file,line);
	auto tmp = format(form, arr);
	std::cout<<tmp<<std::endl;
	qDebug()<<tmp.c_str();
}

void Log::operator()(std::string form, ptype a, ptype b, ptype c, ptype d,
		ptype e) {
	std::vector<ptype> arr = {shortenString(file),line,a,b,c,d,e};
	form = std::string("%s:%d ") + form;
	check(form, arr,file,line);
	auto tmp = format(form, arr);
	std::cout<<tmp<<std::endl;
	qDebug()<<tmp.c_str();
}

void Log::operator()(std::string form, ptype a, ptype b, ptype c, ptype d,
		ptype e, ptype f) {
	std::vector<ptype> arr = {shortenString(file),line,a,b,c,d,e,f};
	form = std::string("%s:%d ") + form;
	check(form, arr,file,line);
	auto tmp = format(form, arr);
	std::cout<<tmp<<std::endl;
	qDebug()<<tmp.c_str();
}

void Log::operator()(std::string form, ptype a, ptype b, ptype c, ptype d,
		ptype e, ptype f, ptype g) {
	std::vector<ptype> arr = {shortenString(file),line,a,b,c,d,e,f,g};
	form = std::string("%s:%d ") + form;
	check(form, arr,file,line);
	auto tmp = format(form, arr);
	std::cout<<tmp<<std::endl;
	qDebug()<<tmp.c_str();
}

void Log::operator()(std::string form, ptype a, ptype b, ptype c, ptype d,
		ptype e, ptype f, ptype g, ptype h) {
	std::vector<ptype> arr = {shortenString(file),line,a,b,c,d,e,f,g,h};
	form = std::string("%s:%d ") + form;
	check(form, arr,file,line);
	auto tmp = format(form, arr);
	std::cout<<tmp<<std::endl;
	qDebug()<<tmp.c_str();
}

void Log::operator()(std::string form, ptype a, ptype b, ptype c, ptype d,
		ptype e, ptype f, ptype g, ptype h, ptype i) {
	std::vector<ptype> arr = {shortenString(file),line,a,b,c,d,e,f,g,h,i};
	form = std::string("%s:%d ") + form;
	check(form, arr,file,line);
	auto tmp = format(form, arr);
	std::cout<<tmp<<std::endl;
	qDebug()<<tmp.c_str();
}
