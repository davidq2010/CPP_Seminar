#include <iostream>
using namespace std;

#include "3_template_specialization.h"

////////////////////////////////////////////////////////////////////////////////
/// Template Specializations
///
/// 1. Sometimes there is not a one-size-fits-all blueprint, e.g., Vector cross
///    product in 2D returns a scalar, but in 3D returns a vector.
/// 2. Template specialization allowes for an alternate definition of a template
///    given a specific (or subset of) type.
///   a. Class template specializations must be entirely rewritten.
/// 3. C++ is powerful enough to specialize only some of the template parameters
///    which is called partial template specialization.
///   a. Only can be done on class templates.
/// 4. The compiler determines the specialization with the closest fit (yes
///    you can specify more than one specialization).
/// 5. See the accompanying .h file for an example and the main method below for
///    its instantiations and uses.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief Main method
int
main() {
  /// Exmaple 1
  do_something(4.5); /// General template
  do_something(4);   /// Specialized template

  /// Example 2
  Vector<double, 3> v1{3, 4, 5};  /// General template
  Vector<int, 2>    v2{4, 5};     /// Partially specialized template

}