#include "Menu.h"

int prntMenu() {
	cout << "\nChoose an option:" << endl;
	unsigned i = 1;
	cout << i++ << "-> Make automaton" << endl;
	cout << i++ << "-> Print automaton" << endl;
	cout << i++ << "-> Print current initial state" << endl;
	cout << i++ << "-> Read a word" << endl;
	cout << i++ << "->" << endl;
	cout << "0-> Exit program" << endl;
	return 0;
}
