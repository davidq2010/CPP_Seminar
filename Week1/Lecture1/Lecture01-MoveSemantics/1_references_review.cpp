////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief A small review of Classical C++ references.
///
/// Outline
/// - History of C++ development
/// - References vs Pointers
///   - Main uses of references/pointers
////////////////////////////////////////////////////////////////////////////////

#include <iomanip>
#include <iostream>
#include <vector>
using namespace std; // Only do global using statements in cpp source files, not 
                     // header source files (.h)

////////////////////////////////////////////////////////////////////////////////
/// History of C++ development
///
/// 1. C was originally developed by Dennis Ritchie and Ken Thompson in 1972 to
///    support the Unix operating system.
/// 2. C++ was invented by Bjarne Stroustrup in 1979, as "C with Classes"
/// 3. C++ was originally standardized in 1998, with minor revisions in 2003.
/// 4. Modern C++ refers to the modern standard of the language inseminated in
///    2011. This includes 2014 (minor revision), 2017 and soon 2020.
/// 5. Each version supports the last, as in you can compile C code in modern 
///    C++.
/// 5. Generally, the feature sets are unique enough and the idioms in each are
///    specialized. So consider them separate languages and practices.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// References and pointers
///
/// 1. References - a renaming of a variable or other piece of data.
/// 2. Pointer - a variable which holds a memory address as its value, i.e., 
///              they provide an indirect reference to a piece of data.
/// 3. Use cases
///   a. References allow for cheap passing of variables to avoid unnecessary 
///      copying.
///   b. While pointers can also be used for that purpose, this should be
///      avoided as they add indirection. However, pointers are used for two
///      separate reasons: (1) they allow memory to live longer than its 
///      original scope and (2) they directly support run-time polymorphism.
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////
/// Example of 1 and 2.

void 
reference_examples() {
  int i = 0;
  int& j = i; // j is now another name for i.
  ++j;        // Increments both j and i.
  cout << "Reference example:" << endl;
  cout << "\tAddresses: &i: " << setw(20) << &i 
    << setw(20) << "\t&j: " << &j << endl;
  cout << "\t   Values:  i: " << setw(20) <<  i 
    << setw(20) << "\t j: " <<  j << endl;

  int* k = &j; // k is a pointer to both i and j.
  ++(*k);      // Alter the value of all three
  cout << "Pointer example:" << endl;
  cout << "\tAddresses: &k: " << setw(20) << &k << endl;
  cout << "\t   Values:  k: " << setw(20) <<  k << endl;

  // Notice the following:
  // 1. &i, &j are identical, i.e., it is a renaming.
  // 2. k stores the address of i/j, it is an indirection to this memory. 
}

///////////////////////////////////////
/// Example of 3.a.
void 
by_value(vector<int> _arr) {
  _arr.resize(10);
  cout << "\t  Inside by_value:    &_arr: " << setw(20) << &_arr
    << "\tsize: " << _arr.size() << endl;
}

void 
by_reference(vector<int>& _arr) {
  _arr.resize(10);
  cout << "\t  Inside by_reference:&_arr: " << setw(20) << &_arr
    << "\tsize: " << _arr.size() << endl;
}

void 
by_pointer(vector<int>* _arr) {
  _arr->resize(20);
  cout << "\t  Inside by_pointer:  &_arr: " << setw(20) << &_arr
    << "\tsize: " << _arr->size() << endl;
}

void 
pass_by_reference_example() {
  vector<int> arr{1, 2, 3, 4, 5};
  cout << "\n\nPass-by-reference example:" << endl;
  cout << "\tOriginal address/size: &arr: " << setw(20) << &arr 
    << "\tsize: " << arr.size() << endl;
  by_value(arr); // Create a copy
  cout << "\tAfter by_value:        &arr: " << setw(20) << &arr 
    << "\tsize: " << arr.size() << endl;
  by_reference(arr); // Avoid copying and use the memory directly
  cout << "\tAfter by_reference:    &arr: " << setw(20) << &arr 
    << "\tsize: " << arr.size() << endl;
  by_pointer(&arr); // Avoids copying but adds an indirection (not desirable)
  cout << "\tAfter by_pointer:      &arr: " << setw(20) << &arr 
    << "\tsize: " << arr.size() << endl;

  // Notice the following:
  // 1. By value will copy, which is inefficient.
  // 2. Notice that by pointer will add indirection, which is inefficient.
  // 3. References refer to the original memory directly, allowing you to 
  //    read/write to it. This is the most efficient option.
}

///////////////////////////////////////
/// Example of 3.b.1

int*
generate_array(size_t n) {
  int* local_arr = new int[n];
  cout << "\tInside generate_array: local_arr: " << local_arr << endl;
  return local_arr; // Here local_arr goes out of scope
}

void
extend_scope_example() {
  cout << "\nExtend scope example:" << endl;
  int* arr = generate_array(10);
  cout << "\tAfter generate_array:  local_arr: " << arr << endl;
  delete arr;
}

///////////////////////////////////////
/// Example of 3.b.2

struct A {
  virtual ~A() = default;

  virtual void show() {
    cout << "\tA.show()" << endl;
  }
};

struct B : A {
  void show() override {
    cout << "\tB.show()" << endl;
  }
};

void support_polymorphism_example() {
  cout << "\nSupport polymorphism example:" << endl;
  A* a = new B();
  a->show();
  delete a;
}

///////////////////////////////////////
/// Run all examples

int 
main(int _argc, char** _argv) {
  reference_examples();
  pass_by_reference_example();
  extend_scope_example();
  support_polymorphism_example();
}