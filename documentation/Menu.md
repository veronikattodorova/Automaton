# Menu Class

This class is responsible for presenting the capabilities of the application in a concise way. It provides the user with option that easy to understand and streamlines the process of creating `int` and `char` automatons and performing operations with them. Included in the header file are also some utility `template functions`, whose main role is to reduce code duplication and reduce the number of `if/else` statements for creating `different types` of automatons.

## Enums

The role of these enums, included in the header file, is to increase code readability and reduce the possibilities for errors when dealing with options (instead of using 1,2,3,4, etc., which can be confusing and complicated to follow)

### CreationOptions

Used by the menu methods that handle creating automatons to present the user with options for creating automatons.

### DFAOperations

Used in the automaton creation methods to call the appropriate operator for `unifying`, `intersecting`, or `reversing` automatons

## Data members

- `std::vector<DeterminateFiniteAutomaton<int>> intAutomatons` - Array of automatons with an `int` alphabet
- `std::vector<DeterminateFiniteAutomaton<char>> charAutomatons` - Array of automatons with a `char` alphabet

## Methods

### Public

- `printMenu()` - Prints the menu options to the console
- `selectMenuOption(int option)` - Calls the appropriate `template/utility functions`, based on the value passed as a parameter

### Private

These functions are only meant to be called inside the public methods and therefore are declared as private

- `chooseAutomatonType()` - Loops until the user enters either 1 or 2 and returns the input value
- `chooseCreationMethod()` - Loops until the user select an appropriate value to represent a `CreationOption` and returns it
- `makeAutomaton()` - Makes the user choose an automaton type and a method for creation with `chooseAutomatonType()` and `chooseCreationMethod()` and then call the template function `createAutomatonAndPush(CreationOptions method, std::vector<DeterminateFiniteAutomaton<T>>& automatonArr)` with the appropriate parameters

### Template functions

Functions, created in ored to increase code readability, reduce `branching` and satisfy the `DRY principle`

- `chooseAutomaton(std::vector<DeterminateFiniteAutomaton<T>>& automatonArr)` - Lets the user choose an automaton from the appropriate array type. Returns either the index of the automaton or -1 if the array is empty

- `printAutomaton(std::vector<DeterminateFiniteAutomaton<T>>& automatonArr)` - Outputs the appropriate automaton to the console or `out.txt`

- `inputFromFile(DeterminateFiniteAutomaton<T>& newAutomaton)` - Creates an automaton of the specified type by retrieving data from `in.txt`

- `printInitialState(std::vector<DeterminateFiniteAutomaton<T>>& automatonArr)` - Lets the user choose an automaton from the specified type, prints its initial state and provides the user with an option to overwrite it

- `readWord(std::vector<DeterminateFiniteAutomaton<T>>& automatonArr)` - Lets the user choose an automaton from the specified type, makes the user input a word, then checks if the automaton is able to recognize the word

- `executeAutomatonOpeartions(DeterminateFiniteAutomaton<T>& newAutomaton, std::vector<DeterminateFiniteAutomaton<T>>& automatonArr, DFAOperations operation)` - Creates a new automaton from a specified type by using the `| & ^` operators

- `createAutomatonAndPush(CreationOptions method, std::vector<DeterminateFiniteAutomaton<T>>& automatonArr)` - creates a new automaton using the specified method, then pushes it to the menu array.
