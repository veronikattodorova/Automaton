#include "Menu.h"

int Menu::printMenu()
{
	std::cout << "\nChoose an option:" << std::endl;
	unsigned i = 1;
	std::cout << i++ << "-> Make a new automaton" << std::endl;
	std::cout << i++ << "-> Print automaton" << std::endl;
	std::cout << i++ << "-> Print initial state of automaton" << std::endl;
	std::cout << i++ << "-> Read a word" << std::endl;
	std::cout << i++ << "-> Select a new active automaton" << std::endl;
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
			printAutomaton();
			break;
		}
	case 3:
	{
		printInitialState();
		break;
	}
	case 4:
	{
		readWord();
		break;
	}

	default:
		std::cout << "There is no such option\n";
	}
	return 0;
}

int Menu::makeAutomaton()
{
	std::cout << "Enter type of the automaton:" << std::endl;
	std::cout << "1-> DeterminateFiniteAutomaton with an int alphabet" << std::endl;
	std::cout << "2-> DeterminateFiniteAutomaton with a char alphabet" << std::endl;

	int typeChoice;
	std::cin >> typeChoice;
	while (typeChoice != 1 && typeChoice != 2)
	{
		std::cout << "There is no such option, please choose one of the following: " << std::endl;
		std::cout << "1-> DeterminateFiniteAutomaton with an int alphabet" << std::endl;
		std::cout << "2-> DeterminateFiniteAutomaton with a char alphabet" << std::endl;
		std::cin >> typeChoice;
	}

	std::cout << "Input data form:" << std::endl;
	std::cout << "1-> the console" << std::endl;
	std::cout << "2-> a txt file" << std::endl;
	int importFromFile;
	std::cin >> importFromFile;
	while (importFromFile != 1 && importFromFile != 2)
	{
		std::cout << "There is no such option, please choose one of the following: " << std::endl;
		std::cout << "1-> The console" << std::endl;
		std::cout << "2-> A txt file" << std::endl;
		std::cin >> importFromFile;
	}
	importFromFile--; //Decrement by 1 so that the "create from console" option becomes 0 (false)

	if (typeChoice == 1)
	{
		try
		{
			makeIntAutomaton(importFromFile);
		}
		catch (...)
		{
			return 0;
		}
	}
	else
	{
		try
		{
			makeCharAutomaton(importFromFile);
		}
		catch (...)
		{
			return 0;
		}
	}
	return 1;
}

int Menu::printAutomaton() const
{
	int type;
	std::cout << "Choose the automaton that you want to print!\n";
	int automatonIndex = chooseAutomaton(type);
	if (automatonIndex >= 0) {
		if (type == 1)
		{
			std::cout << intAutomatons[automatonIndex];
		}
		else
		{
			std::cout << charAutomatons[automatonIndex];
		}
	}
	return automatonIndex;
}

int Menu::printInitialState()
{
	int type;
	std::cout << "Choose the automaton, which initial state you want to get!\n";
	int automatonIndex = chooseAutomaton(type);
	if (type == 1) {
		std::cout << "\nCurrent initial state:" << *(intAutomatons[automatonIndex].getBeg()) << std::endl;
		std::cout << "Do you want to change the initial state?" << std::endl;
		std::cout << "1-> yes\n2-> no\n";
		int choice;
		std::cin >> choice;
		while (choice != 1 && choice != 2)
		{
			std::cout << "There is no such option!" << std::endl;
			std::cin >> choice;
		}
		if (choice == 1) {
			{
				intAutomatons[automatonIndex].setBegIO(std::cin);
			}
		}

	}
	else
	{
		std::cout << "\nCurrent initial state:" << *(charAutomatons[automatonIndex].getBeg()) << std::endl;
		std::cout << "Do you want to change the initial state?" << std::endl;
		std::cout << "1-> yes\n2-> no\n";
		int choice;
		std::cin >> choice;
		while (choice != 1 && choice != 2)
		{
			std::cout << "There is no such option!" << std::endl;
			std::cin >> choice;
		}
		if (choice == 1) {
			{
				charAutomatons[automatonIndex].setBegIO(std::cin);
			}
		}
	}
	return 0;
}

int Menu::readWord() const
{
	int type;
	std::cout << "Choose the automaton that you want to read the word with!\n";
	int automatonIndex = chooseAutomaton(type);
	if (automatonIndex >= 0) {
		if (type == 1)
		{
			std::cout << (intAutomatons[automatonIndex].readWord() == 1 ? "The word was recognized by the automaton" : "The word was not recognized by the automaton");

		}
		else
		{
			std::cout << (charAutomatons[automatonIndex].readWord() == 1 ? "The word was recognized by the automaton" : "The word was not recognized by the automaton");

		}
	}
	return automatonIndex;
}

int Menu::makeIntAutomaton(bool createFromFile)
{
	DeterminateFiniteAutomaton<int> newAutomaton;
	if (createFromFile)
	{
		std::ifstream fin("in.txt");
		if (!fin)
		{
			std::cout << "File could not be opened\n";
			throw;
		}
		fin >> newAutomaton;
	}
	else
	{
		std::cin >> newAutomaton;
	}
	intAutomatons.push_back(newAutomaton);
	return 0;
}

int Menu::makeCharAutomaton(bool createFromFile)
{
	DeterminateFiniteAutomaton<char> newAutomaton;
	if (createFromFile)
	{
		std::ifstream fin("in.txt");
		if (!fin)
		{
			std::cout << "File could not be opened\n";
			throw;
		}
		fin >> newAutomaton;
	}
	else
	{
		std::cin >> newAutomaton;
	}
	charAutomatons.push_back(newAutomaton);
	return 0;
}

int Menu::chooseAutomaton(int& type) const
{
	int automatonIndex = -1;
	if (intAutomatons.empty() && charAutomatons.empty())
	{
		std::cout << "There are no automatons made!\n";
		return -1;
	}

	std::cout << "Choose the type of automaton!\n";
	std::cout << "1-> DeterminateFiniteAutomaton with an int alphabet\n";
	std::cout << "2-> DeterminateFiniteAutomaton with a char alphabet\n";
	std::cin >> type;
	while (type != 1 && type != 2)
	{
		std::cout << "Choose the type of automaton!\n";
		std::cout << "1-> DeterminateFiniteAutomaton with an int alphabet\n";
		std::cout << "2-> DeterminateFiniteAutomaton with a char alphabet\n";
		std::cin >> type;
	}

	if (type == 1)
	{
		if (intAutomatons.empty())
		{
			std::cout << "There are no int automatons made!\n";
			return -1;
		}
		std::cout << "Enter the index of the automaton you want to choose:";
		std::cin >> automatonIndex;
		while (intAutomatons.size() <= automatonIndex) //Int automatons
		{
			std::cout << "There is no int automaton at this index!\n\n";
			std::cout << "Enter the index of the automaton you want to choose:";
			std::cin >> automatonIndex;
		}
	}
	else
	{
		if (charAutomatons.empty())
		{
			std::cout << "There are no char automatons made!\n";
			return -1;
		}
		std::cout << "Enter the index of the automaton you want to choose:";
		std::cin >> automatonIndex;
		while (charAutomatons.size() <= automatonIndex) //char automatons
		{
			std::cout << "There is no char automaton at this index!\n\n";
			std::cout << "Enter the index of the automaton you want to choose:";
			std::cin >> automatonIndex;
		}
	}
	return automatonIndex;
}
