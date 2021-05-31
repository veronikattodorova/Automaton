#ifndef MENU_H
#define MENU_H
#include <vector>
#include "MyStr.h"
#include "DFA.h"

enum CreationOptions
{
	OPTION_CONSOLE = 1,
	OPTION_TXT_FILE,
	OPTION_UNIFY,
	OPTION_INTERSECT,
	OPTION_NEGATE
};

enum DFAOperations
{
	OPERATION_UNIFY,
	OPERATION_INTERSECT,
	OPERATION_NEGATE
};

class Menu
{
public:
	int printMenu();
	int selectMenuOption(int option);

private:
	std::vector<DeterminateFiniteAutomaton<int>> intAutomatons;
	std::vector<DeterminateFiniteAutomaton<char>> charAutomatons;

	int makeAutomaton();

	static int chooseAutomatonType();
	static CreationOptions chooseCreationMethod();
};

template <typename T>
int chooseAutomaton(std::vector<DeterminateFiniteAutomaton<T>>& automatonArr)
{
	int automatonIndex;
	if (automatonArr.empty())
	{
		std::cout << "There are no automatons made of this type!\n";
		return -1;
	}
	std::cout << "Enter the index of the automaton you want to choose:";
	std::cin >> automatonIndex;
	while (automatonArr.size() <= automatonIndex && automatonIndex < 0)
	{
		std::cout << "There is no automaton of this type at this index!\n\n";
		std::cout << "Enter the index of the automaton you want to choose:";
		std::cin >> automatonIndex;
	}
	return automatonIndex;
}

template <typename T>
int printAutomaton(std::vector<DeterminateFiniteAutomaton<T>>& automatonArr)
{
	std::cout << "Choose the automaton that you want to print!\n";
	int automatonIndex = chooseAutomaton<T>(automatonArr);
	if (automatonIndex >= 0)
	{
		int outputChoice = 0;
		std::cout << "Please choose where you wish to print the file!\n";
		std::cout << "1-> Print to the console\n";
		std::cout << "2-> Print to external file - out.txt\n";
		std::cin >> outputChoice;
		while (outputChoice != 1 && outputChoice != 2)
		{
			std::cout << "Please choose where you wish to print the file!\n";
			std::cout << "1-> Print to the console\n";
			std::cout << "2-> Print to external file - out.txt\n";
		}
		if (outputChoice == 1)
			std::cout << automatonArr[automatonIndex];
		else
		{
			std::fstream fout("out.txt");
			if (!fout)
			{
				std::cout << "File could not be opened\n";
				return -1;
			}
			fout << automatonArr[automatonIndex];
		}
	}
	return automatonIndex;
}

template <typename T>
int inputFromFile(DeterminateFiniteAutomaton<T>& newAutomaton)
{
	std::ifstream fin("in.txt");
	if (!fin)
	{
		std::cout << "File could not be opened\n";
		return -1;
	}
	fin >> newAutomaton;
	return 0;
}

template <typename T>
int printInitialState(std::vector<DeterminateFiniteAutomaton<T>>& automatonArr)
{
	int automatonIndex = chooseAutomaton<T>(automatonArr);
	if (automatonIndex >= 0)
	{
		std::cout << "\nCurrent initial state:" << *(automatonArr[automatonIndex].getBeg()) << std::endl;
		std::cout << "Do you want to change the initial state?" << std::endl;
		std::cout << "1-> yes\n2-> no\n";
		int choice;
		std::cin >> choice;
		while (choice != 1 && choice != 2)
		{
			std::cout << "There is no such option!" << std::endl;
			std::cin >> choice;
		}
		if (choice == 1)
		{
			{
				automatonArr[automatonIndex].setBegIO(std::cin);
			}
		}
	}
	return 0;
}

template <typename T>
int readWord(std::vector<DeterminateFiniteAutomaton<T>>& automatonArr)
{
	int automatonIndex = chooseAutomaton<T>(automatonArr);
	if (automatonIndex >= 0)
	{
		std::cout << (automatonArr[automatonIndex].readWord() == 1
			              ? "The word was recognized by the automaton"
			              : "The word was not recognized by the automaton");
	}
	return 0;
}

template <typename T>
int executeAutomatonOpeartions(DeterminateFiniteAutomaton<T>& newAutomaton,
                               std::vector<DeterminateFiniteAutomaton<T>>& automatonArr, DFAOperations operation)
{
	if (operation == OPERATION_UNIFY)
	{
		if (automatonArr.size() < 2)
		{
			throw NotEnoughAutomatonsException("There are not enough automatons of this type!");
		}
		std::cout << "Choose the automatons to unify: \n";
		int automatonForUnion1 = chooseAutomaton<T>(automatonArr);
		int automatonForUnion2 = chooseAutomaton<T>(automatonArr);
		newAutomaton = automatonArr[automatonForUnion1] | automatonArr[automatonForUnion2];
	}
	if (operation == OPERATION_INTERSECT)
	{
		if (automatonArr.size() < 2)
		{
			throw NotEnoughAutomatonsException("There are not enough automatons of this type!");
		}
		std::cout << "Choose the automatons to intersect: \n";
		int automatonForIntersect1 = chooseAutomaton<T>(automatonArr);
		int automatonForIntersect2 = chooseAutomaton<T>(automatonArr);

		newAutomaton = automatonArr[automatonForIntersect1] & automatonArr[automatonForIntersect2];
	}
	else
	{
		if (automatonArr.size() == 0)
		{
			throw NotEnoughAutomatonsException("There are no automatons of this type!");
		}
		std::cout << "Choose the automatons to inverse: \n";
		int automatonToInverseIndex = chooseAutomaton<T>(automatonArr);
		DeterminateFiniteAutomaton<T> automatonToInverse = automatonArr[automatonToInverseIndex];
		newAutomaton = automatonToInverse ^ automatonToInverse;
	}
	return 0;
}

template <typename T>
int createAutomatonAndPush(CreationOptions method, std::vector<DeterminateFiniteAutomaton<T>>& automatonArr)
{
	DeterminateFiniteAutomaton<T> newAutomaton;

	switch (method)
	{
	case OPTION_CONSOLE:
		std::cin >> newAutomaton;
		break;
	case OPTION_TXT_FILE:
		inputFromFile<T>(newAutomaton);
		break;
	case OPTION_UNIFY:
		try
		{
			executeAutomatonOpeartions<T>(newAutomaton, automatonArr, OPERATION_UNIFY);
		}
		catch (NotEnoughAutomatonsException e)
		{
			std::cout << e.message() << std::endl;
			return -1;
		}
		break;
	case OPTION_INTERSECT:
		try
		{
			executeAutomatonOpeartions<T>(newAutomaton, automatonArr, OPERATION_INTERSECT);
		}
		catch (NotEnoughAutomatonsException e)
		{
			std::cout << e.message() << std::endl;
			return -1;
		}
		break;
	case OPTION_NEGATE:
		try
		{
			executeAutomatonOpeartions<T>(newAutomaton, automatonArr, OPERATION_NEGATE);
		}
		catch (NotEnoughAutomatonsException e)
		{
			std::cout << e.message() << std::endl;
			return -1;
		}
		break;
	}
	automatonArr.push_back(newAutomaton);

	return 0;
}

#endif
