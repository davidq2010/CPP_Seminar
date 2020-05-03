////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief Simple Generic Array and sorting function.
///
/// This exercise demonstrates various uses of template class/functions and
/// template specialization.
///
/// Reflection:
///   - Templates are cool!
///   - I relearned some important rules of partial specialization.
////////////////////////////////////////////////////////////////////////////////

#include <algorithm>

////////////////////////////////////////////////////////////////////////////////
/// @brief Generic Array
////////////////////////////////////////////////////////////////////////////////
template<typename T, size_t D>
class generic_array {
  private:
    T arr[D]; ///< Generic array of size D
  public:
    generic_array() {
      for(size_t i = 0; i < D; ++i)
        arr[i] = T();
    }

    // Accessors
          T& operator[](size_t _i)       { return arr[_i]; }
    const T& operator[](size_t _i) const { return arr[_i]; }
};

////////////////////////////////////////////////////////////////////////////////
/// @brief Specialized array
////////////////////////////////////////////////////////////////////////////////
template<size_t D>
class generic_array<char, D> {
  private:
    std::string arr; ///< Generic array of size D
  public:
    generic_array() : arr(D, ' ') {}

    // Accessors
          char& operator[](size_t _i)       { return arr[_i]; }
    const char& operator[](size_t _i) const { return arr[_i]; }
};

////////////////////////////////////////////////////////////////////////////////
/// @brief Generic array sort
template<typename T, size_t D>
void
generic_array_sort(generic_array<T, D>& _arr) {
  std::sort(&_arr[0], &_arr[D]);
}