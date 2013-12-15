#ifndef DEBUG_H
#define DEBUG_H

#include <iosfwd>
#include <sstream>
#include <string>

#define DEBUG 0

class Debug {
	public:
		static Debug& Instance ();
		
		Debug& operator<< (const bool& val);
		Debug& operator<< (const short& val);
		Debug& operator<< (const unsigned short& val);
		Debug& operator<< (const int& val);
		Debug& operator<< (const unsigned int& val);
		Debug& operator<< (const long& val);
		Debug& operator<< (const unsigned long& val);
		Debug& operator<< (const float& val);
		Debug& operator<< (const double& val);
		Debug& operator<< (const long double& val);
		Debug& operator<< (const void* val);
		Debug& operator<< (const std::streambuf* sb);
		Debug& operator<< (std::ostream& ( *pf )(std::ostream&));
		Debug& operator<< (const std::string& s);
		Debug& operator<< (const std::string* s);
		Debug& operator<< (const char* s);
		Debug& operator<< (const unsigned char* s);
	    Debug& operator<< (const std::wstring& s);
		Debug& operator<< (const std::wstring* s);
		Debug& operator<< (const wchar_t* s);

		static void Release();
private:
		static Debug* instance;
		Debug ();
#if DEBUG
		std::ostream& out;
#endif
};

#endif
