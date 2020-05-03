////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief Brief overview of variadics and initializer lists.
///
/// Outline
///  - Initializer Lists
///  - Variadic Functions
///  - Variadic Templates
///  - Examples
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// Initializer Lists
///
/// - This is a random insertion into this lecture.
/// - Initializer lists allow a convenient static initialization of data
///   structures or classes.
/// - Example:
///   std::vector<int> v = {1, 2, 3};
/// - This was not allowed in classical C++, but it is a nice new feature.
/// - Not a lot of complexity here, but you can utilize this for your own
///   classes by taking a std::initializer_list<T> as a parameter to
///   constructors (technically speaking, you can use this a return from a
///   function, an argument to a function, throwing exceptions, etc.).
/// - Also as an aside, prefer initializer list syntax in construction:
///   A(int i) : m_i(i) {}
///   vs
///   A(int i) {
///     m_i = i;
///   }
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// Variadic Functions
///
/// - Since initializer lists were discussed, i.e., a static collection of an
///   arbitrary amount of things, it is worth continuing into random features
///   that are similar: variadics.
/// - C has long supported variadic functions. A perfect example is printf.
///   printf can take as many arguments as you specify -- the definition of a
///   variadic function is one in which a variable number of parameters are
///   accepted.
/// - You can write your own variadic function too, see the example below.
/// - Decription of syntactical elements (which are mostly macros):
///   - Use ... to specify the variadic arguments. This is also loosely referred
///     to as a parameter pack (though not in C).
///   - va_list is the type to capture a variadic argument list. It is
///     initialized with va_start.
///   - va_start takes a va_list and a starting argument, e.g., the count or a
///     string for formatting like printf.
///   - va_arg is a macro to give the next parameter from the variadic list. You
///     specify the va_list and the type of the argument that is expected
///     (casting occurs in the macro).
///   - Finally, when you are finished you call va_end on the argument list to
///     clean up the memory.
/// - C version of variadics cannot capture the type, be agnostic to the actual
///   number of things (you need a variable to count somehow as va_list doesn't
///   know the length), or easily allow verification (by compiler error) that
///   the wrong format or number of arguments was specified. Additionally, it
///   only can work with functions and not structs.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// Variadic Templates
///
/// - C++11 added a mechanism to fix all the issues with the C version, in the
///   form of variadic templates. A variadic template allows a variable number
///   of template arguments.
///   - Some uses:
///     - Data structures that are variadic
///     - Forwarding lists of variables to a constructor
///     - Easy error checking and type information in variadic functions
///   - Some successful examples:
///     - make_unique(), make_shared()
///     - emplacement (in place construction)
///     - tuples (variadic class structure)
/// - The syntax is to define a variadic template argument (with ...) and an
///   accompanying parameter (for functions only not class templates)
///   - Ex.
///     template<typename... T>
///     void foo(T... args)
/// - Variadic templates are defined recursively, and not to be iterated over
///   like their C counterpart.
/// - Can do many advanced things like forward the whole parameter pack. But
///   other pros include: being agnostic to the number of arguments, knowing the
///   type, allowing forwarding, and much more.
/// - See extended example below.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// Examples
///
/// - C variadic function to add integers
/// - C++ variadic template to add integral types
////////////////////////////////////////////////////////////////////////////////

#include <cstdarg>
#include <iostream>

///////////////////////////////////////
/// @brief C variadic print
/// @param _count Number of integers
/// @param ... Parameter pack
/// @return Sum of integers
long long
add_c(size_t _count, ...) {
  va_list args;
  va_start(args, _count);
  int sum = 0;
  for(size_t i = 0; i < _count; ++i)
    sum += va_arg(args, long long);
  va_end(args);
  return sum;
}

///////////////////////////////////////
/// @brief Base case of add
/// @return 0
long long
add_cpp() {
  return 0;
}

///////////////////////////////////////
/// @brief Variadic add
/// @tparam T Parameter type
/// @tparam Args Parameter pack type
/// @param _t Parameter
/// @param _args Parameter pack
template<typename... Args>
long long
add_cpp(long long _t, Args&&... _args) {
  return _t + add_cpp(std::forward<Args>(_args)...);
}

///////////////////////////////////////
/// @brief Main driver
/// @return Success/failure
int
main() {
  std::cout << "C:   " << add_c(3, 100, 200, 300) << std::endl;
  std::cout << "C++: " << add_cpp(100, 200, 300) << std::endl;
}