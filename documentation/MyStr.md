# MyStr Class

Utility class, designed to mimic the functionality of the `std::string` class

## Data members

- `char* buff` - Array of characters, representing the whole string

## Methods

- `Constructors/Destructor` - All the necessary constructors required to satisfy the `Rule of the Big Five`

- `Redefined operators` - Provide various operator functionality

  - `operator+(const MyStr&)` - Concatenate this string with another string of type MyStr and return a new object of type MyStr
  - `operator+(char)` - Concatenate a `char` to the end of `this` and return the new string
  - `operator[](unsigned i) const` - Return the value of the char at index `i`
  - `operator[](unsigned i)` - Return the address of the chara at index `i`, allowing it to be changed
  - `operator==(const MyStr& rhs)` - Compares the 2 string and returns true if their values are identical

- `ins(std::ostream& out)` - Output the address of the `buff` pointer to the given output stream
- `ext(std::istream& in)` - Input data to `buff` using the given input stream object

## Redefined input/output operators

- `std::ostream& operator<<(std::ostream& lhs, const MyStr& rhs)` - Calls `rhs.ins(lhs)`, making output available for all `ostream` objects
- `std::istream& operator>>(std::istream& lhs, MyStr& rhs)` - Calls `rhs.ext(lhs)`, making input available for all `istream` objects
