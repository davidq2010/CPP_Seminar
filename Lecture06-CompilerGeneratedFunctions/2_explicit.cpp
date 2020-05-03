////////////////////////////////////////////////////////////////////////////////
/// Explicit
///
/// - The keyword 'explicit' is used to prevent implicit type conversion in C++.
/// - Attach to a constructor which takes in a single argument, i.e., 
///   conversion operators.
/// - Implicit type conversion of classes is allowed to perform a single 
///   implicit step.
/// - Best practice - think about type conversion by design.
///   - Most commonly, disallow it.
///   - Rarely, e.g., mathematics contexts, allow it.
/// - Examples.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;

///////////////////////////////////////
/// @brief Example convertable from
///        integers.
///////////////////////////////////////
class A {
  public:
    A() = default;
    A(int _i) : m_i{_i} {}

    int getI() const {return m_i;}

  private:
    int m_i;
};

///////////////////////////////////////
/// @brief Example convertable from
///        As.
///////////////////////////////////////
class B {
  public:
    B() = default;
    /*explicit*/ B(A _a) : m_a{_a} {}

    int getI() const {return m_a.getI();}

  private:
    A m_a;
};

///////////////////////////////////////
/// @brief Example not-convertable.
///////////////////////////////////////
class C {
  public:
    C() = default;
    explicit C(A _a) : m_a{_a} {} // explicit disallows any conversion.

    int getI() const {return m_a.getI();}

  private:
    A m_a;
};

void foo1(A a) {
  cout << a.getI() << endl;
}

void foo2(B b) {
  cout << b.getI() << endl;
}

void foo3(C c) {
  cout << c.getI() << endl;
}

int
main() {
  A a{5};
  B b{a};
  C c{a};

  foo1(10); // Implicit conversion from 10 -> A
  foo1(a);

  // foo2(10); // Error cannot convert 10 -> A -> B (can't do 2 steps)
  foo2(a);     // Implicit conversion from A -> B
  foo2(b);

  // foo3(10); // Error cannot convert 10 -> A -> C (can't do 2 steps)
  // foo3(a);  // Error cannot convert A -> C (explicit!)
  foo3(C(a));  // Can manually do it, i.e., explicitely
  foo3(c);
}