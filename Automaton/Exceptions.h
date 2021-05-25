#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <stdexcept>
#include "MyStr.h"

class AutomatonStateException :public std::exception {
public:
	AutomatonStateException(MyStr);
	MyStr message() const;
private:
	MyStr state;
};

#endif
