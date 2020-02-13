////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief A small introduction to Modern C++'s move semantics.
///
/// Outline
/// - Copy vs move
/// - Using std::move
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
using namespace std; // Only do global using statements in cpp source files, not 
                     // header source files (.h)

////////////////////////////////////////////////////////////////////////////////
/// Move semantics
///
/// 1. Copying refers to creating a new location in memory with an identical 
///    value as the other variable, whilst maintaining the value of the old 
///    variable. Typically this is a "deep" copy, whose purpose is to duplicate
///    memory.
/// 2. Moving refers to a creating a new location in memory with an identical 
///    value as the other variable, whilst destroying the old variable's value.
///    This is to transfer ownership of memory, i.e., moving it to a new owner.
///    Can be thought of as a "strategic shallow copy".
///   a. When using other's code, do not assume moving is available, cheap, or 
///      used.
/// 3. rvalue-references are the "glue" in modern C++ allowing moving. It is 
///    important to know that rvalues are only candidates for moving, and 
///    sometimes a copy will still be generated.
/// 4. std::move(x) is a method that will convert variables (e.g.
///    an lvalue-to-an-rvalue-reference) to an rvalue-reference, such that they
///    will be considered candidates for moving.
///   a. std::move is literally a cast. It has 0 cost.
/// 5. You can operator overload with rvalue-references and support move 
///    construction in user-defined classes.
///   a. Still prefer pass by reference and const reference first (used most of 
///     the time).
///   b. Can provide pass by rvalue references (used some of the time).
///   c. If an interface is unwieldy with too many overloads (poor software 
///      engineering), consider pass by value. A pass by value can be the cost
///      of two move constructions, compared with a copy.
/// 6. Still trust return-value-optimization instead of moving data out of 
///    functions.
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////
/// Example of writing and implementing
/// a move contructor.

struct A {
  int a;

  explicit A(int _a) : a(_a) {     // Constructor
    cout << "\tConstructor" << endl;
  }
  A(const A& _a) : a(_a.a) {       // Copy construction
    cout << "\tCopy constructor" << endl;
  }
  A(A&& _a) : a(std::move(_a.a)) { // Move construction - Note that std::move
                                   // casts the lvalue to an rvalue 
    cout << "\tMove constructor" << endl;
  }

  vector<int> move_out_of_function() { // This may be tempting but do not do
    vector<int> arr{a};                // this often
    return std::move(arr);
  }

  vector<int> candidate_for_rvo() { // Prefer this version! Any decent compiler
    vector<int> arr{a};             // will perform return value optimization.
    return arr;
  }

  // RVO will convert a call the function to:
  //
  // void with_rvo(vector<int>& arr) {
  //   arr.emplace_back(a);
  // }
  //
  // and a call of the method like
  // vector<int> arr = my_A.candidate_for_rvo();
  // to:
  // 
  // vector<int> arr;
  // with_rva(arr);
  //
  // automatically. This compiler optimization provides an immense boost in 
  // efficiency.
};

int 
main() {

  cout << "Move semantics" << endl;

  A a{5};
  vector<int> arr = a.candidate_for_rvo();

  A b{a};            // Copy construction
  
  A c{std::move(b)}; // Move construction (typically invalidates moved object)
}