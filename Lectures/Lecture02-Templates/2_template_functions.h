////////////////////////////////////////////////////////////////////////////////
/// Template function example
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////
/// @brief Example
template<typename T>
T
my_max(const T& _a, const T& _b) {
  return _a < _b ? _b : _a;
}
