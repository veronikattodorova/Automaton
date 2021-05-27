#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <vector>
#include <fstream>
#include "MyStr.h"
#include "DFA.h"

class Menu
{
public:
	int printMenu();
	int selectMenuOption(int option);

private:
	std::vector<DeterminateFiniteAutomaton<int>> intAutomatons;
	std::vector<DeterminateFiniteAutomaton<char>> charAutomatons;

	int makeAutomaton();
	int printAutomaton() const;
	int printInitialState();
	int readWord() const;
	int makeIntAutomaton(bool createFromFile);
	int makeCharAutomaton(bool createFromFile);
	int chooseAutomaton(int& type) const;

};



/*

template <typename A, typename B, template<typename> class DeterminateFiniteAutomaton>
int switchMenu(int a, std::vector<DeterminateFiniteAutomaton<A>>& intAutomatons,
               std::vector<DeterminateFiniteAutomaton<B>>& charAutomatons, int& type, std::istream& fin,
               std::ostream& fout)
{
	switch (a)
	{
	case 1:
		{
			makeAutomaton(intAutomatons, aChar, type, fin);
			break;
		}
	case 2:
		{
			printAutomaton(aInt, aChar, type, fout);
			break;
		}
	case 3:
		{
			if (type == 1)
				printInitial(aInt);
			else if (type == 2)
				printInitial(aChar);
			else std::cout << "There is no automaton made!" << std::endl;
			break;
		}
	case 4:
		{
			if (type == 1)
				std::cout << ((aInt.readWord() == 1)
					              ? "The word was accepted by the automaton!"
					              : "The word was not accepted by the automaton!") << std::endl;
			else if (type == 2)
				std::cout << ((aChar.readWord() == 1)
					              ? "The word was accepted by the automaton!"
					              : "The word was not accepted by the automaton!") << std::endl;
			else std::cout << "There is no automaton made!" << std::endl;
			break;
		}
	case 5:
		{
		}
	default:
		std::cout << "There is no such option\n";
	}
	return 0;
}

template <typename A, typename B, template<typename> class DeterminateFiniteAutomaton>
int makeAutomaton(DeterminateFiniteAutomaton<A>& aInt, DeterminateFiniteAutomaton<B>& aChar, int& type,
                  std::istream& fin)
{
	std::cout << "Enter type of the automaton:" << std::endl;
	std::cout << "1-> DeterminateFiniteAutomaton with an int alphabet" << std::endl;
	std::cout << "2-> DeterminateFiniteAutomaton with a char alphabet" << std::endl;
	int choice1;
	std::cin >> choice1;
	while (choice1 != 1 && choice1 != 2)
	{
		std::cout << "There is no such option!" << std::endl;
		std::cin >> choice1;
	}

	std::cout << "Input data form:" << std::endl;
	std::cout << "1-> the console" << std::endl;
	std::cout << "2-> a txt file" << std::endl;
	int choice2;
	std::cin >> choice2;
	while (choice2 != 1 && choice2 != 2)
	{
		std::cout << "There is no such option!" << std::endl;
		std::cin >> choice2;
	}
	if (choice1 == 1)
	{
		type = 1;
		if (choice2 == 1)
		{
			std::cin >> aInt;
		}
		else
		{
			fin >> aInt;
		}
	}
	else if (choice1 == 2)
	{
		type = 2;
		if (choice2 == 1)
		{
			std::cin >> aChar;
		}
		else
		{
			fin >> aChar;
		}
	}
	return 0;
}

template <typename A, typename B, template<typename> class DeterminateFiniteAutomaton>
int printAutomaton(DeterminateFiniteAutomaton<A>& aInt, DeterminateFiniteAutomaton<B>& aChar, int& type,
                   std::ostream& fout)
{
	if (type == 0)
	{
		std::cout << "There is no automaton made!" << std::endl;
		return 0;
	}
	std::cout << "Print automaton:" << std::endl;
	std::cout << "1-> in the console" << std::endl;
	std::cout << "2-> in a txt file" << std::endl;
	int choice;
	std::cin >> choice;
	while (choice != 1 && choice != 2)
	{
		std::cout << "There is no such option!" << std::endl;
		std::cin >> choice;
	}
	switch (choice)
	{
	case 1:
		{
			if (type == 1)
			{
				std::cout << aInt << std::endl;
			}
			else if (type == 2)
			{
				std::cout << aChar << std::endl;
			}
			break;
		}
	case 2:
		{
			if (type == 1)
			{
				fout << aInt << std::endl;
			}
			else if (type == 2)
			{
				fout << aChar << std::endl;
			}
			break;
		}
	default:
		{
			break;
		}
	}
	return 0;
}

template <typename A, template<typename> class DeterminateFiniteAutomaton>
int printInitial(DeterminateFiniteAutomaton<A>& a)
{
	std::cout << "\nCurrent initial state:" << *(a.getBeg()) << std::endl;
	std::cout << "Do you want to change the initial state?" << std::endl;
	std::cout << "1-> yes\n2-> no\n";
	int choice;
	std::cin >> choice;
	while (choice != 1 && choice != 2)
	{
		std::cout << "There is no such option!" << std::endl;
		std::cin >> choice;
	}
	switch (choice)
	{
	case 1:
		{
			a.setBegIO(std::cin);
			break;
		}
	case 2:
		{
			break;
		}
	default:
		break;
	}
	return 0;
} */

#endif
