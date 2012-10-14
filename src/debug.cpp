#include <debug.hpp>
#include <exception.hpp>
#include <boost/regex.hpp>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

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

void Log::check(const std::string& form, const std::vector<ptype>& vec, 
		std::string file , int line) {
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

Log::Log(const char* f, int l) : file(f) , line(l), warn(false) {}
Log::Log(const char* f, int l, bool w) : file(f) , line(l), warn(w) {}

void Log::write(std::string form, const std::vector<ptype>& arr,
		std::string& file, int line) {
	if(warn) {
		form = std::string("WARN %s:%d ") + form;
	} else {
		form = std::string("%s:%d ") + form;
	}
	check(form,arr,file,line);
	auto tmp = format(form, arr);
	std::cout<<tmp<<std::endl;
	qDebug()<<tmp.c_str();
}

void Log::operator()() {
	std::string f = shortenString(file);
	std::vector<ptype> arr = {f,line};
	write("", arr, f, line);
}

void Log::operator()(std::string form) {
	std::string f = shortenString(file);
	std::vector<ptype> arr = {f,line};
	write(form, arr, f, line);
}

void Log::operator()(std::string form, ptype a) {
	std::string f = shortenString(file);
	std::vector<ptype> arr = {f,line,a};
	write(form, arr, f, line);
}

void Log::operator()(std::string form, ptype a, ptype b) {
	std::string f = shortenString(file);
	std::vector<ptype> arr = {f,line,a,b};
	write(form, arr, f, line);
}

void Log::operator()(std::string form, ptype a, ptype b, ptype c) {
	std::string f = shortenString(file);
	std::vector<ptype> arr = {f,line,a,b,c};
	write(form, arr, f, line);
}

void Log::operator()(std::string form, ptype a, ptype b, ptype c, ptype d) {
	std::string f = shortenString(file);
	std::vector<ptype> arr = {f,line,a,b,c,d};
	write(form, arr, f, line);
}

void Log::operator()(std::string form, ptype a, ptype b, ptype c, ptype d,
		ptype e) {
	std::string f = shortenString(file);
	std::vector<ptype> arr = {f,line,a,b,c,d,e};
	write(form, arr, f, line);
}

void Log::operator()(std::string form, ptype a, ptype b, ptype c, ptype d,
		ptype e, ptype f) {
	std::string fi = shortenString(file);
	std::vector<ptype> arr = {f,line,a,b,c,d,e,f};
	write(form, arr, fi, line);
}

void Log::operator()(std::string form, ptype a, ptype b, ptype c, ptype d,
		ptype e, ptype f, ptype g) {
	std::string fi = shortenString(file);
	std::vector<ptype> arr = {f,line,a,b,c,d,e,f,g};
	write(form, arr, fi, line);
}

void Log::operator()(std::string form, ptype a, ptype b, ptype c, ptype d,
		ptype e, ptype f, ptype g, ptype h) {
	std::string fi = shortenString(file);
	std::vector<ptype> arr = {f,line,a,b,c,d,e,f,g,h};
	write(form, arr, fi, line);
}

void Log::operator()(std::string form, ptype a, ptype b, ptype c, ptype d,
		ptype e, ptype f, ptype g, ptype h, ptype i) {
	std::string fi = shortenString(file);
	std::vector<ptype> arr = {f,line,a,b,c,d,e,f,g,h,i};
	write(form, arr, fi, line);
}

void print_trace(int) {
    char pid_buf[30];
    sprintf(pid_buf, "%d", getpid());
    char name_buf[512];
    name_buf[readlink("/proc/self/exe", name_buf, 511)]=0;
    int child_pid = fork();
    if (!child_pid) {           
        dup2(2,1); // redirect output to stderr
        fprintf(stdout,"stack trace for %s pid=%s\n",name_buf,pid_buf);
        execlp("gdb", "gdb", "--batch", "-n", "-ex", "thread", "-ex", "bt", 
			name_buf, pid_buf, NULL);
        abort(); /* If gdb failed to start */
		exit(1);
    } else {
        waitpid(child_pid,NULL,0);
		exit(1);
    }
}
