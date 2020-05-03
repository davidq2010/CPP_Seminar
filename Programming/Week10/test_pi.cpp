////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief Timing/testing of sequential and parallel algorithms to compute pi.
////////////////////////////////////////////////////////////////////////////////

#include "parallel_pi.h"
#include "sequential_pi.h"

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
using namespace std;

constexpr size_t MAX_N_THREADS = 128; ///< Num threads in experiment
constexpr size_t MAX_N = 256*256*256; ///< Max N in expeiriment 2^8*2^8*2^8 = 2^24
constexpr size_t LINE_LEN = 116;      ///< Helper for output

////////////////////////////////////////////////////////////////////////////////
/// @brief Helper to print a line of characters
/// @param _c Character to compose the line
void
print_line(char _c) {
  for(int i = 0; i < LINE_LEN; ++i)
    cout << _c;
  cout << endl;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Time a function for a specific size n
/// @param _f Function
/// @param _n Number
/// @return Average time to execute @c _f on size of @c _n
float
time_func(auto _f, size_t _n) {
  using my_clock = chrono::high_resolution_clock;
  using seconds = chrono::duration<float>;

  my_clock::time_point start = my_clock::now();
  size_t r = max(MAX_N / 256 / _n, 10ul);
  for(size_t i = 0; i < r; ++i) {
    _f();
  }

  return chrono::duration_cast<seconds>(
    my_clock::now() - start
  ).count()/(float(r));
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Main driver
/// @return Success/Failure
int
main() {
  cout << setprecision(7);
  cout << fixed;

  // Header information
  print_line('%');
  cout << "Approximating pi" << endl;
  print_line('%');
  cout << endl;

  cout << setw(8) << "n\\nt";
  cout << setw(12) << "sq";
  for(size_t nt = 1; nt <= MAX_N_THREADS; nt *= 2) {
    cout << setw(12) << nt;
  }
  cout << endl;
  print_line('-');

  // Time all possibilities
  for(size_t n = 256; n <= MAX_N; n*=2) {
    cout << setw(8) << n;
    cout << setw(12) << time_func([_n = n](){ sequential::pi(_n); }, n);
    for(size_t nt = 1; nt <= MAX_N_THREADS; nt *= 2) {
      cout << setw(12) << time_func([_n = n, _nt = nt](){ parallel::pi(_n, _nt); }, n);
    }
    cout << endl;
  }
}