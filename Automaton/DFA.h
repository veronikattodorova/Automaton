#ifndef DFA_H
#define DFA_H
#include "State.h"
#include "MyStr.h"
#include "Exceptions.h"

template <typename T>
class DeterminateFiniteAutomaton {
public:
	DeterminateFiniteAutomaton();
	DeterminateFiniteAutomaton(const DeterminateFiniteAutomaton&);
	DeterminateFiniteAutomaton& operator=(const DeterminateFiniteAutomaton&);
	~DeterminateFiniteAutomaton();

	int inputSt(istream&, unsigned);
	int inputSym(istream&, unsigned);

	State* getState(MyStr str) const;
	unsigned getStateNum(MyStr) const;
	unsigned getNum()const;
	State* getArr() const;

	int makeTable(istream&);
	int prntTable(ostream&) const;

	State* getBeg() const;

	int setBegIO(istream&);
	int setBeg(MyStr) throw(AutomatonStateException);

	int setEndIO(istream&);
	int setEnd(MyStr) throw (AutomatonStateException);

	int fillArr(T*, MyStr) const;
	State* transition(State*, T) const;
	bool readWord() const;

private:
	unsigned numOfSt;
	State* states;
	unsigned symbols;
	T* alphabet;
	State** trTable;
};

template <typename T>
DeterminateFiniteAutomaton<T>::DeterminateFiniteAutomaton():numOfSt(0),states(nullptr),symbols(0),alphabet(nullptr),trTable(nullptr){}

template <typename T>
DeterminateFiniteAutomaton<T>::DeterminateFiniteAutomaton(const DeterminateFiniteAutomaton& rhs) : numOfSt(rhs.numOfSt), states(new State[numOfSt]),
symbols(rhs.symbols), alphabet(new T[symbols]) {
	for (int i = 0; i < numOfSt; i++) {
		states[i] = rhs.states[i];
	}
	for (int i = 0; i < symbols; i++) {
		alphabet[i] = rhs.alphabet[i];
	}
	trTable = new State * [numOfSt];
	for (int i = 0; i < numOfSt; i++) {
		trTable[i] = new State[symbols];
	}
	for (int i = 0; i < numOfSt; i++) {
		for (int k = 0; k < symbols; k++) {
			trTable[i][k] = rhs.trTable[i][k];
		}
	}
}

template <typename T>
DeterminateFiniteAutomaton<T>& DeterminateFiniteAutomaton<T>::operator=(const DeterminateFiniteAutomaton& rhs) {
	if (this != &rhs) {
		numOfSt = rhs.numOfSt;
		if (states != nullptr) {
			delete[] states;
		}
		states = new State[numOfSt];
		for (int i = 0; i < numOfSt; i++) {
			states[i] = rhs.states[i];
		}
		symbols = rhs.symbols;
		if (alphabet != nullptr) {
			delete[] alphabet;
			alphabet = nullptr;
		}
		alphabet = new T[symbols];
		for (int i = 0; i < symbols; i++) {
			alphabet[i] = rhs.alphabet[i];
		}
		if (trTable != nullptr) {
			for (int i = 0; i < numOfSt; i++) {
				delete[] trTable[i];
				trTable[i] = nullptr;
			}
			delete[] trTable;
			trTable = nullptr;
		}
		trTable = new State * [numOfSt];
		for (int i = 0; i < (*this).getNum(); i++) {
			trTable[i] = new State[symbols];
		}
		for (int i = 0; i < numOfSt; i++) {
			for (int k = 0; k < symbols; k++) {
				trTable[i][k] = rhs.trTable[i][k];
			}
		}

	}
	return *this;
}

template <typename T>
DeterminateFiniteAutomaton<T>::~DeterminateFiniteAutomaton() {
	if (states != nullptr) {
		delete[] states;
	}
	if (alphabet != nullptr) {
		delete[] alphabet;
	}
	if (trTable != nullptr) {
		for (int i = 0; i < numOfSt; i++) {
			delete[] trTable[i];
			trTable[i] = nullptr;
		}
		delete[] trTable;
	}
}

template <typename T>
int DeterminateFiniteAutomaton<T>::inputSt(istream& in, unsigned st) {
	MyStr str;
	numOfSt = st;
	if (states != nullptr) {
		delete[] states;
		states = nullptr;
	}
	states = new State[st];
	for (int i = 0; i < st; i++) {
		if (typeid(in) == typeid(cin)) {
			std::cout << "Enter state number " << i + 1 << ":";
		}
		in >> str;
		states[i].setName(str);
	}
	return 0;
}

template <typename T>
int DeterminateFiniteAutomaton<T>::inputSym(istream& in, unsigned sym) {
	symbols = sym;
	if (alphabet != nullptr) {
		delete[] alphabet;
		alphabet = nullptr;
	}
	alphabet = new T[sym];
	T a;
	for (int i = 0; i < sym; i++) {
		if (typeid(in) == typeid(cin)) {
			cout << "Enter symbol " << i + 1 << ":";
		}
		in >> a;
		alphabet[i] = a;
	}
	return 0;
}

template <typename T>
State* DeterminateFiniteAutomaton<T>::getState(MyStr str) const {
	for (int i = 0; i < numOfSt; i++) {
		if (str == states[i].getName()) {
			return states + i;
		}
	}
	return nullptr;
}

template <typename T>
unsigned DeterminateFiniteAutomaton<T>::getStateNum(MyStr str) const {
	for (int i = 0; i < numOfSt; i++) {
		if (str == states[i].getName()) {
			return i;
		}
	}
	return -1;
}

template <typename T>
unsigned DeterminateFiniteAutomaton<T>::getNum()const {
	return numOfSt;
}

template <typename T>
State* DeterminateFiniteAutomaton<T>::getArr() const {
	return states;
}

template <typename T>
int DeterminateFiniteAutomaton<T>::makeTable(istream& in) {
	if (trTable != nullptr) {
		for (int i = 0; i < numOfSt; i++) {
			delete[] trTable[i];
		}
		delete[] trTable;
		trTable = nullptr;
	}
	int states = numOfSt;
	trTable = new State * [states];
	for (int i = 0; i < states; i++) {
		trTable[i] = new State[symbols];
	}
	for (int i = 0; i < states; i++) {
		for (int k = 0; k < symbols; k++) {
			if (typeid(in) == typeid(cin)){
				here:
				cout << "Please enter (" << this->states[i] << ", " << alphabet[k] << ")->";
			}
			MyStr str;
			unsigned line;
			try {
				in >> str;
				if (getState(str) == nullptr) {
					line = __LINE__; throw AutomatonStateException(str);
				}
			}
			catch (AutomatonStateException& e){
				cerr << "Exception cought at line " << line << endl;
				cerr << "Exception type:" << typeid(e).name() << endl;
				cerr << e.message() << endl;
				goto here;
			}
			trTable[i][k] = *(getState(str));
		}
	}
	return 0;
}

template <typename T>
int DeterminateFiniteAutomaton<T>::setBegIO(istream& in) {
here:
	if (typeid(in) == typeid(cin)) {
		cout << "Enter an initial state:";
	}
	MyStr str;
	in >> str;
	try {
		setBeg(str);
	}
	catch (...) {
		goto here;
	}
	return 0;
}

template <typename T>
int DeterminateFiniteAutomaton<T>::setBeg(MyStr str) throw(AutomatonStateException) {
	if (getBeg() != nullptr) {
		getBeg()->setBeg();
	}
	State* tmp;
	unsigned line = 0;
	try {
		tmp = getState(str);
		if (tmp == nullptr) {
			line = __LINE__; throw AutomatonStateException(str);
		}
	}
	catch (AutomatonStateException& e) {
		cerr << "Exception cought at line " << line << endl;
		cerr << "Exception type:" << typeid(e).name() << endl;
		cerr << e.message() << endl;
		throw;
	}
	tmp->setBeg();
	return 0;
}

template <typename T>
State* DeterminateFiniteAutomaton<T>::getBeg() const {
	for (int i = 0; i < numOfSt; i++) {
		if (states[i].isBeg()) {
			return states + i;
		}
	}
	return nullptr;
}

template <typename T>
int DeterminateFiniteAutomaton<T>::setEndIO(istream& in) {
	unsigned num;
	if (typeid(in) == typeid(cin)) {
		there:
		cout << "Enter number of final states:";
	}
	in >> num;
	if (num > numOfSt) {
		cerr << "There cannot be " << num << " final states out of " << numOfSt << " states!\n";
		goto there;
	}
	MyStr str;
	for (int i = 0; i < num; i++) {
	here:
		if (typeid(in) == typeid(cin)) {
			cout << "Enter final state " << i + 1 << ": ";
		}
		in >> str;
		try {
			setEnd(str);
		}
		catch (...) {
			goto here;
		}
	}
	return 0;
}

template <typename T>
int DeterminateFiniteAutomaton<T>::setEnd(MyStr str) throw(AutomatonStateException) {
	State* tmp = getState(str);
	unsigned line = 0;
	try {
		if (tmp == nullptr) {
			line = __LINE__; throw (AutomatonStateException(str));
		}
	}
	catch (AutomatonStateException& e) {
		cerr << "Exception cought at line " << line << endl;
		cerr << "Exception type:" << typeid(e).name() << endl;
		cerr << e.message() << endl;
		throw;
	}
	tmp->setEnd();
	return 0;
}

template <typename T>
int DeterminateFiniteAutomaton<T>::fillArr(T* word, MyStr str) const {
	unsigned len = str.len();
	if (typeid(T) == typeid(int)) {
		for (int i = 0; i < len; i++) {
			word[i] = str[i] - '0';
		}
		return 0;
	}
	if (typeid(T) == typeid(char)) {
		for (int i = 0; i < len; i++) {
			word[i] = (T)str[i];
		}
		return 0;
	}
	return 0;
}

template <typename T>
State* DeterminateFiniteAutomaton<T>::transition(State* pos, T sym) const {
	unsigned stRow = getStateNum(pos->getName());
	unsigned stCol=-1;
	for (int i = 0; i < symbols; i++) {
		if (sym == alphabet[i]) {
			stCol = i;
			break;
		}
	}
	if (stCol == -1) {
		return nullptr;
	}
	pos = &(trTable[stRow][stCol]);
	return pos;

}

template <typename T>
bool DeterminateFiniteAutomaton<T>::readWord() const {
	MyStr str;
	cout << "Enter a word:";
	cin >> str;
	unsigned len = str.len();
	T* word = new T[len];
	fillArr(word, str);
	State* pos = (getBeg());
	for (int i = 0; i < len; i++) {
		pos = transition(pos, word[i]);
		//cout << (*pos).getName() << endl;
	}
	MyStr name = (*pos).getName();
	if ((getState(name))->isEnd()) {
		delete[] word;
		return true;
	}
	delete[] word;
	return false;

}

template <typename T>
istream& operator>>(istream& lhs, DeterminateFiniteAutomaton<T>& rhs) {
	unsigned num;
	if (typeid(lhs) == typeid(cin)) {
		cout << "Please enter number of states:";
	}
	lhs >> num;
	rhs.inputSt(lhs, num);
	if (typeid(lhs) == typeid(cin)) {
		cout << "Please enter number of symbols in the alphabet:";
	}
	lhs >> num;
	rhs.inputSym(lhs, num);
	rhs.makeTable(lhs);
	rhs.setBegIO(lhs);
	rhs.setEndIO(lhs);
	return lhs;
}

template <typename T>
int DeterminateFiniteAutomaton<T>::prntTable(ostream& out) const{
	out << "\t";
	for (int i = 0; i < symbols; i++) {
		out << alphabet[i] << '\t';
	}
	out << endl;
	for (int i = 0; i < numOfSt; i++) {
		out << states[i] << '\t';
		for (int k = 0; k < symbols; k++) {
			out << trTable[i][k] << "\t";
		}
		out << endl;
	}
	return 0;
}

template <typename T>
ostream& operator<<(ostream& lhs, const DeterminateFiniteAutomaton<T>& rhs) {
	lhs << "Transition table:" << endl;
	rhs.prntTable(lhs);
	lhs << "Initial state:" << *(rhs.getBeg()) << endl;
	lhs << "Final states: ";
	for (int i = 0; i < rhs.getNum(); i++) {
		if ((rhs.getArr() + i)->isEnd()) {
			lhs << *(rhs.getArr() + i) << "\t";
		}
	}
	return lhs;
}



#endif