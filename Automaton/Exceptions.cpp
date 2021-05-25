#include "Exceptions.h"

AutomatonStateException::AutomatonStateException(MyStr str) :state(str) {}
MyStr AutomatonStateException::message() const {
	MyStr errorMessage(state + " is not a valid state name!");
	return errorMessage;
}