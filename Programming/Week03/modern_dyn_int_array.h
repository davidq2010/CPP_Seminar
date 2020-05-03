////////////////////////////////////////////////////////////////////////////////
/// @brief Modern dynamic integer array
////////////////////////////////////////////////////////////////////////////////
#include <cstdlib>
#include <memory>

class modern_dyn_int_array {
  public:
    modern_dyn_int_array();

    size_t size() const { return m_size; }

    int& operator[](size_t _i) { return m_arr[_i]; }
    const int& operator[](size_t _i) const { return m_arr[_i]; }

    void add(size_t _i, int _e);

    void remove(size_t _i);

  private:
    void resize(size_t _cap);

    size_t m_cap;
    size_t m_size;
    std::unique_ptr<int[]> m_arr;
};