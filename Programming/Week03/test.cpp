////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief Simple test of classic vs modern dynamic integer arrays.
///
/// This exercise demonstrates simple use of RAII and smart pointers.
///
/// Reflection:
///   - RAII FTW!
///   - Refactoring feels good.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;

#include "classic_dyn_int_array.h"
#include "modern_dyn_int_array.h"

int
main() {
  cout << "Classic test" << endl;
  classic_dyn_int_array cdia;
  for(size_t i = 0; i < 15; ++i)
    cdia.add(i, i);
  for(size_t i = 0; i < 15; ++i)
    cdia.add(i*2, -i);
  for(size_t i = 0; i < cdia.size(); ++i)
    cout << " " << cdia[i];
  cout << endl;
  for(int i = cdia.size() - 1; i >= 0; i-=2)
   cdia.remove(i);
  for(size_t i = 0; i < cdia.size(); ++i)
    cout << " " << cdia[i];
  cout << endl;

  cout << "Modern test" << endl;
  modern_dyn_int_array mdia;
  for(size_t i = 0; i < 15; ++i)
    mdia.add(i, i);
  for(size_t i = 0; i < 15; ++i)
    mdia.add(i*2, -i);
  for(size_t i = 0; i < mdia.size(); ++i)
    cout << " " << mdia[i];
  cout << endl;
  for(int i = mdia.size() - 1; i >= 0; i-=2)
   mdia.remove(i);
  for(size_t i = 0; i < mdia.size(); ++i)
    cout << " " << mdia[i];
  cout << endl;
}