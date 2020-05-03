////////////////////////////////////////////////////////////////////////////////
/// Template type deduction (and auto type deduction)
///
/// - Essentially three cases. Consider the following:
///
///   template<typename T>   // T - template parameter
///   void foo(ParamType t); // ParamType - how T is specified as a parameter
///
///   foo(expr);             // expr - invoked expression with its own type
///
///   - Case 1: ParamType is a pointer or reference, but not a universal 
///     reference.
///   - Case 2: ParamType is a universal reference.
///   - Case 3: ParamType is not a pointer nor a reference.
/// - Rules
///   - Case 1: If expr is a refernce, ignore the reference. After, 
///     pattern-match to determine ParamType.
///   - Case 2: If expr is an lvalue, both T and ParamType will be 
///     lvalue-references. If expr is an rvalue, apply case 1 (deduce T and 
///     ParamType will be rvalue reference).
///   - Case 3: If expr is a reference, ignore the reference. Ignore 
///     const/volatile qualifiers. Becomes a pass-by-value always.
/// - Additional oddity for passing arrays/functions. Deduced type may be the 
///   array/function type or the decayed pointer-to-array/pointer-to-function.
/// - Auto type deduction is the same as template type deduction except for one 
///   exception with initializer lists. Think of "auto" as T, how auto is 
///   written as ParamType, and the expression as what the variable is assigned.
/// - Examples.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;

///////////////////////////////////////
/// @brief Case 1: ParamType is reference
template<typename T>
void
f_reference(const T& t) {
  cout << "F_Reference" << endl;
}

///////////////////////////////////////
/// @brief Case 2: ParamType is a universal reference
template<typename T>
void
f_universal(T&& t) {
  cout << "F_Universal" << endl;
}

///////////////////////////////////////
/// @brief Case 3: ParamType is a value
template<typename T>
void
f_value(T t) {
  cout << "F_Value" << endl;
}

///////////////////////////////////////
/// @brief Main driver
/// @return Success/fail
int
main() {
  int i = 0;
  const int j = 1;
  const int& k = i;

  f_reference(i); // T: int, ParamType: const int&
  f_reference(j); // T: int, ParamType: const int&
  f_reference(k); // T: int, ParamType: const int&
  f_reference(2); // T: int, ParamType: const int&

  f_universal(i); // lvalue, T:       int&, ParamType:       int&
  f_universal(j); // lvalue, T: const int&, ParamType: const int&
  f_universal(k); // lvalue, T: const int&, ParamType: const int&
  f_universal(2); // rvalue, T:        int, ParamType:      int&&

  f_value(i); // T: int, ParamType: int
  f_value(j); // T: int, ParamType: int
  f_value(k); // T: int, ParamType: int
  f_value(2); // T: int, ParamType: int
}