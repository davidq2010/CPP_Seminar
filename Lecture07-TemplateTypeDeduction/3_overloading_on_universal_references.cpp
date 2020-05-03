////////////////////////////////////////////////////////////////////////////////
/// How to avoid overloading on universal references
///
/// - You should avoid overloading on universal references. Almost always it 
///   will dispatch to the universal reference overload instead of the other
///   overload.
/// - Alternatives:
///   - Name differently.
///   - Pass-by-const reference.
///   - Pass-by-value.
///   - Use tag-dispatch.
///   - Constrain template type, e.g., with enable_if.
/// - Examples of tag dispatch and enable_if.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>

template<typename T> void fooImpl(T&& _t, std::false_type);
void fooImpl(int _t, std::true_type);

///////////////////////////////////////
/// @brief Example tag-dispatch
///
/// First method can be a public method 
/// or function
template<typename T>
void foo(T&& _t) {
  fooImpl(std::forward<T>(_t), std::is_integral<std::remove_reference_t<T>>());
}

///////////////////////////////////////
/// @brief Generic overload
template<typename T>
void fooImpl(T&& _t, std::false_type) {
  std::cout << "Generic foo." << std::endl;
}

///////////////////////////////////////
/// @brief Integer overload
void fooImpl(int _t, std::true_type) {
  std::cout << "Integral foo." << std::endl;
}

///////////////////////////////////////
/// @brief Examples of tag dispatch
void tag_dispatch() {
  int x;
  std::string y;
  double z;
  foo(x);  // Integer version
  foo(y);  // Generic version
  foo(z);  // Generic version
  foo(32); // Integer version
}

///////////////////////////////////////
/// @brief Example of constraining type
template<typename T,
         typename U = std::enable_if_t<!std::is_integral<std::remove_reference_t<T>>::value>>
void bar(T&& _t) {
  std::cout << "Generic bar" << std::endl;
}

///////////////////////////////////////
/// @brief Integer overload
void bar(int _t) {
  std::cout << "Integral bar" << std::endl;
}

///////////////////////////////////////
/// @brief Examples of constraining
void constraining() {
  int x;
  std::string y;
  double z;
  bar(x);  // Integer version
  bar(y);  // Generic version
  bar(z);  // Generic version
  bar(32); // Integer version
}

///////////////////////////////////////
/// @brief Main driver
/// @return Success/fail
int 
main() {
  tag_dispatch();
  constraining();
}
