#include <iostream>
#include <stdexcept>

////////////////////////////////////////////////////////////////////////////////
/// Template specialization examples
///
/// 1. Example of class specialization.
/// 2. Example of function partial specialization.
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////
/// @brief Example 1 - function 
///        specialization
template<typename T>
void do_something(T _t) {
  std::cout << "General function template" << std::endl;
}

template<>
void do_something<int>(int _t) {
  std::cout << "Specialized function template" << std::endl;
}

///////////////////////////////////////
/// @brief Example 1 - Vector dimension
///        partial specialization.
template<typename T, size_t D>
class Vector {
  T vec[D];

public:
  // Note there are some other mechanisms for this, e.g., compile time pass of
  // array type (using 'cont T(&_vec)[D]') as a parameter.
  Vector(std::initializer_list<T> _vec) {
    if(_vec.size() > D)
      throw std::length_error("Initializer list has incorrect length.");
    size_t i = 0;
    for(auto&& e : _vec)
      vec[i++] = std::move(e);
    std::cout << "General Vector template" << std::endl;
  }

  // Etc
};

template<typename T>
class Vector<T, 2> {
  double x, y;

public:
  Vector(double _x, double _y) : x(_x), y(_y) {
    std::cout << "Partially specialized Vector template" << endl;
  }
};

