#ifndef MENU_H
#define MENU_H
#include <iostream>
#include "MyStr.h"
#include "DFA.h"
using namespace std;

int prntMenu();

template <typename A, typename B, template<typename> class DeterminateFiniteAutomaton>
int switchMenu(int a, DeterminateFiniteAutomaton<A>& aInt, DeterminateFiniteAutomaton<B>& aChar, int& type, istream& fin, ostream& fout) {
	switch (a) {
	case 1: {
		makeAutomaton(aInt, aChar, type, fin);
		break;
	}
	case 2: {
		prntAutomaton(aInt, aChar, type, fout);
		break;
	}
	case 3: {
		if (type == 1)
			prntInitial(aInt);
		else if (type == 2)
			prntInitial(aChar);
		else cout << "There is no automaton made!" << endl;
		break;
	}
	case 4: {
		if (type == 1)
			cout << ((aInt.readWord()==1)? "The word was accepted by the automaton!" : "The word was not accepted by the automaton!" )<< endl;
		else if (type == 2)
			cout << ((aChar.readWord() == 1) ? "The word was accepted by the automaton!" : "The word was not accepted by the automaton!") << endl;
		else cout << "There is no automaton made!" << endl;
		break;
	}
	case 5: {
	}
	default:
		cout << "There is no such option\n";
	}
	return 0;
}

template <typename A, typename B, template<typename> class DeterminateFiniteAutomaton>
int makeAutomaton(DeterminateFiniteAutomaton<A>& aInt, DeterminateFiniteAutomaton<B>& aChar, int& type, istream& fin) {
here:
	cout << "Enter type of the automaton:" << endl;
	cout << "1-> DeterminateFiniteAutomaton with an int alphabet" << endl;
	cout << "2-> DeterminateFiniteAutomaton with a char alphabet" << endl;
	int choice1;
	cin >> choice1;
	if (choice1 != 1 && choice1 != 2) {
		cout << "There is no such option!" << endl;
		goto here;
	}
there:
	cout << "Input data form:" << endl;
	cout << "1-> the console" << endl;
	cout << "2-> a txt file" << endl;
	int choice2;
	cin >> choice2;
	if (choice2 != 1 && choice2 != 2) {
		cout << "There is no such option!" << endl;
		goto there;
	}
	if (choice1 == 1) {
		type = 1;
		if (choice2 == 1) {
			cin >> aInt;
		}
		else {
			fin >> aInt;
		}
	}
	else if (choice1 == 2) {
		type = 2;
		if (choice2 == 1) {
			cin >> aChar;
		}
		else {
			fin >> aChar;
		}
	}
	return 0;
}

template <typename A, typename B, template<typename> class DeterminateFiniteAutomaton>
int prntAutomaton(DeterminateFiniteAutomaton<A>& aInt, DeterminateFiniteAutomaton<B>& aChar, int& type, ostream& fout) {
	if (type == 0) {
		cout << "There is no automaton made!" << endl;
		return 0;
	}
	here:
	cout << "Print automaton:" << endl;
	cout << "1-> in the console" << endl;
	cout << "2-> in a txt file" << endl;
	int choice;
	cin >> choice;
	switch (choice) {
	case 1: {
		if (type == 1) {
			cout << aInt << endl;
		}
		else if (type == 2) {
			cout << aChar << endl;
		}
		break;
	}
	case 2: {
		if (type == 1) {
			fout << aInt << endl;
		}
		else if (type == 2) {
			fout << aChar << endl;
		}
		break;
	}
	default: {
		cout << "There is no such option!" << endl;
		goto here;
	}
	}
    return 0;
}

template <typename A,template<typename> class DeterminateFiniteAutomaton>
int prntInitial(DeterminateFiniteAutomaton<A>& a) {
	cout << "\nCurrent initial state:" << *(a.getBeg()) << endl;
	here:
	cout << "Do you want to change the initial state?" << endl;
	cout << "1-> yes\n2-> no\n";
	int choice;
	cin >> choice;
	switch (choice) {
	case 1: {
		a.setBegIO(cin);
		break;
	}
	case 2: {
		break;
	}
	default:
		cout << "There is no such option!\n";
		goto here;
	}
	return 0;
}

#endif