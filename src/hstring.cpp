/************************************************************************************\
* This source file is part of the High Level C++ types library                       *
* For latest info, see http://libhltypes.sourceforge.net/                            *
**************************************************************************************
* Copyright (c) 2010 Kresimir Spes, Boris Mikic, Domagoj Cerjan                      *
*                                                                                    *
* This program is free software; you can redistribute it and/or modify it under      *
* the terms of the BSD license: http://www.opensource.org/licenses/bsd-license.php   *
\************************************************************************************/
#define _CRT_SECURE_NO_WARNINGS // damn visual studio warnings
#include "Array.h"
#include "hstring.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <algorithm>

#define HL_E_TOLERANCE (0.01f)

typedef std::basic_string<char> stdstr;

namespace hltypes
{
	string::string() : stdstr() {}
	string::string(const char* s) : stdstr(s) {}
	string::string(const string& s) : stdstr(s) {}
	string::string(const std::string& s) : stdstr(s) {}
	string::string(const char* s, const int len) : stdstr(s, len) {}
	string::string(const string& s, const int len) : stdstr(s, len) {}
	string::string(const int i) { this->operator=(i); }
	string::string(const float f) { this->operator=(f); }

	harray_hstr string::split(const char* splitter, unsigned int n) const
	{
		harray_hstr out;
		const char *s = this->c_str(), *p;
		int splitter_len = strlen(splitter);
		while ((p = strstr(s, splitter)) != 0 && n > 0)
		{
			out.push_back(string(s, p - s));
			s = p + splitter_len;
			n--;
		}
		if (s[0] != 0)
		{
			out.push_back(string(s));
		}
		return out;
	}
	
	harray_hstr string::rsplit(const char* splitter, unsigned int n) const
	{
		harray_hstr out;
		const char *s = this->c_str(), *p;
		int splitter_len = strlen(splitter);
		for (p = s + strlen(s) - 1; p != s && n > 0; p--)
		{
			if (strncmp(p, splitter, splitter_len) == 0)
			{
				n--;
			}
		}
		if (s != p)
		{
			out.push_back(string(s, p - s + 1));
			s = p + 1 + splitter_len;
		}
		while ((p = strstr(s, splitter)) != 0)
		{
			out.push_back(string(s, p - s));
			s = p + splitter_len;
		}
		if (s[0] != 0)
		{
			out.push_back(string(s));
		}
		return out;
	}

	bool string::split(const char* splitter, string& out_left, string& out_right) const
	{
		int index = this->find(splitter);
		if (index < 0)
		{
			return false;
		}
		out_left = this->substr(0, index);
		out_right = this->substr(index + strlen(splitter), 1000);
		return true;
	}
	
	bool string::rsplit(const char* splitter, string& out_left, string& out_right) const
	{
		int index = this->rfind(splitter);
		if (index < 0)
		{
			return false;
		}
		out_left = this->substr(0, index);
		out_right = this->substr(index + strlen(splitter), 1000);
		return true;
	}

	bool string::starts_with(const char* s) const
	{
		return (strncmp(this->c_str(), s, strlen(s)) == 0);
	}

	bool string::ends_with(const char* s) const
	{
		const char* thiss = this->c_str();
		int thislen = this->size(), slen = strlen(s);
		if (slen > thislen)
		{
			return false;
		}
		return (strcmp(thiss + thislen - slen, s) == 0);
	}
	
	string string::lower() const
	{
		hstr s(*this);
		std::transform(s.begin(), s.end(), s.begin(), tolower);
		return s;
	}
	
	string string::upper() const
	{
		hstr s(*this);
		std::transform(s.begin(), s.end(), s.begin(), toupper);
		return s;
	}

	string string::replace(const char* what, const char* with_what) const
	{
		const char *s = this->c_str(), *p;
		string out;
		int what_len = strlen(what);
		if (what_len == 0)
		{
			return *this;	
		}
		while ((p = strstr(s, what)) != 0)
		{
			out.append(s, p - s);
			out.append(with_what);
			s = p + what_len;
		}
		out.append(s);
		return out;
	}
/******* TYPE EXTENSION FUNCTIONS **************************************/
	harray_hstr string::split(const char splitter, unsigned int n) const
	{
		const char sp[2] = {splitter, 0};
		return this->split(sp, n);
	}

	harray_hstr string::split(const string& splitter, unsigned int n) const
	{
		return this->split(splitter.c_str(), n);
	}
	
	harray_hstr string::rsplit(const char splitter, unsigned int n) const
	{
		const char sp[2] = {splitter, 0};
		return this->rsplit(sp, n);
	}

	harray_hstr string::rsplit(const string& splitter,unsigned int n) const
	{
		return this->rsplit(splitter.c_str(), n);
	}
	
	bool string::split(const char splitter,string& out_left,string& out_right) const
	{
		const char sp[2] = {splitter, 0};
		return this->split(sp, out_left, out_right);
	}
		
	bool string::split(const string& splitter,string& out_left, string& out_right) const
	{
		return this->split(splitter.c_str(), out_left, out_right);
	}
	
	bool string::rsplit(const char splitter, string& out_left, string& out_right) const
	{
		const char sp[2] = {splitter, 0};
		return this->rsplit(sp, out_left, out_right);
	}
	
	bool string::rsplit(const string& splitter, string& out_left, string& out_right) const
	{
		return this->rsplit(splitter.c_str(), out_left, out_right);
	}

	bool string::starts_with(const string& s) const
	{
		return this->starts_with(s.c_str());
	}

	bool string::ends_with(const string& s) const
	{
		return this->ends_with(s.c_str());
	}

	string string::replace(const string& what, const char* with_what) const
	{
		return this->replace(what.c_str(), with_what);
	}
	
	string string::replace(const char* what, const string& with_what) const
	{
		return this->replace(what, with_what.c_str());
	}
	
	string string::replace(const string& what, const string& with_what) const
	{
		return this->replace(what.c_str(), with_what.c_str());
	}
	
	string string::replace(size_t pos1, size_t n1, const string& str)
	{
		return stdstr::replace(pos1, n1, str);
	}
	
	string string::replace(size_t pos1, size_t n1, const string& str, size_t pos2, size_t n2)
	{
		return stdstr::replace(pos1, n1, str, pos2, n2);
	}
	
	string string::replace(size_t pos1, size_t n1, const char* s, size_t n2)
	{
		return stdstr::replace(pos1, n1, s, n2);
	}
	
	string string::replace(size_t pos1, size_t n1, const char* s)
	{
		return stdstr::replace(pos1, n1, s);
	}
	
	string string::replace(size_t pos1, size_t n1, size_t n2, char c)
	{
		return stdstr::replace(pos1, n1, n2, c);
	}
/******* CAST OPERATORS ************************************************/
	string::operator float() const
	{
		float f;
		sscanf(this->c_str(), "%f", &f);
		return f;
	}
	
	string::operator int() const
	{
		int i;
		sscanf(this->c_str(), "%d", &i);
		return i;
	}
/******* ASSIGNMENT OPERATORS ******************************************/
	void string::operator=(const float f)
	{
		char s[64];
		sprintf(s, "%f", f);
		stdstr::operator=(s);
	}
	
	void string::operator=(const std::string& s)
	{
		stdstr::operator=(s);
	}
	
	void string::operator=(const char* s)
	{
		stdstr::operator=(s);
	}
	
	void string::operator=(const int i)
	{
		char s[64];
		sprintf(s, "%d", i);
		stdstr::operator=(s);
	}
	
	void string::operator=(const bool b)
	{
		stdstr::operator=(b ? "true" : "false");
	}
/******* COMPARISON OPERATORS ******************************************/
	bool string::operator==(const float f) const
	{
		return (fabs(((float)*this) - f) < HL_E_TOLERANCE);
	}
	
	bool string::operator==(const int i) const
	{
		return (((int)*this) == i);
	}
	
	bool string::operator==(const bool b) const
	{
		const char* cstr = this->c_str();
		return (strcmp(cstr, "1") == 0 && b ||
				strcmp(cstr, "0") == 0 && !b ||
				strcmp(cstr, "true") == 0 && b ||
				strcmp(cstr, "false") == 0 && !b);
	}

	bool string::operator==(const char* s) const
	{
		return (strcmp(this->c_str(), s) == 0);
	}
	
	bool string::operator==(const std::string& s) const
	{
		return (strcmp(this->c_str(), s.c_str()) == 0);
	}
/******* ADDITION OPERATORS *********************************************/
	string string::operator+(const char* s1) const
	{
		string s(*this);
		s.append(s1);
		return s;
	}
	
	string string::operator+(char* s1) const
	{ 
		return this->operator+((const char*) s1);
	}
	
	string string::operator+(const string& s1) const
	{
		string s(*this);
		s.append(s1);
		return s;
	}
	
	string string::operator+(const std::string& s1) const
	{
		string s(*this);
		s.append(s1);
		return s;
	}
	
}
/******* GLOBAL ADDITION OPERATORS *******************************************/
hstr operator+(const char* s1, chstr s2)
{
	hstr s(s1);
	return (s + s2);
}

hstr operator+(char* s1, chstr s2)
{
	hstr s(s1);
	return (s + s2);
}