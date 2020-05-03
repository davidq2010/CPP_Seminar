////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief Testing of variadic assertion.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "variadic_assert.h"

////////////////////////////////////////////////////////////////////////////////
/// @brief Main driver
/// @return Success/failure
int
main() {
  std::cout << "C True Case" << std::endl;
  c::variadic_assert(3, "Check 1", true, "Check 2", true, "Check 3", true);
  std::cout << "C False Case" << std::endl;
  c::variadic_assert(3, "Check 1", true, "Check 2", false, "Check 3", true);

  std::cout << "CPP True Case" << std::endl;
  cpp::variadic_assert("Check 1", true, "Check 2", true, "Check 3", true);
  std::cout << "CPP False Case" << std::endl;
  cpp::variadic_assert("Check 1", true, "Check 2", false, "Check 3", true);
  // std::cout << "CPP Bad Case" << std::endl;
  // cpp::variadic_assert("Check 1", true, "Check 2", false, "Check 3");
}