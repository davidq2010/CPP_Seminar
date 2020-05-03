////////////////////////////////////////////////////////////////////////////////
/// constexpr
///
/// - constexpr is a C++11 keyword that is used to express that a computation
///   could be performed at compile-time.
///   - Confusing name and slightly confusing meaning -- not always const or
///     determined at runtime.
///   - constexpr variables are always const and can be used anywhere
///     compile-time constants are required, e.g., template arguments like
///     std::array size.
///   - constexpr functions produce compile-time constants when compile-time
///     constants are provided as parameters, but produce run-time values
///     otherwise. Naturally, there are limitations to the implementation of
///     constexpr functions.
///     - C++11 restrictions - single line with return. Ternary selection (?:)
///       and recursion are allowed!
///     - C++14 restrictions - multilines, if-else, loops. Mostly, relaxed
///       restrictions.
///     - C++17/20 relaxed further.
///     - Literal types only, but the types can be user defined. Constexpr can
///       be used on constructors and other methods of a class.
/// - Best practice: use liberally! Compile-time optimization can be extremely
///   lucrative, as you do less work during run-time. BUT, understand the
///   limitations.
/// - Examples
////////////////////////////////////////////////////////////////////////////////

#include <array>
#include <iostream>

///////////////////////////////////////
/// @brief C++03 Fibonacci
size_t
fibonacci03(size_t n) {
  if(n == 0) return 0;
  if(n <= 2) return 0;

  size_t f2 = 0;
  size_t f1 = 1;
  size_t f = 1;

  for(size_t i = 2; i < n; ++i) {
    f2 = f1;
    f1 = f;
    f = f1 + f2;
  }

  return f;
}

///////////////////////////////////////
/// @brief C++11 Fibonacci constexpr
constexpr size_t
fibonacci11(size_t n) {
  return n == 0 ? 0 : (n <= 2 ? 1 : fibonacci11(n - 1) + fibonacci11(n - 2));
}

///////////////////////////////////////
/// @brief C++14 Fibonacci constexpr
constexpr size_t
fibonacci14(size_t n) {
  if(n == 0) return 0;
  if(n <= 2) return 0;

  size_t f2 = 0;
  size_t f1 = 1;
  size_t f = 1;

  for(size_t i = 2; i < n; ++i) {
    f2 = f1;
    f1 = f;
    f = f1 + f2;
  }

  return f;
}

///////////////////////////////////////
/// @brief Main driver
/// @return Success/fail
int
main() {
  int x;
  std::cout << "Enter a run-time value (e.g. 5): ";
  std::cin >> x;

  // Classical
  std::cout << "\nClassical" << std::endl;
  const int fc_10 = fibonacci03(10);
  std::cout << "Fibonacci(10): " << fc_10 << std::endl;
  // std::array<int, fc_10> arrc; // Error
  // std::cout << "Arr size: " << arrc.size() << std::endl;

  // Modern - C++11
  std::cout << "\nModern - C++11" << std::endl;
  constexpr int fm11_10 = fibonacci11(10);
  std::cout << "Fibonacci(10): " << fm11_10 << std::endl;
  std::array<int, fm11_10> arrm11; // Works
  std::cout << "Arr size: " << arrm11.size() << std::endl;
  std::cout << "Fibonacci(x): " << fibonacci11(x) << std::endl; // Runtime

  // Modern - C++14
  std::cout << "\n Modern - C++14" << std::endl;
  constexpr int fm11_14 = fibonacci11(10);
  std::cout << "Fibonacci(10): " << fm11_14 << std::endl;
  std::array<int, fm11_14> arrm14; // Works
  std::cout << "Arr size: " << arrm14.size() << std::endl;
  std::cout << "Fibonacci(x): " << fibonacci14(x) << std::endl; // Runtime
}