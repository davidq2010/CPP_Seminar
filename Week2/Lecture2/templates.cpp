// Java: 2 pass compiler
// C/C++: 1 pass compiler; forward declarations
// Ways to do Generic Programming
//   1) Runtime polymorphism; everything is an Object (Java)
//   2) Compile-time polymorphism; templates (C++)
//      a) Screw code duplication
//   3) void* and then cast (C)

class Vector {
  double x, y;

  public:
    Vector(double _x, double _x) : x(_x), y(_y) {}

    // Overload operators
};

// Smaller classes = better cache utilization

// This isn't a class yet...it's a template/blueprint for a class. The compiler
// will come along and generate its own class.
template<typename T>
class Vector {
  T x, y;

  public:
    Vector(T _x, T _y) : x(_x), y(_y) {}
};

Vector<int> v; // Only at *this point* is anything with my template compiled
               // (template instantiation).
               // Compiler fills out template with the parameter "int"
               // Makes this class:
               // class Vector<int> {
               //   int x, y;
               // };
// Jory recommends not immediately jumping to a template (unless you know
// better). Design and then redesign. Try not to pre-generalize.


// New Example: Note we can include primitive types (he believes they can be
// integral types only)
template<typename T, typename U, size_t D>
class Vector {
  T x, y;

  public:
    Vector(T _x, T _y) : x(_x), y(_y) {}
};

// Another Example: We can template functions
// Some subtle constraints:
//   1) T must be copyable
//   2) T must be comparable
template<typename T>
T max(T _t, T, _u) {
  if (_t > _u) return _t;
  return _u;
}

// Template type deduction
max(4, 6); // Instantiating template function - option 1
max<float>(5, 8); // Option 2

////////////////////////////////////////////////////////////////////////////////
// Template Specialization
// So now, if we use Vector<int>, the compiler uses this version. Otherwise, it
// uses the more general version above.
// Allows us to change how Vector is implemented.
template<>
class Vector<int> {
  // Reimplement everything
};
// In the C++ STL, the vector class has one specialization: for booleans. They
// do things at the bit level, so a vector of 8 booleans has a size of 1 byte.

////////////////////////////////////////////////////////////////////////////////
template<typename T, typename U>
void do_something(T _t, U, _u) {
  // Do something
}

// Partial specialization
template<typename T>
void do_something<int>(T _t, int _u) {
  // Do something
}
