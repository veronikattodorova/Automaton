# State Class

Simple class representation of a deterministic finite automaton state.

## Data Members

- `MyStr name` - The name of the state
- `bool begin` - Whether the state is the initial state of an automaton
- `bool end` - Whether the state is a final state of an automaton

## Methods

- `Constructors/Destructor` - All the necessary constructors required to satisfy the `Rule of the Big Five`
- `Setters/Getters`

  - `setBeg()` - set `this.begin` to `!this.begin`
  - `setEnd()` - set `this.end` to `!this.end`
  - `setName(MyStr name)` - change the name of the state
  - `isBeg()` - if the state is an initial state
  - `isEnd()` - if the state is a final state
  - `getName()` - return the entire `name` string
  - `getSt1()/getSt2()` - used by the [DFA](DFA.md) class when performing `union`, `intersection`, `reversal`. This is used when the state is actually made from 2 states with `,` inbetween. Returns the characters before/after `,`

- `ins(std::ostream& out)` - Output data from the `name` pointer to the given output stream
- `ext(std::istream& in)` - Input data to `name` using the given input stream object

## Redefined input/output operators

- `std::ostream& operator<<(std::ostream& lhs, const State& rhs)` - Calls `rhs.ins(lhs)`, making output available for all `ostream` objects
- `std::istream& operator>>(std::istream& lhs, State& rhs)` - Calls `rhs.ext(lhs)`, making input available for all `istream` objects
