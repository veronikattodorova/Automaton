#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <stdexcept>
#include "MyStr.h"

class AutomatonStateException : public std::exception
{
public:
	AutomatonStateException(MyStr);
	MyStr message() const;
private:
	MyStr state;
};

class NotEnoughAutomatonsException : public std::exception
{
public:
	NotEnoughAutomatonsException(MyStr);
	MyStr message() const;
private:
	MyStr status;
};

#endif
