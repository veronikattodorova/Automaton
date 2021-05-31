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
	int printAutomaton() const;
	int printInitialState();
	int readWord() const;
	int chooseAutomaton(int& type) const;
	CreationOptions chooseCreationMethod() const;
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
	while (automatonArr.size() <= automatonIndex) //Int automatons
	{
		std::cout << "There is no automaton of this type at this index!\n\n";
		std::cout << "Enter the index of the automaton you want to choose:";
		std::cin >> automatonIndex;
	}
	return automatonIndex;
}

template <typename T>
int inputFromFile(DeterminateFiniteAutomaton<T> newAutomaton)
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
		std::cout << newAutomaton;
		return 0;
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
