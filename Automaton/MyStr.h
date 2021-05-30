#ifndef MYSTR_H
#define MYSTR_H
#include <iostream>

class MyStr
{
public:
	MyStr();
	MyStr(const char*);
	MyStr(const MyStr&);
	~MyStr();

	MyStr& operator=(const MyStr&);
	MyStr operator+(const MyStr&) const;
	MyStr operator+(char) const;
	char operator[](unsigned) const;
	char& operator[](unsigned);
	std::ostream& ins(std::ostream&) const;
	std::istream& ext(std::istream&);
	unsigned len() const;

	bool operator==(const MyStr&) const;

private:
	char* buff;
};

std::ostream& operator<<(std::ostream&, const MyStr&);
std::istream& operator>>(std::istream&, MyStr&);
//istream& getline(istream&, MyStr&, const char = '\n');

#endif
