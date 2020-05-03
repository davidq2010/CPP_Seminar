////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief Brief overview of polymorphism in C++
///
/// Outline
///  - Rules of polymorphism and dynamic binding
///  - Purevirtual, override, final
///  - Virtual destructors
///  - Other practices
///  - Polymorphism example
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
/// Rules of polymorphism and dynamic binding
///
/// 1) In C++ runtime polymorphism will occur when:
///   - Using a pointer/reference to a base object to invoke a virtual method, 
///     i.e., required (1) pointer to base and (2) invokation of virtual method.
///     Yes, the method must be labeled virtual.
/// 2) Dynamic binding is the process by which an object is "linked" to its
///    appropriate virtual table at the time of constructing a polymorphic 
///    object.
///   - Essentially, there is an invisible pointer data member of virtual base
///     classes called a "vtable" that points to the appropriate virtual table
///     of method calls for the actual type (derived class) of the pointer.
///   - During virtual method invocation, first a lookup of the vtable occurs,
///     and then a lookup of the appropriate method to invoke of its actual, 
///     derived type occurs. So it costs 2 indirections for a virtual method
///     invocation.
/// 3) Contrast to Java
///   - Polymorphism is "on" by default in Java, where as polymorphism is "off"
///     by default in C++.
///   - Virtual is almost identical to the abstract keyword in Java.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// Purevirtual, override, final
///
/// 1) Denote a pure virtual (meaning there is no default implementation) method
///    by noting "= 0" after the method declaration. This makes the whole class
///    abstract meaning that you cannot invoke "new" using this base class. In
///    another interpretation, it is for classes that only work polymorphically,
///    not as stand alone objects.
/// 2) Whenever you override a virtual method demarcate this method with the
///    override keyword. The compiler will then double check that you actually
///    override the correct signature of a virtual method. Override is a C++11
///    keyword.
/// 3) Whenever you want to prevent inheritance of a class, note it with the
///    keyword final. Whenever you want to prevent a method from being 
///    overridden, denote it with the keyword final. Final is a C++11 keyword.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// Virtual destructors
///
/// 1) Whenever a base class is to be used polymorphically label the destructor
///    as virtual. If a base class is not to be used polymorphically then do
///    not label it virtual.
/// 2) When a polymorphic object goes out of scope (i.e., is deleted) then
///    a virtual lookup of the correct destructor will only occur when the 
///    base's destructor is labeled as virtual. Otherwise only the base class 
///    destructor is invoked, i.e., there will be leak of the memory taken by
///    the derived object's members.
/// 3) General rules - construction means to initialize all my classes data
///    members not my base's or derived classes members. Same for destruction.
///    Additionally, the order of contruction is from the base to the derived,
///    whereas the order of construction is from the derived to the base.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// Other practices
///
/// 1) Do not invoke virtual methods in the constructor or destructor of a base 
///    class.
/// 2) Understand namehiding vs "overloading" in inheritance. Can include base 
///    member functions explicitely with using::func_name;
/// 3) Use the NVI (non-virtual interface) idiom to allow private virtual method
///    to only perform work that is different from other derived classed.
/// 4) Polymorphism is not for free. Seek other alternatives when possible,
///    e.g., NVI with function pointers or Strategy design pattern.
/// 5) Never redefine an inherited non-virtual function.
/// 6) Never redefine default parameters of virtual functions.
/// 7) "Has-A" relationships, i.e., composition, should be preferred to private
///    inheritance. Private inheritance means "is implemented in terms of", 
///    i.e., common implementation, not common interface.
/// 8) Know about the Empty-Base-Optimization (EBO). It "Squashes" base classes
///    with no member variables.
/// 9) Avoid multiple inheritance, though know the rules are defined. If you
///    need to, then know when to use a virtual base class to avoid memory 
///    duplication.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// Polymorphism Example
///
/// A <- B
////////////////////////////////////////////////////////////////////////////////

class A {
  public:
    A() { // Called first in construction
      cout << "A's constructor." << endl;
    }
    virtual ~A() { // Polymorphic bases should always have a virtual destructor
                   // Called last in destruction chain
      cout << "A's destructor." << endl;
    }

    virtual void non_pure_virtual() {
      cout << "A's non_pure." << endl;
    }

    virtual void pure_virtual() = 0;

    void non_virtual() {
      cout << "A's non_virtual." << endl;
    }

    virtual void final_() final { // In reality it shouldn't be virtual, but this 
                                 // is just for the example.
      cout << "A's final." << endl;
    }
};

class B final : public A { // No more classes can inherit
  public:
    B() {
      cout << "B's constructor." << endl;
    }
    ~B() {
      cout << "B's destructor." << endl;
    }

    void non_pure_virtual() override { // Demarcate it override and compiler 
                                       // double checks your work.
      cout << "B's non_pure override." << endl;
    }

    void pure_virtual() override {
      cout << "B's pure override." << endl;
    }

    // void non_virtual() { // Do not add this! Non-virtual methods are not 
    //                      // "overriden", they are entirely redefined!
    //   cout << "B's non_virtual." << endl;
    // }

    // void final_() override { // Cannot override, it is final in A. Error.
    //   cout << "B's final." << endl;
    // }
};

///////////////////////////////////////
/// @brief Main driver.
/// @return Success/fail.
int
main() {
  // Example 1 object of type A, and all method calls.
  // A* just_a = new A(); // Error because of the pure virtual method.
  // // Can get the rest to work without A being abstract or with defining A's pure 
  // // virtual.
  // just_a->non_pure_virtual();
  // just_a->pure_virtual();
  // just_a->non_virtual();
  // just_a->final_();
  // delete just_a;

  // Example 2 object of type B, and all method calls.
  B* just_b = new B();
  just_b->non_pure_virtual();
  just_b->pure_virtual();
  just_b->non_virtual();
  just_b->final_();
  delete just_b;

  // Example 3 object of declared type A and actual type B (polymorphic), and
  // all method calls.
  A* poly_b = new B();
  poly_b->non_pure_virtual();
  poly_b->pure_virtual();
  poly_b->non_virtual();
  poly_b->final_();
  delete poly_b;
}