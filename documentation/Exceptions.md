# Exception classes

These are classes that extend `std::exception` and are used for handling errors. They have a similar structure, but are called in different scenarios.

## AutomatonStateException

This exception is used by [DFA](DFA.md) to throw an exception when invalid state data was inputted from the user or a file.

- `MyStr state` - The name of the state, which caused this exception.
- `MyStr message()` - Returns the name of the state to the console, followed by: `" is not a valid state name"`

## NotEnoughAutomatons

This exception is used by the [Menu](Menu.md) class to throw an exception when the user tries to `intersect` or `unify` 2 Automatons, but there are no 2 automatons of the same type created yet.

- `MyStr status` - The reason for throwing this exception
- `MyStr message()` - Returns the status message.
