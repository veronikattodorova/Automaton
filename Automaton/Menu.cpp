#include "Menu.h"
#include <iostream>
#include <fstream>

int Menu::printMenu()
{
	std::cout << "\nChoose an option:" << std::endl;
	unsigned i = 1;
	std::cout << i++ << "-> Make a new automaton" << std::endl;
	std::cout << i++ << "-> Print automaton" << std::endl;
	std::cout << i++ << "-> Print initial state of automaton" << std::endl;
	std::cout << i++ << "-> Read a word" << std::endl;
	std::cout << "0-> Exit program" << std::endl;
	return 0;
}

int Menu::selectMenuOption(int option)
{
	switch (option)
	{
	case 1:
		{
			makeAutomaton();
			break;
		}
	case 2:
		{
			int type = chooseAutomatonType();
			type == 1 ? printAutomaton<int>(intAutomatons) : printAutomaton<char>(charAutomatons);
			break;
		}
	case 3:
		{
			int type = chooseAutomatonType();
			type == 1 ? printInitialState<int>(intAutomatons) : printInitialState<char>(charAutomatons);
			break;
		}
	case 4:
		{
			int type = chooseAutomatonType();
			type == 1 ? readWord<int>(intAutomatons) : readWord<char>(charAutomatons);
			break;
		}

	default:
		std::cout << "There is no such option\n";
	}
	return 0;
}

int Menu::makeAutomaton()
{
	int type = chooseAutomatonType();
	CreationOptions inputMethod = chooseCreationMethod();


	bool importFromFile = inputMethod == 2;

	if (type == 1)
	{
		createAutomatonAndPush<int>(inputMethod, intAutomatons);
	}
	else if(type == 2)
	{
		createAutomatonAndPush<char>(inputMethod, charAutomatons);
	}
	return 1;
}

int Menu::chooseAutomatonType()
{
	int type = 0;
	std::cout << "Choose the type of automaton!\n";
	std::cout << "1-> DeterminateFiniteAutomaton with an int alphabet\n";
	std::cout << "2-> DeterminateFiniteAutomaton with a char alphabet\n";
	std::cin >> type;
	while (type != 1 && type != 2)
	{
		std::cout << "Invalid option!\n";
		std::cout << "Choose the type of automaton!\n";
		std::cout << "1-> DeterminateFiniteAutomaton with an int alphabet\n";
		std::cout << "2-> DeterminateFiniteAutomaton with a char alphabet\n";
		std::cin >> type;
	}
	return type;
}

CreationOptions Menu::chooseCreationMethod()
{
	std::cout << "How do you wish to create the automaton:" << std::endl;
	std::cout << "1-> Manually input data from the console" << std::endl;
	std::cout << "2-> Import data from a txt file" << std::endl;
	std::cout << "3-> Unify 2 existing automatons" << std::endl;
	std::cout << "4-> Intersect 2 existing automatons" << std::endl;
	std::cout << "5-> Inverse automatons" << std::endl;

	int methodOption;
	std::cin >> methodOption;
	while (methodOption < 1 || methodOption > 5)
	{
		std::cout << "There is no such option, please choose one of the following: " << std::endl;
		std::cout << "1-> Manually input data from the console" << std::endl;
		std::cout << "2-> Import data from a txt file" << std::endl;
		std::cout << "3-> Unify 2 existing automatons" << std::endl;
		std::cout << "4-> Intersect 2 existing automatons" << std::endl;
		std::cout << "5-> Inverse automatons" << std::endl;
		std::cin >> methodOption;
	}
	return static_cast<CreationOptions>(methodOption);
}
