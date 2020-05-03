////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief Practice writing lambda expressions.
////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
/// @brief Main driver
/// @return Success/failure
int
main() {
  constexpr size_t sz = 1000000;
  vector<double> vals(sz);

  // Random numbers
  default_random_engine rng;
  uniform_real_distribution<double> dist(0.0, 1.0);
  generate_n(vals.begin(), sz, [&dist,&rng](){return dist(rng);});

  // Copy if x < 0.3 or x > 0.6
  vector<double> vals_if;
  copy_if(vals.begin(), vals.end(), back_inserter(vals_if),
    [](auto& a){return a < 0.3 || a > 0.6;}
  );

  // Transform by rounding
  vector<int> vals_i(vals_if.size());
  transform(vals_if.begin(), vals_if.end(), vals_i.begin(),
    [](auto& a){return (int)round(a);}
  );

  // Sort
  sort(vals_i.begin(), vals_i.end(),
    [](auto& a, auto& b){return b < a;}
  );

  // Counts
  cout << "1s: "
    << count_if(vals_i.begin(), vals_i.end(), [](auto& a){return a == 1;})
    << endl;
  cout << "0s: "
    << count_if(vals_i.begin(), vals_i.end(), [](auto& a){return a == 0;})
    << endl;
}