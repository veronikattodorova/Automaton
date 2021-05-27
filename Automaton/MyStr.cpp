#include "MyStr.h"

MyStr::MyStr() :buff(new char[1]) {
	buff[0] = '\0';
}

MyStr::MyStr(const char* txt) : buff(new char[strlen(txt) + 1]) {
	for (int i = 0; i < strlen(txt); i++) {
		buff[i] = txt[i];
	}
	buff[strlen(txt)] = '\0';
}
MyStr::MyStr(const MyStr& txt) : buff(new char[txt.len() + 1]) {
	for (unsigned i = 0; i < txt.len(); i++) {
		buff[i] = txt[i];
	}
	buff[txt.len()] = '\0';
}

MyStr::~MyStr() {
	if (buff != nullptr) {
		delete[] buff;
	}
}

MyStr& MyStr::operator=(const MyStr& rhs) {
	if (this != &rhs) {
		if (buff != nullptr) {
			delete[] buff;
			buff = nullptr;
		}
		buff = new char[rhs.len() + 1];
		for (unsigned i = 0; i < rhs.len(); i++) {
			buff[i] = rhs[i];
		}
		buff[rhs.len()] = '\0';
	}
	return *this;
}

MyStr MyStr::operator+(const MyStr& rhs) const {
	unsigned len = (*this).len() + rhs.len();
	unsigned lenOfThis = (*this).len();
	unsigned lenOfRhs = rhs.len();
	char* buffer = new char[len + 1];
	int i = 0;
	for (unsigned i =0; i < lenOfThis; i++) {
		buffer[i] = buff[i];
	}
	int j = 0;
	for (; i < len; i++) {
		buffer[i] = rhs.buff[j++];
	}
	buffer[len] = '\0';
	MyStr result(buffer);
	delete[] buffer;
	return result;
}

MyStr MyStr::operator+(char ch) const {
	char* buffer = new char[len() + 2];
	for (unsigned i = 0; i < len(); i++) {
		buffer[i] = buff[i];
	}
	buffer[len()] = ch;
	buffer[len() + 1] = '\0';
	MyStr result(buffer);
	delete[] buffer;
	return result;
}

char MyStr::operator[](unsigned i) const {
	return buff[i];
}

char& MyStr::operator[](unsigned i) {
	return buff[i];
}

std::ostream& MyStr::ins(std::ostream& out) const {
	out << buff;
	return out;
}

std::istream& MyStr::ext(std::istream& in) {
	char buffer[100];
	in >> buffer;
	(*this) = MyStr(buffer);
	return in;
}

unsigned MyStr::len() const {
	return strlen(buff);
}

bool MyStr::operator==(const MyStr& rhs) const {
	if ((*this).len() != rhs.len()) return false;
	unsigned len = (*this).len();
	for (unsigned i = 0; i < len; i++) {
		if ((*this)[i] != rhs[i])
			return false;
	}
	return true;
}

std::ostream& operator<<(std::ostream& lhs, const MyStr& rhs) {
	return rhs.ins(lhs);
}

std::istream& operator>>(std::istream& lhs, MyStr& rhs) {
	return rhs.ext(lhs);
}

/*istream& getline(istream& in, MyStr& str, const char delim) {
	char ch;
	char buffer[300];
	in.get(ch);
	unsigned i=0;
	while (ch != delim) {
		buffer[i++] = ch;
		in.get(ch);
	}
	buffer[i] = '\0';
	str = MyStr(buffer);
	return in;
}*/