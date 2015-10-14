#include "string.h"
#include <iostream>
#include <cstring>


// A few freebies to get past the first couple of tests.
// These may need to be modified!
sfw_string::string::string(void)
{
	m_data = new char[m_size = 1]{ '\0' }; //set to 1 by default
}

sfw_string::string::~string()
{
	// only delete if not null
	if (m_data != nullptr)
	{
		delete[] m_data;
	}
}

size_t sfw_string::string::length() const
{
	// return 0 if null
	if (m_data != nullptr) return strlen(m_data);
	else return 0;
}





sfw_string::string::string(size_t size)
{
	m_size = size;
	m_data = new char[size];
	m_data[0] = '\0';
}

sfw_string::string::string(const char * a, size_t size)
{
	if (a != nullptr)
	{
		m_size = size + 1;
		int n2 = (int)size + 10;
		char *newChar;
		newChar = new char[n2];
		strcpy_s(newChar, strlen(a) + 1, a);
		newChar[m_size - 1] = '\0';
		m_data = new char[m_size];
		strcpy_s(m_data, m_size, newChar);
		delete[] newChar;
	}
}

sfw_string::string::string(const char * a)
{
	m_size = strlen(a) + 1;
	m_data = new char[m_size];
	strcpy_s(m_data, m_size, a);
}

sfw_string::string::string(const string & a)
{
	if (a.m_data != nullptr)
	{
		m_size = a.size();
		m_data = new char[m_size];
		strcpy_s(m_data, m_size, a.m_data);
	}
	else
	{
		string();
	}
}

sfw_string::string::string(string && a)
{
	m_size = a.m_size;
	m_data = a.m_data;
	a.m_data = nullptr;
	a.m_size = 0;
}

sfw_string::string & sfw_string::string::operator=(const string & a)
{
	if (a.m_data != nullptr)
	{
		m_size = a.size();
		int n2 = (int)a.size() + 10;
		char *newChar;
		newChar = new char[n2];
		strcpy_s(newChar, strlen(a.cstring()) + 1, a.cstring());
		delete m_data;
		newChar[m_size - 1] = '\0';
		m_data = new char[m_size];
		strcpy_s(m_data, m_size, newChar);
		delete[] newChar;

		return *this;
	}
	else
	{
		return string();
	}
}

sfw_string::string & sfw_string::string::operator=(string && a)
{
	if (a.m_data != nullptr)
	{
		m_size = a.m_size;
		m_data = a.m_data;
	}
	else
	{
		string();
	}
	return *this;
}

sfw_string::string & sfw_string::string::operator=(const char * a)
{
	m_size = strlen(a) + 1;
	delete m_data;
	m_data = new char[m_size];
	strcpy_s(m_data, m_size, a);
	return *this;
}

sfw_string::string & sfw_string::string::operator+=(const string & a)
{
	char *newChar = new char[m_size];
	size_t Prev_m_size = m_size;

	strcpy_s(newChar, m_size, m_data);
	delete m_data;
	m_size = m_size + strlen(a.cstring());
	m_data = new char[m_size];
	strcpy_s(m_data, Prev_m_size, newChar);
	strcat_s(m_data, m_size, a.cstring());
	delete[] newChar;

	return *this;
}

sfw_string::string & sfw_string::string::operator+=(const char * a)
{
	m_size = m_size + strlen(a);

	char *newChar = new char[m_size]; //Copy the m_data
	strcpy_s(newChar, m_size, m_data); //Give m_data to newChar
	delete m_data;
	m_data = new char[m_size]; //Change Size
	strcpy_s(m_data, m_size, newChar); //copy over old m_data
	strcat_s(m_data, strlen(a) + 1, a); //Add the new string
	delete[] newChar;

	return *this;
}

sfw_string::string & sfw_string::string::operator+=(char a)
{
	char *newChar = new char[m_size];
	size_t Prev_m_size = m_size;

	strcpy_s(newChar, m_size, m_data);
	delete m_data;
	m_size = m_size + 2;
	m_data = new char[m_size];
	strcpy_s(m_data, Prev_m_size, newChar);
	strcat_s(m_data, m_size, &a);
	delete[] newChar;
	return *this;
}

char & sfw_string::string::operator[](size_t index)
{
	return this->m_data[index];
}

const char & sfw_string::string::operator[](size_t index) const
{

	return this->m_data[index];
}




size_t sfw_string::string::size() const
{
	return m_size;
}

void sfw_string::string::resize(size_t size)
{
	// delete current memory if not null
	// allocate new memory to a temp
	// copy data tmp if not null
	// delete m_data if not null
	// set m_data to tmp

	//size_t newSize = size;
	//char* newArr = new char[newSize];

	//memcpy(newArr, m_data, size * sizeof(char));

	//m_size = newSize;
	//delete[] m_data;
	//m_data = newArr;

	m_size = size;
	delete m_data;
	m_data = new char[m_size];
	//m_data = "\0";
}

void sfw_string::string::clear()
{
	strcpy_s(m_data, 1, "\0");
}

bool sfw_string::string::empty() const
{
	if (strlen(m_data) == 0) return true;
	else return false;
}

const char * sfw_string::string::cstring() const
{
	return m_data;
}

bool sfw_string::operator<(const string & a, const string & b)
{
	if (strcmp(a.cstring(), b.cstring()) == -1) return true;
	else return false;
}

bool sfw_string::operator<(const string & a, const char * b)
{
	if (strcmp(a.cstring(), b) == -1) return true;
	else return false;
}

bool sfw_string::operator<(const char * a, const string & b)
{
	if (strcmp(a, b.cstring()) == -1) return true;
	else return false;
}

bool sfw_string::operator<=(const string & a, const string & b)
{
	if (strcmp(a.cstring(), b.cstring()) == 0 || strcmp(a.cstring(), b.cstring()) == -1) return true;
	else return false;
}

bool sfw_string::operator<=(const string & a, const char * b)
{
	if (strcmp(a.cstring(), b) == 0 || strcmp(a.cstring(), b) == -1) return true;
	else return false;
}

bool sfw_string::operator<=(const char * a, const string & b)
{
	if (strcmp(a, b.cstring()) == 0 || strcmp(a, b.cstring()) == -1) return true;
	else return false;
}

bool sfw_string::operator>(const string & a, const string & b)
{
	if (strcmp(a.cstring(), b.cstring()) == 1) return true;
	else return false;
}

bool sfw_string::operator>(const string & a, const char * b)
{
	if (strcmp(a.cstring(), b) == 1) return true;
	else return false;
}

bool sfw_string::operator>(const char * a, const string & b)
{
	if (strcmp(a, b.cstring()) == 1) return true;
	else return false;
}

bool sfw_string::operator>=(const string & a, const string & b)
{
	if (strcmp(a.cstring(), b.cstring()) == 0 || strcmp(a.cstring(), b.cstring()) == 1) return true;
	else return false;
}

bool sfw_string::operator>=(const string & a, const char * b)
{
	if (strcmp(a.cstring(), b) == 0 || strcmp(a.cstring(), b) == 1) return true;
	else return false;
}

bool sfw_string::operator>=(const char * a, const string & b)
{
	if (strcmp(a, b.cstring()) == 0 || strcmp(a, b.cstring()) == 1) return true;
	else return false;
}

bool sfw_string::operator!=(const string & a, const string & b)
{
	if (strcmp(a.cstring(), b.cstring()) != 0) return true;
	else return false;
}

bool sfw_string::operator!=(const string & a, const char * b)
{
	if (strcmp(a.cstring(), b) != 0) return true;
	else return false;
}

bool sfw_string::operator!=(const char * a, const string & b)
{
	if (strcmp(a, b.cstring()) != 0) return true;
	else return false;
}

bool sfw_string::operator==(const string & a, const string & b)
{
	if (strcmp(a.cstring(), b.cstring()) == 0) return true;
	else return false;
}

bool sfw_string::operator==(const string & a, const char * b)
{
	if (strcmp(a.cstring(), b) == 0) return true;
	else return false;
}

bool sfw_string::operator==(const char * a, const string & b)
{
	if (strcmp(a, b.cstring()) == 0) return true;
	else return false;
}

sfw_string::string sfw_string::operator+(const string & a, const string & b)
{
	size_t thePrev_m_size = a.size() + b.size();
	char *theChar = new char[thePrev_m_size];
	strcpy_s(theChar, a.size(), a.cstring());
	strcat_s(theChar, thePrev_m_size, b.cstring());
	string newString = string(theChar);
	delete[] theChar;

	return newString;
}

sfw_string::string sfw_string::operator+(const string & a, const char * b)
{
	size_t thePrev_m_size = a.size() + strlen(b);
	char *theChar = new char[thePrev_m_size];
	strcpy_s(theChar, a.size(), a.cstring());
	strcat_s(theChar, thePrev_m_size, b);
	string newString = string(theChar);
	delete[] theChar;

	return newString;
}

sfw_string::string sfw_string::operator+(const char * a, const string & b)
{
	size_t thePrev_m_size = strlen(a) + b.size();
	char *theChar = new char[thePrev_m_size];
	strcpy_s(theChar, strlen(a) + 1, a);
	strcat_s(theChar, thePrev_m_size, b.cstring());
	string newString = string(theChar);
	delete[] theChar;

	return newString;
}

sfw_string::string sfw_string::operator+(const string & a, char b)
{
	size_t thePrev_m_size = a.size() + 2;
	char *theChar = new char[thePrev_m_size];
	strcpy_s(theChar, a.size(), a.cstring());
	strcat_s(theChar, thePrev_m_size, &b);
	string newString = string(theChar);
	delete[] theChar;

	return newString;
}

sfw_string::string sfw_string::operator+(char a, const string & b)
{
	size_t thePrev_m_size = 2 + b.size();
	char *theChar = new char[thePrev_m_size];
	strcpy_s(theChar, 2, &a);
	strcat_s(theChar, thePrev_m_size, b.cstring());
	string newString = string(theChar);
	delete[] theChar;

	return newString;
}

std::ostream & sfw_string::operator<<(std::ostream & os, const string & p)
{

	return os << p.cstring();
}

std::istream & sfw_string::operator>>(std::istream & is, string & p)
{
	char tmp[256];
	is >> tmp;
	p = tmp;
	return is;
}

const sfw_string::string sfw_string::literals::operator""_sfw_string(const char * a, size_t len)
{
	return string(a, len);
}
