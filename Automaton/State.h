#ifndef STATE_H
#define STATE_H
#include "MyStr.h"

class State
{
public:
	State();
	State(MyStr);
	State(const State&);
	State& operator=(const State&);
	~State();

	int setBeg();
	int setEnd();
	int setName(MyStr);
	bool isBeg() const;
	bool isEnd() const;

	MyStr getSt1() const;
	MyStr getSt2() const;

	MyStr getName() const;
	std::ostream& ins(std::ostream&) const;
	std::istream& ext(std::istream&);

private:
	MyStr name;
	bool begin;
	bool end;
};

std::ostream& operator<<(std::ostream&, const State&);
std::istream& operator>>(std::istream&, State&);

#endif
