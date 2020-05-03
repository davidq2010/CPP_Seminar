////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief Brief overview of lambda expressions.
///
/// Outline
///  - STL and library use
///  - Generic function specification
///  - Lambda Expressions
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// STL and library use
///
/// - Try your best not to reinvent the wheel.
/// - In any language and real-world context, rely on standard libraries and
///   utilities for languages and when possible rely on 3rd party libraries
///   instead of writing every algorithm from scratch.
/// - Many libraries allow for generic algorithms to be specified to adapt the
///   behavior/functionality as needed for an application. A simple example is
///   sorting. In sorting, you often want to adapt the comparison function to be
///   unique for your application or data type. Sorting libraries are written
///   generically for this purpose.
///   - Other examples include:
///     - for_each, transform, find, sort
///     - Custom deletion algorithms for pointers
///     - Custom callback functions for event handling
///     - Thread specifications
///   - See C++'s algorithm library: https://en.cppreference.com/w/cpp/algorithm
/// - So, realize that the backbone of generic functionality, is functions!
///   Start thinking of functions as data (objects, yes "verbs" can be objects
///   too).
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// Generic Function Specification
///
/// - There are many ways in which C++ allows generic function specifications
/// 1. C-style function pointers - a pointer to the instruction location for the
///    function. These clearly cannot manage a changing state (data) except
///    through the use of global data. Attrocious syntax!
/// 2. Classic C++ Function objects - any object containing the function
///    operator (operator()). Optionally, function objects can contain data
///    (state) of their own. Too verbose!
/// 3. Modern C++ Lambda expressions - syntax to create function objects
///    succinctly. Amazing!
/// - Examples are below of how to create variables of them and pass them to an
///   algorithm.
/// - Other techniques, e.g., std::bind, boil down to generating a classic
///   function object. std::bind should be avoided when possible and replaced
///   with lambda functions.
////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <array>
#include <functional>
#include <iostream>

///////////////////////////////////////
/// @brief Example function
/// @param _x Element
/// @return Found
bool
find_if_mod_5(const int& _x) {
  return _x % 5 == 0;
}

///////////////////////////////////////
/// @brief Example function object
///////////////////////////////////////
class FindIfModY {
  public:
    /// @brief Constructor
    /// @param _y Divisor
    FindIfModY(int _y) : m_y{_y} {}

    /// @brief Function operator
    /// @param _x Element
    /// @return True if _x % m_y == 0, false otherwise.
    bool operator()(const int& _x) {
      return _x % m_y == 0;
    }
  private:
    int m_y;
};

///////////////////////////////////////
/// @brief Main driver
/// @return Success/fail
int
main() {
  // Example data
  std::array<int, 10> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  // Function pointer both raw and as a variable
  std::cout << "Function pointer" << std::endl;
  std::cout << "\tpass raw: "
    << std::count_if(arr.begin(), arr.end(), find_if_mod_5) << std::endl;

  auto* f1 = find_if_mod_5; // Note no parenthesis, we are not invoking the
                            // function here.
  // bool (*f1)(const int&) = find_if_mod_5; // Explicit type declaration
  std::cout << "\tdirect invocation of variable: " << f1(5) << std::endl;
  std::cout << "\tpass variable: "
    << std::count_if(arr.begin(), arr.end(), f1) << std::endl;

  // Function object both raw and as a variable
  std::cout << "\nFunction object" << std::endl;
  std::cout << "\tpass annonymous object: "
    << std::count_if(arr.begin(), arr.end(), FindIfModY(3)) << std::endl;
  auto f2 = FindIfModY(3);
  // FindIfModY f2{3}; // Explicit type declaration
  std::cout << "\tdirect invocation of variable: " << f2(9) << std::endl;
  std::cout << "\tpass variable: "
    << std::count_if(arr.begin(), arr.end(), f2) << std::endl;

  // Lamda expressions
  std::cout << "\nLambda Expression" << std::endl;
  std::cout << "\tpass as annonymous object: "
    << std::count_if(arr.begin(), arr.end(),
      [](const int& _x){return _x % 4 == 0;}
    ) << std::endl;
  auto f3 = [](const int& _x) {return _x % 4 == 0;};
  // std::function<bool (const int&)> f3 = [](const int& _x) {return _x % 4 == 0;}; // Explicit type declaration
  std::cout << "\tdirect invocation of variable: " << f3(8) << std::endl;
  std::cout << "\tpass variable: "
    << std::count_if(arr.begin(), arr.end(), f3) << std::endl;
}