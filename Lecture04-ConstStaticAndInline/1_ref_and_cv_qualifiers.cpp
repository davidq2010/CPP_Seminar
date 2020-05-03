////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief A brief overview of CV- and ref- qualifiers, static, and inlining.
///
/// Outline
/// - Const/Volatile and Reference Qualifiers
/// - Static
/// - Inlining
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
/// Const/Volatile and Reference Qualifiers
///
/// 1) Const means constant. This implies it should not change, or identifies a
///    read only component.
/// 2) Volatile disallows compiler optimizations on a variable so that its value
///    is always read from memory, useful in multi-threaded application access
///    to things like global variables.
/// 3) Mutable allows a variable to be altered in const contexts.
/// 4) A CV- (const/volatile) or Ref- (&, &&) qualifier is to limit the use of
///    a method to the appropriate context. i.e., if an object is const then 
///    only const methods may be used, if a variable is volatile, then only
///    volatile methods may be used, etc.
/// 5) See an example accessors for all the combinations.
/// 6) Best Practices
///   - Design deliberately. Design for the immutable parts of an object 
///     explicitely.
///   - const qualify regularly.
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////
/// @brief Class example
///////////////////////////////////////
class A {
  public:
    explicit A(int _i) : m_i{_i} {}

    // Accessor options in their entirety.
    // The following precedence rules help limit
    //
    // unqualified < const
    // unqualified < volatile
    // unqualified < const volatile
    // const < const volatile
    // volatile < const volatile
    //
    // Said another way, if a variable is more qualified, then it can only
    // use the more qualified methods -- unqualified can access any, but const
    // may only access const or const volatile.
                   int&     get()                   { return m_i; }
                   int&    get_()                 & { return m_i; }
                   int&   get__()                && { return m_i; }
             const int&    getC() const             { return m_i; }
             const int&   getC_() const           & { return m_i; }
             const int&  getC__() const          && { return m_i; }
          volatile int&    getV()       volatile    { return m_i; }
          volatile int&   getV_()       volatile  & { return m_i; }
          volatile int&  getV__()       volatile && { return m_i; }
    const volatile int&   getCV() const volatile    { return m_i; }
    const volatile int&  getCV_() const volatile  & { return m_i; }
    const volatile int& getCV__() const volatile && { return m_i; }

  private:
    int m_i;

    mutable int m_j; // Mutable in const context.
};

void 
foo(const A& _a) {          // _a can only access const qualified methods, 
                            // compiler protects this.
  //cout <<     _a.get() << endl; // Error in this context
  //cout <<    _a.get_() << endl; // Error in this context
  //cout <<   _a.get__() << endl; // Error in this context
  cout <<    _a.getC() << endl;
  cout <<   _a.getC_() << endl;
  //cout <<  _a.getC__() << endl; // Error in this context
  //cout <<    _a.getV() << endl; // Error in this context
  //cout <<   _a.getV_() << endl; // Error in this context
  //cout <<  _a.getV__() << endl; // Error in this context
  cout <<   _a.getCV() << endl;
  cout <<  _a.getCV_() << endl;
  //cout << _a.getCV__() << endl; // Error in this context
}

int 
main() {
  A a{5};
  foo(a);
}