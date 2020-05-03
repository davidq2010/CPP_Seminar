////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief Test of the logged map class.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "pow_two.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////
/// @brief Main driver.
/// @return Success/fail.
int
main() {
  cout << "Check 2^10: " << pow_two(10) << endl;

  constexpr size_t four = 4ul;
  constexpr size_t pt4 = pow_two(4);
  pow_two_array<double, four> arr1;
  for(size_t i = 0; i < pt4; ++i)
    arr1[i] = i;

  cout << "Array1 intiialized:";
  for(auto& x : arr1)
    cout << " " << x;
  cout << endl;

  pow_two_array<float, four> arr2;
  for(size_t i = 0; i < pt4; ++i)
    arr2[i] = pt4 - i;

  cout << "Array2 intiialized:";
  for(auto& x : arr2)
    cout << " " << x;
  cout << endl;

  auto sum = add(arr1, arr2);

  cout << "Sum:";
  for(auto& x : sum)
    cout << " " << x;
  cout << endl;
}