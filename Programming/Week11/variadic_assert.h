////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief Variadic assertions.
////////////////////////////////////////////////////////////////////////////////

#include <cstdarg>
#include <cstdio>

#include <iostream>

////////////////////////////////////////////////////////////////////////////////
/// @brief C function namespace.
////////////////////////////////////////////////////////////////////////////////
namespace c {

////////////////////////////////////////////////////////////////////////////////
/// @brief Assertion of multiple conditions.
/// @param _count Count of conditions to check.
///
/// All other parameters should be count number of const char*, int pairs of
/// arguments.
void
variadic_assert(size_t _count, ...) {
  va_list args;
  va_start(args, _count);
  for(size_t i = 0; i < _count; ++i) {
    const char* msg = va_arg(args, const char*);
    int cond = va_arg(args, int);
    if(!cond)
      printf("Assertion '%s' failed.\n", msg);
  }
  va_end(args);
}

}

////////////////////////////////////////////////////////////////////////////////
/// @brief CPP function namespace.
////////////////////////////////////////////////////////////////////////////////
namespace cpp {

////////////////////////////////////////////////////////////////////////////////
/// @brief Base case of no arguments for variadic assertion.
void
variadic_assert() {
  // Do nothing
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Template dependent constexpr that is always false.
/// @tparam T Parameter pack
////////////////////////////////////////////////////////////////////////////////
template <typename... T>
struct dependent_false {
  static constexpr bool value = false; ///< False
};

////////////////////////////////////////////////////////////////////////////////
/// @brief Assertion with a single parameter left, which will cause a compile
///        error.
/// @tparam T Parameter Type
/// @param _t Parameter
template<typename T>
void
variadic_assert(T&& _t) {
  static_assert(dependent_false<T>::value,
    "variadic_assert must be called with an even number of arguments.");
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Assertion of multiple conditions.
/// @tparam T Parameter pack
/// @param _msg Message
/// @param _cond Conditional
/// @param _args Parameter pack for variadic
template<typename... T>
void
variadic_assert(std::string&& _msg, bool _cond, T&&... _args) {
  if(!_cond)
    std::cerr << "Assertion '" << _msg << "' failed." << std::endl;
  variadic_assert(std::forward<T>(_args)...);
}

}