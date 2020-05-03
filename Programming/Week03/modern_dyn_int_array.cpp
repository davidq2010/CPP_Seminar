#include "modern_dyn_int_array.h"

#include <stdexcept>

modern_dyn_int_array::
modern_dyn_int_array() : m_size{0}, m_cap{0} {
  resize(10);
}

void 
modern_dyn_int_array::
add(size_t _i, int _e) {
  if(_i < m_size + 1) {
    if(m_size == m_cap)
      resize(2*m_cap);
    for(size_t j = m_size; j > _i; --j)
      m_arr[j] = m_arr[j-1];
    m_arr[_i] = _e;
    ++m_size;
  }
  else
    throw std::invalid_argument("Bad add index");
}

void 
modern_dyn_int_array::
remove(size_t _i) {
  if(_i < m_size) {
    for(size_t j = _i; j < m_size - 1; ++j)
      m_arr[j] = m_arr[j+1];
    m_arr[m_size-1] = 0;
    --m_size;
  }
  else
    throw std::invalid_argument("Bad remove index");
}

void 
modern_dyn_int_array::
resize(size_t _cap) {
  std::unique_ptr<int[]> new_arr = std::make_unique<int[]>(_cap);
  for(size_t i = 0; i < _cap; ++i) {
    if(i < m_cap)
      new_arr[i] = m_arr[i];
    else
      new_arr[i] = 0;
  }
  std::swap(new_arr, m_arr);
  m_cap = _cap;
}