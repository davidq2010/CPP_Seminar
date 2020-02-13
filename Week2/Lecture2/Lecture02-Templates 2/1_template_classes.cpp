////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief A brief overview of C++ Template Classes/Functions.
///
/// Outline
/// - C++ is a 1-pass compiler
/// - Generic Programming
/// - Template Classes
/// - Template Functions
/// - (Partial) Template Specialization
////////////////////////////////////////////////////////////////////////////////

#include "1_template_classes.h"
using namespace std;

////////////////////////////////////////////////////////////////////////////////
/// C++ is a 1-pass compiler
///
/// 1. In a 1-pass compiler, the parsing mechanism iterates over a file one 
///    time. So all names must be "declared" before they are used. Then during
///    "linking" the compiler (linker) will look for all of the compiled 
///    "definitions" to point all function/method calls to the correct
///    definition.
/// 2. Compare this with a 2-pass compiler (e.g., Java) where the first pass
///    collects all the names, while the second pass compiles. In this case,
///    methods can be defined out of order.
/// 3. Because of C++'s history, the standards committee has not updated the 
///    parsing (possibly yet).
/// 4. When using templates, because these are only compiled on use 
///    (i.e., instantiation), the entire declaration/definition needs to be
///    available. Thus, all template mechanisms are typically found only in
///    header (.h) files.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// Generic Programming
///
/// 1. Generic programming is a programming paradigm in which the programmer
///    designs classes/functions with the absense of type. Instead thinking
///    about all possible types with available operations. In this sense, the
///    classes/functions are written in terms of "types-to-be-specified-later."
/// 2. Generic programming can be done in various ways:
///   a. Dealing with raw memory (void*) - C style.
///   b. Dealing with run-time polymorphism with large class hierarchies - Java 
///      style.
///   c. Dealing with parametric polymorphism with special syntax - C++ style.
/// 3. In C++ parametric polymorphism is primarily supported through templates,
///    which typically come in the form of classes or functions.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// Template Classes
///
/// 1. Template classes are blueprints for a class. When a template class is 
///    instantiated, the C++ compiler copies and reduces the blueprint into an
///    actual type. It only brings in the relevant parts of the blueprint, i.e.,
///    the methods you use.
///   a. Because of this, errors can get nasty listing nested instantiations
///      of template uses. See bad_template_err.txt to see a single real error 
///      causing multiple compiler erros spanning 100 lines of output.
/// 2. You can have 0 or more template parameters on a template class.
///   a. C++ even supports writing in terms of an unknown or variable amount of
///      template parameters, called variadics.
/// 3. Template class parameters must be explicitely stated when instantiating.
/// 4. See the accompanying .h file for an example and the main method below for
///    its instantiations and uses.
///   a. Note that I didn't start with the template class, you develop it as
///      needed usually. Unless I know that I will need a template mechanism, I
///      wait to evolve my code into a template form.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief Main method
int
main() {
  Vector<int, 2> vec{2, 3}; /// At this point this compiler copies the 
                            /// blueprint and makes a new class called 
                            /// "Vector<int, 2>".
}