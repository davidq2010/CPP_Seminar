#include <iostream>
using namespace std;

#include "2_template_functions.h"

////////////////////////////////////////////////////////////////////////////////
/// Template Functions
///
/// 1. Template classes are blueprints for a functions. When a template class is 
///    instantiated, the C++ compiler copies the blueprint into an actual 
///    function.
/// 2. Template class parameters can be explicitely stated when instantiating,
///    but more conveniently the compiler can infer the correct types.
/// 4. See the accompanying .h file for an example and the main method below for
///    its instantiations and uses.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief Main method
int
main() {
  cout << my_max(3, 5) << endl;           /// Implicite usecase -- compiler  
                                          /// determines the type.
  cout << my_max<float>(5.6f, 3) << endl; /// Explicit instantiation 
  // cout << my_max(3, 5.6) << endl;      /// Error! Can't deduce the type.
}