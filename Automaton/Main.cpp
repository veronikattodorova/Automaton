#include "DFA.h"
#include "Menu.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
	Menu menu;

	menu.printMenu();
	int option;
	cout << "\nEnter an option number:";
	cin >> option;
	while (option != 0)
	{
		menu.selectMenuOption(option);
		menu.printMenu();
		cout << "\nEnter an option number:";
		cin >> option;
	}
}
