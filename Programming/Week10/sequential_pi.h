////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief Sequential monte carlo approximation of pi.
////////////////////////////////////////////////////////////////////////////////

#include <random>

////////////////////////////////////////////////////////////////////////////////
/// @brief Collection of sequential algorithms
////////////////////////////////////////////////////////////////////////////////
namespace sequential{

////////////////////////////////////////////////////////////////////////////////
/// @brief Approximate pi with monte carlo
/// @param _n Number of samples.
/// @return Approximation of pi
double
pi(size_t _n) {
  std::default_random_engine generator{0};
  std::uniform_real_distribution<double> distribution(-0.5,0.5);

  size_t n_inner = 0;
  for(size_t i = 0; i < _n; ++i) {
    double x = distribution(generator);
    double y = distribution(generator);
    if(x*x + y*y < 0.25)
      ++n_inner;
  }
  return 4.f*n_inner/_n;
}

}