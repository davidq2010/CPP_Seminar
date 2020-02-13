#include <iostream>

using namespace std;

// AKA a move
void strategic_shallow_copy(int*& _arr) {
  int* y = _arr;
  _arr = nullptr;
  return y;
}

int main(int argc, char** argv) {

  // Refs had to refer to a named variable. Other option was to make a const
  // reference.
  const int& a = i + 5;

  // r-value reference - reference to a temporary object (an r-value).
  int&& b = i + 5;
  ++b;

  // l-value reference - anything with a name; can appear on the lefthand side
  // of an assignment.
  // Question: What is the type of b?
  // Answer: l-value to an r-value reference; l-values have names, and b is the
  // name for this r-value reference.

  // A move is a strategic shallow copy.
  // Copy is a "deep" copy.
  // We can have Move Constructors like how we can have Copy Constructors.
  int [] arr = [1, 2, 3, 4];
  int* strategic_shallow_copy = strategic_shallow_copy(arr);

  // r-values are candidates for moving.
}

// This would be bad design...but we kinda need them all :(
// So we just have one method bar. And the compiler does some optimizing stuff.
// For example, there are cases where we consider pass by value bc the compiler
// *might* use some moves for us behind the scenes.
void bar_value(vector<double> _vec) {}
void bar_const_ref(const vector<double>& _vec) {}
void bar_ref(vector<double>& _vec) {}
void bar_rvalue_ref(vector<double>&& _vec) {}

string s = "hello";
bar_value(s);
bar_const_ref(s);
bar_const_ref(std::move(s)); // std::move() forces a move

// move might be implemented as follows:
template<typename T>
decltype(auto) move(T&& _t) {
  using R = std::remove_reference<T>&&;
  // move is a cast to an r-value reference.
  return static_cast<R>(_t);
}

vector<int> generate(int n) {
  vector<int> vec(n);
  for (int i = 0; i < n; ++i)
    n.emplace_back(i);
  return vec;
}

// We could have 2 copies here: one to a temp object from generate(100) and
// another into vec variable.
vector<int> vec = generate(100);

// RVO Perspective
void generate(int n, vector<int>& _invisible) {
  for (int i = 0; i < n; ++i)
    _invisible.emplace_back(i);
}

// Applicable example w/class. Use i(move(_i)) to force invocation of move
// constructor

class Example {
  private:
    int i;
};

Example::Example(int _i) : i{std::move(_i)} {};
