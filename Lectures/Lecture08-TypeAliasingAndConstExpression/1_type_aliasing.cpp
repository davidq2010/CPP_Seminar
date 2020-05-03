////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief Brief overview of type aliasing, decltype, and constexpr.
///
/// Outline
///  - Type aliasing
///  - decltype
///  - constexpr
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// Type aliasing
///
/// - In classical C++, typedef was a very valued feature! I used it all over,
///   mainly for the reason that typenames can get long, unintuitive, and
///   obtrusive.
///   - Syntax:
///     typedef Type Alias
///   - Example:
///     typedef map<size_t, unordered_map<string, float>> WierdMap;
///   - What is worse is when you consider type aliases within a class or
///     template class, e.g., iterator. The type can become dependent on a
///     template parameter (only within a template context), and then you need
///     to also use typename in conjunction with it. More on all of this in
///     examples below.
/// - In modern C++, use alias declarations and alias templates. The syntax is
///   almost identical to assignment making it more intuitive, and it works with
///   template types.
///   - Syntax:
///     using Alias = Type;
///     or
///     template<typename T>
///     using Alias = Type<T>; // Or another use of T
///   - Example:
///     using WierdMap = map<size_t, unordered_map<string, float>>;
///     or
///     template<typename T>
///     using Array5 = array<T, 5>;
/// - Often in template environments, you need to modify the type, e.g.,
///   removing references or consts. In this case, type traits are very useful.
///   Type traits are functions or classes that reason about or transform a
///   type, e.g., remove_const.
///   - It is very common to have a class with only type aliases in it (or other
///     properties).
/// - Examples below for you to explore.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>

///////////////////////////////////////
/// @brief Class with dependent name.
///        Classical view.
///////////////////////////////////////
template<typename T>
struct MyClassical {
  // Classical C++
  typedef std::vector<T> Vec;
  // typedef Vec::iterator It; // Error
  typedef typename Vec::iterator It; // iterator is a type within vector
                                     // dependent on T, so "typename" is
                                     // required.

  Vec vec; ///< Vector of T

  /// @brief Constructor to make vector of size 10.
  MyClassical() : vec(10, T()) {}

  /// @brief Beginning iterator
  It begin() { return vec.begin(); }
  /// @brief Ending iterator
  It end() { return vec.end(); }
};

///////////////////////////////////////
/// @brief Fake template typedef
///
/// Just a hack and ugly!
///////////////////////////////////////
template<typename T> struct AliasTemplate {
  typedef MyClassical<T> type;
};

///////////////////////////////////////
/// @brief Classical C++ type aliasing
void
classical_type_aliasing() {
  std::cout << "Typedef version" << std::endl;

  // Basic typedef
  typedef int MyInt;
  MyInt x = 5;
  std::cout << "MyInt value: " << x << std::endl;

  // Use of nested typedefs
  typedef MyClassical<int> C;
  C stuff;
  // Note that here, M::it is not dependent on an unknown template parameter T,
  // so typename is not required.
  for(C::It i = stuff.begin(), j = (i+1); j != stuff.end(); ++i, ++j) {
    if(*i == *j) {
      std::cout << "Duplicates next to each other." << std::endl;
      break;
    }
  }

  // Use of a fake template typedef
  AliasTemplate<double>::type stuff2;
  std::cout << "Values:";
  for(auto& x : stuff2)
    std::cout << " " << x;
  std::cout << std::endl;
}

///////////////////////////////////////
/// @brief Class with dependent name.
///        Modern view.
///////////////////////////////////////
template<typename T>
struct MyModern {
  // Modern C++
  using Vec = std::vector<T>;
  // using It = Vec::iterator; // Error
  using It = typename Vec::iterator; // iterator is a type within vector
                                     // dependent on T, so "typename" is
                                     // required.

  Vec vec; ///< Vector of T

  /// @brief Constructor to make vector of size 10.
  MyModern() : vec(10) {}

  /// @brief Beginning iterator
  It begin() { return vec.begin(); }
  /// @brief Ending iterator
  It end() { return vec.end(); }
};

///////////////////////////////////////
/// @brief Real alias template
///////////////////////////////////////
template<typename T>
using AliasTemplate_t = MyClassical<T>;

///////////////////////////////////////
/// @brief Modern C++ type aliasing
void
modern_type_aliasing() {
  std::cout << "\nAlias version" << std::endl;

  // Basic alias declaration
  using MyInt = int;
  MyInt x = 5;
  std::cout << "MyInt value: " << x << std::endl;

  // Use of nested type aliases
  using C = MyModern<int>;
  C stuff;
  // Note that here, M::it is not dependent on an unknown template parameter T,
  // so typename is not required.
  for(C::It i = stuff.begin(), j = (i+1); j != stuff.end(); ++i, ++j) {
    if(*i == *j) {
      std::cout << "Duplicates next to each other." << std::endl;
      break;
    }
  }

  // Use of a real alias template
  AliasTemplate_t<double> stuff2;
  std::cout << "Values:";
  for(auto& x : stuff2)
    std::cout << " " << x;
  std::cout << std::endl;
}

///////////////////////////////////////
/// @brief Main driver
/// @return Success/fail
int
main() {
  classical_type_aliasing();
  modern_type_aliasing();
}