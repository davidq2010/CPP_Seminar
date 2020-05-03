////////////////////////////////////////////////////////////////////////////////
/// Template class examples
///
/// 1. The first two classes are not templates but show how you might discover
///    the need for a template class. Essentially, you do this to reduce
///    duplicate code.
/// 2. The examples refactored into a template class.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <stdexcept>

///////////////////////////////////////
/// @brief Example 1 - mathematical 
///        Vector.
class Vector2d {
  double x, y;

public:
  Vector2d(double _x, double _y) : x(_x), y(_y) { 
    std::cout << "Vector 2D with double" << std::endl;
  }

  // Etc
};

class Vector3f {
  float x, y, z;

public:
  Vector3f(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {
    std::cout << "Vector 3D with float" << std::endl;
  }

  // Etc
};

///////////////////////////////////////
/// @brief Example 2 - parameterizing
///        type and dimension.
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
    std::cout << "Vector ND with T" << std::endl;
    std::cout << "Elements: ";
    for(auto&& e : vec)
      std::cout << e << " ";
    std::cout << std::endl;
  }

  // Etc
};