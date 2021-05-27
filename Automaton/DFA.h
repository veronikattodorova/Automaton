#ifndef DFA_H
#define DFA_H
#include "State.h"
#include "MyStr.h"
#include "Exceptions.h"

template <typename T>
class DeterminateFiniteAutomaton
{
public:
	DeterminateFiniteAutomaton();
	DeterminateFiniteAutomaton(const DeterminateFiniteAutomaton&);
	DeterminateFiniteAutomaton& operator=(const DeterminateFiniteAutomaton&);
	~DeterminateFiniteAutomaton();

	int inputSt(std::istream&, unsigned);
	int inputSym(std::istream&, unsigned);

	unsigned getStateCount() const { return stateCount; }
	State* getState(const MyStr& str) const;

	State* getState(unsigned index) const
	{
		if (index < stateCount) return states + index;
		return nullptr;
	}

	unsigned getStateNum(const MyStr& str) const;
	unsigned getNum() const;
	State* getArr() const;

	int makeTable(std::istream&);
	int printTable(std::ostream&) const;

	State* getBeg() const;

	int setBegIO(std::istream&) const;
	int setBeg(const MyStr& str) const;

	int setEndIO(std::istream&) const;
	int setEnd(const MyStr& str) const;

	int fillArr(T*, MyStr) const;
	State* transition(State*, T) const;
	bool readWord() const;

	DeterminateFiniteAutomaton operator&(const DeterminateFiniteAutomaton&);


private:
	unsigned stateCount;
	State* states;
	unsigned symbols;
	T* alphabet;
	State** trTable;

	int makeTableFromAutomatons(const DeterminateFiniteAutomaton& automaton1,
	                            const DeterminateFiniteAutomaton& automaton2);
};

template <typename T>
DeterminateFiniteAutomaton<T>::DeterminateFiniteAutomaton(): stateCount(0), states(nullptr), symbols(0),
                                                             alphabet(nullptr), trTable(nullptr)
{
}

template <typename T>
DeterminateFiniteAutomaton<T>::DeterminateFiniteAutomaton(const DeterminateFiniteAutomaton& rhs) :
	stateCount(rhs.stateCount), states(new State[stateCount]),
	symbols(rhs.symbols), alphabet(new T[symbols])
{
	for (int i = 0; i < stateCount; i++)
	{
		states[i] = rhs.states[i];
	}
	for (int i = 0; i < symbols; i++)
	{
		alphabet[i] = rhs.alphabet[i];
	}
	trTable = new State*[stateCount];
	for (int i = 0; i < stateCount; i++)
	{
		trTable[i] = new State[symbols];
	}
	for (int i = 0; i < stateCount; i++)
	{
		for (int k = 0; k < symbols; k++)
		{
			trTable[i][k] = rhs.trTable[i][k];
		}
	}
}

template <typename T>
DeterminateFiniteAutomaton<T>& DeterminateFiniteAutomaton<T>::operator=(const DeterminateFiniteAutomaton& rhs)
{
	if (this != &rhs)
	{
		stateCount = rhs.stateCount;
		if (states != nullptr)
		{
			delete[] states;
		}
		states = new State[stateCount];
		for (int i = 0; i < stateCount; i++)
		{
			states[i] = rhs.states[i];
		}
		symbols = rhs.symbols;
		if (alphabet != nullptr)
		{
			delete[] alphabet;
			alphabet = nullptr;
		}
		alphabet = new T[symbols];
		for (int i = 0; i < symbols; i++)
		{
			alphabet[i] = rhs.alphabet[i];
		}
		if (trTable != nullptr)
		{
			for (int i = 0; i < stateCount; i++)
			{
				delete[] trTable[i];
				trTable[i] = nullptr;
			}
			delete[] trTable;
			trTable = nullptr;
		}
		trTable = new State*[stateCount];
		for (int i = 0; i < (*this).getNum(); i++)
		{
			trTable[i] = new State[symbols];
		}
		for (int i = 0; i < stateCount; i++)
		{
			for (int k = 0; k < symbols; k++)
			{
				trTable[i][k] = rhs.trTable[i][k];
			}
		}
	}
	return *this;
}

template <typename T>
DeterminateFiniteAutomaton<T> DeterminateFiniteAutomaton<T>::operator&(const DeterminateFiniteAutomaton& rhs)
{
	DeterminateFiniteAutomaton<T> newAutomaton;

	return newAutomaton;
}

template <typename T>
DeterminateFiniteAutomaton<T>::~DeterminateFiniteAutomaton()
{
	if (states != nullptr)
	{
		delete[] states;
	}
	if (alphabet != nullptr)
	{
		delete[] alphabet;
	}
	if (trTable != nullptr)
	{
		for (unsigned i = 0; i < stateCount; i++)
		{
			delete[] trTable[i];
			trTable[i] = nullptr;
		}
		delete[] trTable;
	}
}

template <typename T>
int DeterminateFiniteAutomaton<T>::inputSt(std::istream& in, unsigned st)
{
	MyStr str;
	stateCount = st;
	if (states != nullptr)
	{
		delete[] states;
		states = nullptr;
	}
	states = new State[st];
	for (unsigned i = 0; i < st; i++)
	{
		if (typeid(in) == typeid(std::cin))
		{
			std::cout << "Enter state number " << i + 1 << ":";
		}
		in >> str;
		states[i].setName(str);
	}
	return 0;
}

template <typename T>
int DeterminateFiniteAutomaton<T>::inputSym(std::istream& in, unsigned sym)
{
	symbols = sym;
	if (alphabet != nullptr)
	{
		delete[] alphabet;
		alphabet = nullptr;
	}
	alphabet = new T[sym];
	T a;
	for (unsigned i = 0; i < sym; i++)
	{
		if (typeid(in) == typeid(std::cin))
		{
			std::cout << "Enter symbol " << i + 1 << ":";
		}
		in >> a;
		alphabet[i] = a;
	}
	return 0;
}

template <typename T>
State* DeterminateFiniteAutomaton<T>::getState(const MyStr& str) const
{
	for (unsigned i = 0; i < stateCount; i++)
	{
		if (str == states[i].getName())
		{
			return states + i;
		}
	}
	return nullptr;
}

template <typename T>
unsigned DeterminateFiniteAutomaton<T>::getStateNum(const MyStr& str) const
{
	for (unsigned i = 0; i < stateCount; i++)
	{
		if (str == states[i].getName())
		{
			return i;
		}
	}
	return -1;
}

template <typename T>
unsigned DeterminateFiniteAutomaton<T>::getNum() const
{
	return stateCount;
}

template <typename T>
State* DeterminateFiniteAutomaton<T>::getArr() const
{
	return states;
}

template <typename T>
int DeterminateFiniteAutomaton<T>::makeTable(std::istream& in)
{
	if (trTable != nullptr)
	{
		for (unsigned i = 0; i < stateCount; i++)
		{
			delete[] trTable[i];
		}
		delete[] trTable;
		trTable = nullptr;
	}
	int states = stateCount;
	trTable = new State*[states];
	for (int i = 0; i < states; i++)
	{
		trTable[i] = new State[symbols];
	}
	for (int i = 0; i < states; i++)
	{
		MyStr str;
		for (unsigned k = 0; k < symbols; k++)
		{
			while (true)
			{
				if (typeid(in) == typeid(std::cin))
				{
					std::cout << "Please enter (" << this->states[i] << ", " << alphabet[k] << ")->";
				}
				unsigned line;
				try
				{
					in >> str;
					if (getState(str) == nullptr)
					{
						line = __LINE__;
						throw AutomatonStateException(str);
					}
					break;
				}
				catch (AutomatonStateException& e)
				{
					std::cerr << "Exception caught at line " << line << std::endl;
					std::cerr << "Exception type:" << typeid(e).name() << std::endl;
					std::cerr << e.message() << std::endl;
				}
			}
			trTable[i][k] = *(getState(str));
		}
	}
	return 0;
}

template <typename T>
int DeterminateFiniteAutomaton<T>::makeTableFromAutomatons(const DeterminateFiniteAutomaton<T>& automaton1,
                                                           const DeterminateFiniteAutomaton<T>& automaton2)
{
	this->stateCount = automaton1.getStateCount() * automaton2.getStateCount();
	unsigned currentStateCount = 0;
	states = new State[stateCount];
	for (unsigned i = 0; i < automaton1.getStateCount(); i++)
	{
		for (unsigned j = 0; j < automaton2.getStateCount(); i++)
		{
			this->states[currentStateCount].setName(
				automaton1.getState(i)->getName() + automaton2.getState(j)->getName());
			currentStateCount++;
		}
	}
	for (auto i = 0; i < stateCount; i++)
	{
		std::cout << "State: " << states[i].getName() << "\n";
	}
	return 0;
}

template <typename T>
int DeterminateFiniteAutomaton<T>::setBegIO(std::istream& in) const
{
	while (true)
	{
		if (typeid(in) == typeid(std::cin))
		{
			std::cout << "Enter an initial state:";
		}
		MyStr str;
		in >> str;
		try
		{
			setBeg(str);
			break;
		}
		catch (...)
		{
			std::cout << "Error caught in setBegIO function!\n";
		}
	}
	return 0;
}

template <typename T>
int DeterminateFiniteAutomaton<T>::setBeg(const MyStr& str) const
{
	if (getBeg() != nullptr)
	{
		getBeg()->setBeg();
	}
	State* tmp = nullptr;
	unsigned line = 0;
	try
	{
		tmp = getState(str);
		if (tmp == nullptr)
		{
			line = __LINE__;
			throw AutomatonStateException(str);
		}
	}
	catch (AutomatonStateException& e)
	{
		std::cerr << "Exception caught at line " << line << std::endl;
		std::cerr << "Exception type:" << typeid(e).name() << std::endl;
		std::cerr << e.message() << std::endl;
		throw;
	}
	tmp->setBeg();
	return 0;
}

template <typename T>
State* DeterminateFiniteAutomaton<T>::getBeg() const
{
	for (unsigned i = 0; i < stateCount; i++)
	{
		if (states[i].isBeg())
		{
			return states + i;
		}
	}
	return nullptr;
}

template <typename T>
int DeterminateFiniteAutomaton<T>::setEndIO(std::istream& in) const
{
	unsigned num = 0;
	do
	{
		if (typeid(in) == typeid(std::cin))
		{
			std::cout << "Enter number of final states:";
		}
		in >> num;
		if (num > stateCount)
		{
			std::cerr << "There cannot be " << num << " final states out of " << stateCount << " states!\n";
		}
	}
	while (num > stateCount);

	MyStr str;

	for (unsigned i = 0; i < num; i++)
	{
		while (true)
		{
			if (typeid(in) == typeid(std::cin))
			{
				std::cout << "Enter final state " << i + 1 << ": ";
			}
			in >> str;

			try
			{
				setEnd(str);
				break;
			}
			catch (...)
			{
				std::cout << "Error caught!\n";
			}
		}
	}
	return 0;
}

template <typename T>
int DeterminateFiniteAutomaton<T>::setEnd(const MyStr& str) const
{
	State* tmp = getState(str);
	unsigned line = 0;
	try
	{
		if (tmp == nullptr)
		{
			line = __LINE__;
			throw (AutomatonStateException(str));
		}
	}
	catch (AutomatonStateException& e)
	{
		std::cerr << "Exception cought at line " << line << std::endl;
		std::cerr << "Exception type:" << typeid(e).name() << std::endl;
		std::cerr << e.message() << std::endl;
		throw;
	}
	tmp->setEnd();
	return 0;
}

template <typename T>
int DeterminateFiniteAutomaton<T>::fillArr(T* word, MyStr str) const
{
	unsigned len = str.len();
	if (typeid(T) == typeid(int))
	{
		for (unsigned i = 0; i < len; i++)
		{
			word[i] = str[i] - '0';
		}
		return 0;
	}
	if (typeid(T) == typeid(char))
	{
		for (unsigned i = 0; i < len; i++)
		{
			word[i] = static_cast<T>(str[i]);
		}
		return 0;
	}
	return 0;
}

template <typename T>
State* DeterminateFiniteAutomaton<T>::transition(State* pos, T sym) const
{
	unsigned stRow = getStateNum(pos->getName());
	int stCol = -1;
	for (int i = 0; i < symbols; i++)
	{
		if (sym == alphabet[i])
		{
			stCol = i;
			break;
		}
	}
	if (stCol == -1)
	{
		return nullptr;
	}
	pos = &(trTable[stRow][stCol]);
	return pos;
}

template <typename T>
bool DeterminateFiniteAutomaton<T>::readWord() const
{
	MyStr str;
	std::cout << "Enter a word:";
	std::cin >> str;
	unsigned len = str.len();
	T* word = new T[len];
	fillArr(word, str);
	State* pos = (getBeg());
	for (unsigned i = 0; i < len; i++)
	{
		pos = transition(pos, word[i]);
		//cout << (*pos).getName() << endl;
	}
	MyStr name = (*pos).getName();
	if ((getState(name))->isEnd())
	{
		delete[] word;
		return true;
	}
	delete[] word;
	return false;
}

template <typename T>
std::istream& operator>>(std::istream& lhs, DeterminateFiniteAutomaton<T>& rhs)
{
	unsigned num;
	if (typeid(lhs) == typeid(std::cin))
	{
		std::cout << "Please enter number of states:";
	}
	lhs >> num;
	rhs.inputSt(lhs, num);
	if (typeid(lhs) == typeid(std::cin))
	{
		std::cout << "Please enter number of symbols in the alphabet:";
	}
	lhs >> num;
	rhs.inputSym(lhs, num);
	rhs.makeTable(lhs);
	rhs.setBegIO(lhs);
	rhs.setEndIO(lhs);
	return lhs;
}

template <typename T>
int DeterminateFiniteAutomaton<T>::printTable(std::ostream& out) const
{
	out << "\t";
	for (unsigned i = 0; i < symbols; i++)
	{
		out << alphabet[i] << '\t';
	}
	out << std::endl;
	for (unsigned i = 0; i < stateCount; i++)
	{
		out << states[i] << '\t';
		for (unsigned k = 0; k < symbols; k++)
		{
			out << trTable[i][k] << "\t";
		}
		out << std::endl;
	}
	return 0;
}

template <typename T>
std::ostream& operator<<(std::ostream& lhs, const DeterminateFiniteAutomaton<T>& rhs)
{
	lhs << "Transition table:" << std::endl;
	rhs.printTable(lhs);
	lhs << "Initial state:" << *(rhs.getBeg()) << std::endl;
	lhs << "Final states: ";
	for (unsigned i = 0; i < rhs.getNum(); i++)
	{
		if ((rhs.getArr() + i)->isEnd())
		{
			lhs << *(rhs.getArr() + i) << "\t";
		}
	}
	lhs << "\n";
	return lhs;
}


#endif
