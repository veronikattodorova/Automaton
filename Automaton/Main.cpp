#include "DFA.h"
#include "Menu.h"
#include <iostream>
#include <fstream>
using namespace std;

int main() {
	DeterminateFiniteAutomaton<int> aInt;
	DeterminateFiniteAutomaton<char> aChar;
	ifstream fin("in.txt");
	ofstream fout("out.txt");
	if (!fin) {
		cerr << "Could not open file!" << endl;
		return -1;
	}
	if (!fout) {
		cerr << "Could not open file!" << endl;
		return -1;
	}
	int num;
	int type=0;
	//1-int;
	//2-char;
here:
	prntMenu();
	cout << "\nEnter an option number:";
	cin>>num;
	while (num != 0) {
		switchMenu(num,aInt,aChar,type,fin,fout);
		goto here;
	}
}