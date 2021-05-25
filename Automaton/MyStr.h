#ifndef MYSTR_H
#define MYSTR_H
#include <iostream>
using namespace std;

class MyStr {
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
	ostream& ins(ostream&) const;
	istream& ext(istream&);
	unsigned len() const;

	bool operator==(const MyStr&) const;

private:
	char* buff;
};

ostream& operator<<(ostream&, const MyStr&);
istream& operator>>(istream&, MyStr&);
//istream& getline(istream&, MyStr&, const char = '\n');


#endif
