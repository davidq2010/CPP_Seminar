////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief Utilities for power of two sizes.
////////////////////////////////////////////////////////////////////////////////

#include <array>

////////////////////////////////////////////////////////////////////////////////
/// @brief Compute power of two.
/// @param _n Power
/// @return 2^(_n)
constexpr size_t pow_two(size_t _n) {
  size_t x = 1;
  for(size_t i = 0; i < _n; ++i)
    x *= 2;
  return x;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Array of size of a power of two.
/// @tparam T Type.
/// @tparam N power of two.
////////////////////////////////////////////////////////////////////////////////
template<typename T, size_t N>
using pow_two_array = std::array<T, pow_two(N)>;

////////////////////////////////////////////////////////////////////////////////
/// @brief Add two arrays of the same size.
/// @tparam T Type 1.
/// @tparam U Type 2.
/// @tparam N Size
template<typename T, typename U, size_t N>
auto add(const std::array<T, N>& _arr1,
         const std::array<U, N>& _arr2) -> std::array<decltype(_arr1[0] + _arr2[0]), N> {
  using ST = decltype(_arr1[0] + _arr2[0]);
  std::array<ST, N> sum;
  for(size_t i = 0; i < _arr1.size(); ++i)
    sum[i] = _arr1[i] + _arr2[i];
  return sum;
}