# DFA Class

This class is designed to provide the main functionality of deterministic finite automatons, such as creation, union, intersection, etc.
It's a template class, which allows the user to create automatons with different types of alphabets.

## Data members

- `unsigned stateCount` - The total number of states of an automaton

- `State* states` - An array of class [State](State.md), containing information about each state, such as its `name`, whether or not it's `final`, or a `starting state`

- `unsigned symbols` - The total number of symbols in the alphabet

- `T * alphabet` - Array of the provided `template type`, which stores the symbols/numbers the automaton can read.

- `State** trTable` - Matrix used to store the transition between states

## Methods

### Public

- `Constructors/Destructor` - All the necessary constructors required to satisfy the `Rule of the Big Five`

- `Getters/Setters` - Various getters and setters to get/manipulate values such as the state count, start state, the state array, alphabet symbols, etc.

  - `getStateCount()` - Return the total number of states
  - `getState(const MyStr& str)` - Return the state, whose name matches the given string
  - `getState(unsigned index)` - Return the adress of the state at the given index, or nullptr if it doesn't exist
  - `getSymbols()` - Returns the total count of symbols in the automaton alphabet
  - `getSymbol(unsigned i)` - Returns the symbol at the specified index or -1 if it doesnt exist
  - `getStateNum(const MyStr& str)` - Returns the `index` of the state, whose name matches the given string
  - `getArr()` - Returns a pointer to the begging of the states array
  - `getBeg()` - Returns a pointer to the initial state of the automaton
  - `setBegIO(std::istream&)` - Gets relevant `initial state` data from the input stream and calls `setBeg(const MyStr& str)` with it
  - `setBeg(const MyStr& str)` - Sets the state with the given name as an initial state
  - `setEndIO(std::istream&)` - Gets relevant `initial state` data from the input stream and calls `setEnd(const MyStr& str)` with it
  - `setEnd(const MyStr& str)` - Sets the state with the given name as a final state

- `Operators &, |, and ^` - Used to create a new automaton by by doing an `intersection`, `union`, or `reversal` operation on this and another automaton

- `inputSt(std::istream&, unsigned)` - Set state data by reading an input stream

- `inputSym(std::istream&, unsigned)` - Set symbol data by reading an input stream

- `makeTable(std::istream&)` - Creates the transition table, based on the data from an input stream

- `printTable(std::ostream&)` - Uses an `ostream` object to output the data to a console/file

- `fillArr(T*, MyStr)` - Used to fill an array of template type `T` with the data from a provided string of type `MyStr`

- `transition(State* pos, T sym)` - Checks the `trTable` for a possible transition from the given state, using the given symbol. Return nullptr if impossible

### Private

    The methods below are all meant to used ONLY by the & | ^ operators and that's why they are private

- `makeStatesFromAutomatons` - Combines the states of 2 automatons

- `setBegFromAutomatons` - Sets the start state to the 2 start states of the automatons combined

- `setEndUnion` - Used by the `| operator` to make all states, which include a final state from the initial automatons, final.

- `setEndInteresection` - Used by the `& operator` to make all states, which include a final state from the initial automatons, final.

- `makeAlphFromAutomatons` - Creates an alphabet for the new automaton by combining the alhpabets of the initial 2.

- `makeTableFromAutomatons` - Creates the transition table for the new automaton, using [Cross Product Operation](https://www.geeksforgeeks.org/cross-product-operation-in-dfa/).
