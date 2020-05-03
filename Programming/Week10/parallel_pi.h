////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief Parallel monte carlo approximation of pi.
////////////////////////////////////////////////////////////////////////////////

#include <atomic>
#include <future>
#include <random>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
/// @brief Collection of parallel algorithms
////////////////////////////////////////////////////////////////////////////////
namespace parallel {

////////////////////////////////////////////////////////////////////////////////
/// @brief Approximate pi with monte carlo
/// @param _n Number of samples.
/// @param _nt Number of parallel threads
/// @return Approximation of pi
double
pi(size_t _n, size_t _nt) {

  std::atomic<size_t> n_inner_all{0}; // Total for all inner samples

  auto f_ni = [&n_inner_all, _n = _n, _nt = _nt](size_t _i) {
    std::default_random_engine generator{_i};
    std::uniform_real_distribution<double> distribution(-0.5,0.5);
    size_t n_inner = 0;
    for(size_t i = 0; i < _n/_nt; ++i) {
      double x = distribution(generator);
      double y = distribution(generator);
      if(x*x + y*y < 0.25)
        ++n_inner;
    }
    n_inner_all += n_inner;
  };

  // Create all tasks for asyncronous execution. Destructors will wait for them
  // to finish.
  {
    std::vector<std::future<void>> fts;
    fts.reserve(_nt);

    for(size_t i = 0; i < _nt; ++i)
      fts.emplace_back(std::async(std::launch::async, f_ni, i));
  }

  return 4.f*n_inner_all/_n;
}

}