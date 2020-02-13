////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief Introduction to Modern C++'s view of values and references.
///
/// Outline
/// - lvalue, rvalue, lvalue-reference, rvalue-reference
///   - Heuristics for identification
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std; // Only do global using statements in cpp source files, not 
                     // header source files (.h)

////////////////////////////////////////////////////////////////////////////////
/// lvalue, rvalue, lvalue-reference, rvalue-reference
///
/// 1. lvalue - any value that can appear on the left-hand-side of an assignment
///             '='.
/// 2. rvalue - any value that can only appear on the right-hand-side of an 
///             assignment. In other words you cannot take its address.
/// 3. lvalue-reference - A reference to an lvalue. Denoted with &.
/// 4. rvalue-reference - A "reference" to an rvalue. Denoted with &&.
/// 5. Rvalues support "moving" and move semantics. This will be explained in 
///    the next program.
/// 6. To help identify
///   a. lvalues are typically variables with a name, i.e., you can take its 
///      address.
///   b. rvalues are anything else, e.g., the result of an expression.
////////////////////////////////////////////////////////////////////////////////

int
main(int _argc, char** _argv) {
  int i = 0; // lvalue, &i is supported.
  int j = 5;
  
  int a = i + j; // i+j is an rvalue, while k is an lvalue
  // int& b = &(i+j); // Would be an error!
  int&& c = i + j; // i+j is an r-value, b is an lvalue to an rvalue-reference.

  cout << "Rvalue references" << endl;
  cout << "\tAddresses: &c: " << &c << endl; // Proof c is an lvalue, you can 
                                             // take its address
}