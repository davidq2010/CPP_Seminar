////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief Simple test of generic array.
///
/// This exercise demonstrates various uses of template class/functions and
/// template specialization.
///
/// Reflection:
///   - Templates are cool!
///   - I relearned some important rules of partial specialization.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;

#include "generic_array.h"

////////////////////////////////////////////////////////////////////////////////
/// @brief Simple main test.
int
main() {
  // Generic
  generic_array<double, 10> arr1;
  for(size_t i = 0; i < 10; ++i)
    arr1[i] = 10 - i;
  
  generic_array_sort(arr1);

  cout << "Generic array after sort: ";
  for(size_t i = 0; i < 10; ++i)
    cout << arr1[i] << " ";
  cout << endl;
  
  // Specialization
  generic_array<char, 10> arr2;
  for(size_t i = 0; i < 10; ++i)
    arr2[i] = char(65 + 9 - i);
  generic_array_sort(arr2);

  cout << "Specialized array after sort: ";
  for(size_t i = 0; i < 10; ++i)
    cout << arr2[i] << " ";
  cout << endl;
}