#ifndef STATE_H
#define STATE_H
#include "MyStr.h"

class State {
public:
	State();
	State(MyStr);
	State(const State&);
	State& operator=(const State&);
	~State();

	int  setBeg();
	int setEnd();
	int setName(MyStr);
	bool isBeg() const;
	bool isEnd() const;

	MyStr getSt1() const;
	MyStr getSt2()const;

	MyStr getName() const;
	ostream& ins(ostream&) const;
	istream& ext(istream&);

private:
	MyStr name;
	bool begin;
	bool end;
};

ostream& operator<<(ostream&, const State&);
istream& operator>>(istream&, State&);

#endif