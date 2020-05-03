////////////////////////////////////////////////////////////////////////////////
/// decltype
///
/// - C++11 built-in specifier that yields the type of a name or expression.
///   Detailed set of rules, but loosely:
///   - When used on a name the literal type T, T is given.
///   - When used on an lvalue expression of type T, T& is given.
/// - Primary usage is for function template return values whose result is
///   dependent on the template parameters. Another use is for custom
///   comparators/hash functions in data structures.
/// - For c++14, when auto is used as a return value, then template deduction
///   rules are used. However, if decltype(auto) is used as the return type
///   instead, then decltype rules are used.
///   - In c++11, when auto is used as a return value, then the trailing return
///     syntax is used to look for the type. This allows decltype to be able to
///     see the funciton parameter names.
/// - Examples
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <map>
#include <string>

///////////////////////////////////////
/// @brief Example with adding
///
/// C++11 version.
template<typename A, typename B>
auto add11(A&& a, B&& b) -> decltype(a+b) { // -> is the trailing return syntax
  std::cout << "Add11: A, B, A+B: ";
  std::cout << typeid(a).name() << ", ";
  std::cout << typeid(b).name() << ", ";
  std::cout << typeid(decltype(a+b)).name() << std::endl;
  return a+b;
}

///////////////////////////////////////
/// @brief Example with adding
///
/// C++14 version
template<typename A, typename B>
decltype(auto) add14(A&& a, B&& b) { // Note, if auto is used instead then
                                     // template deduction occurs.
  std::cout << "Add14: A, B, A+B: ";
  std::cout << typeid(a).name() << ", ";
  std::cout << typeid(b).name() << ", ";
  std::cout << typeid(decltype(a+b)).name() << std::endl;
  return a+b;
}

///////////////////////////////////////
/// @brief Example with map
///        comparator function.
void
map_test() {

  // Note this is only one way to do a custom comparator.
  auto cmp = [](const size_t a, const size_t b){ return a>b; };
  using MapType = std::map<size_t, std::string, decltype(cmp)>;

  MapType dict(cmp);
  dict[0] = "A", dict[1] = "B", dict[2] = "C";
  for(auto& p : dict) {
    std::cout << "(" << p.first << ", \"" << p.second << "\")" << std::endl;
  }
}

///////////////////////////////////////
/// @brief Main driver
/// @return Success/fail
int
main() {
  std::cout << "Add tests" << std::endl;
  auto x = add11(5, 5.5);
  auto y = add14(std::string("Hi"), 'C');
  std::cout << x << ", ";
  std::cout << y << std::endl;

  std::cout << "\tMap test" << std::endl;
  map_test();
}

