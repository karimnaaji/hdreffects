#include "debug.h"

#if DEBUG
#include <iostream>
#endif

Debug* Debug::instance = NULL;

Debug& Debug::Instance () {
	if (instance == NULL)
		instance = new Debug();
	return *instance;
}

void Debug::Release() {
	if(instance != NULL) {
		delete instance;
	}
}

Debug::Debug ()
#if DEBUG
: out (std::cout)
#endif
{}

Debug& Debug::operator<< (const bool& val) {
#if DEBUG
	out << val;
#endif
	return *this;
}

Debug& Debug::operator<< (const short& val) {
#if DEBUG
	out << val;
#endif
	return *this;
}

Debug& Debug::operator<< (const unsigned short& val) {
#if DEBUG
	out << val;
#endif
	return *this;
}

Debug& Debug::operator<< (const int& val) {
#if DEBUG
	out << val;
#endif
	return *this;
}

Debug& Debug::operator<< (const unsigned int& val) {
#if DEBUG
	out << val;
#endif
	return *this;
}

Debug& Debug::operator<< (const long& val) {
#if DEBUG
	out << val;
#endif
	return *this;
}

Debug& Debug::operator<< (const unsigned long& val) {
#if DEBUG
	out << val;
#endif
	return *this;
}

Debug& Debug::operator<< (const float& val) {
#if DEBUG
	out << val;
#endif
	return *this;
}

Debug& Debug::operator<< (const double& val) {
#if DEBUG
	out << val;
#endif
	return *this;
}

Debug& Debug::operator<< (const long double& val) {
#if DEBUG
	out << val;
#endif
	return *this;
}

Debug& Debug::operator<< (const void* val) {
#if DEBUG
	out << val;
#endif
	return *this;
}

Debug& Debug::operator<< (const std::streambuf* sb) {
#if DEBUG
	out << sb;
#endif
	return *this;
}

Debug& Debug::operator<< (const unsigned char* s) {
#if DEBUG
	out << s;
#endif
	return *this;	
}

Debug& Debug::operator<< (const char* s) {
#if DEBUG
	out << s;
#endif
	return *this;
}

Debug& Debug::operator<< (const wchar_t* s) {
#if DEBUG
	out << s;
#endif
	return *this;
}

Debug& Debug::operator<< (const std::string& s) {
#if DEBUG
	out << s;
#endif
	return *this;
}

Debug& Debug::operator<< (const std::wstring& s) {
#if DEBUG
	out << s.c_str();
#endif
	return *this;
}

Debug& Debug::operator<< (const std::string* s) {
#if DEBUG
	out << *s;
#endif
	return *this;
}

Debug& Debug::operator<< (const std::wstring* s) {
#if DEBUG
	out << s->c_str();
#endif
	return *this;
}

Debug& Debug::operator<< (std::ostream& (*pf)(std::ostream&)) {
#if DEBUG
	out << pf;
#endif
	return *this;
}