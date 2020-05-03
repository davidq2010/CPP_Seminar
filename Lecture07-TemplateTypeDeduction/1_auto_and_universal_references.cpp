////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief Brief overview of special member functions, explicit, and noexcept.
///
/// Outline
///  - auto
///  - Universal references and reference collapsing
///  - Template type deduction (and auto type deduction)
///  - How to avoid overloading on universal references
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
/// Auto
///
/// - Auto can be used as the type of a variable, parameter to a function, or as
///   the return type to a function (C++14). C++ will infer the type based on
///   the context.
/// - You can also use auto& or auto* for reference or pointers, and even 
///   auto&&. You can use const and volatile as qualifiers as well. However, as 
///   we will see below, auto&& is not always an rvalue reference.
/// - Best practices - prefer auto for complex type names, but avoid using it 
///   for easy to infer types.
/// - A few cases where auto performs unexpectedly or fails.
/// - Examples below.
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////
/// @brief Play around with auto.
void
play_with_auto() {
  auto i = 0;         // int
  const auto& j = i;  // const int&
  auto* const k = &i; // Const pointer to an int (int* const)
  auto&& n = i;       // int&
  auto&& m = 25;      // int&&
  
  i += 78;
  cout << "I: " << i << "\tJ: " << j << "\tK: " << *k 
    << "\tN: " << n << "\tM: " << m << endl;
}

////////////////////////////////////////////////////////////////////////////////
/// Universal References
///
/// - auto&& and template types with && are universal references. A universal
///   reference infers the correct reference type for lvalues or rvalues.
/// - Use std::forward to retain the correct reference type information. This is
///   synonymous to std::move. However, std::move is an unconditional cast to an
///   rvalue. With perfect forwarding (std::forward) of a universal reference,
///   it is conditionally cast to an rvalue retaining the original lvalue or 
///   rvalue information.
/// - Reference collapsing supports type deduction when passing references into
///   deduced contexts. Consider auto&& or T&&:
///   - If the expression passed into the parameter or the deduded type contains
///     an lvalue, then it will collapse to an lvalue-reference.
///   - Otherwise, it will collapse to an rvalue-reference.
///   - Essentially:
///     - int& - lvalue reference
///     - int&& - rvalue reference
///     - int& && - lvalue reference (collapsed to int&)
///     - int& & - Illegal! But if from deduced context - lvalue reference
///     - int&& && - rvalue reference (collapsed to int&&)
/// - Examples of universal references.
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////
/// @brief Examples of universal 
///        references.
template<typename T>
void
foo(T&& t) { // Universal reference! Any other case will not be universal
  auto&& x = t; // Universal reference! Any other case of auto will not be 
                // universal
  cout << ::to_string(std::forward<T>(t)) << endl; // Passes as either lvalue or rvalue!
  cout << ::to_string(std::forward<T>(x)) << endl; // Passes as either lvalue or rvalue!
}

void
play_with_universal() {
  int x = 0;
  int& y = x;
  int&& z = 5;
  foo(x);
  foo(y);
  foo(z);
}

///////////////////////////////////////
/// @brief Main driver.
/// @return Success/fail
int
main() {
  play_with_auto();
  play_with_universal();
}