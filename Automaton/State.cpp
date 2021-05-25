#include "State.h"
#include "MyStr.h"

State::State() :name("NoName"), begin(0), end(0) {}

State::State(MyStr str) : name(str), begin(false), end(false) {}

State::State(const State& rhs) : name(rhs.name), begin(rhs.begin), end(rhs.end) {}

State& State::operator=(const State& rhs) {
	if (this != &rhs) {
		name = rhs.name;
		begin = rhs.begin;
		end = rhs.end;
	}
	return (*this);
}

State::~State() {}

int  State::setBeg() {
	begin = !begin;
	return 0;
}
int State::setEnd() {
	end = !end;
	return 0;
}

int State::setName(MyStr str) {
	name = str;
	return 0;
}

bool State::isBeg() const {
	return begin;
}
bool State::isEnd() const {
	return end;
}

MyStr State::getSt1() const {
	unsigned i = 0; 
	unsigned cnt = 0;
	while (name[i] != ',') {
		cnt++;
		i++;
	}
	MyStr res;
	for (int i = 0; i < cnt; i++) {
		res = res + name[i];
	}
	return res;
}
MyStr State::getSt2()const {
	unsigned len = name.len();
	unsigned i = 0;
	unsigned cnt = 0;
	while (name[i] != ',') {
		cnt++;
		i++;
	}
	MyStr res;
	for (int i = cnt + 1; i < len; i++) {
		res = res + name[i];
	}
	return res;
}

MyStr State::getName() const {
	return name;
}

ostream& State::ins(ostream& out) const {
	out << name;
	return out;
}

ostream& operator<<(ostream& lhs, const State& rhs) {
	return rhs.ins(lhs);
}

istream& State::ext(istream& in) {
	MyStr str;
	in >> str;
	this->setName(str);
	return in;
}

istream& operator>>(istream& lhs, State& rhs) {
	return rhs.ext(lhs);
}