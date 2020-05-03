////////////////////////////////////////////////////////////////////////////////
/// @brief Example of memory managed pointer.
////////////////////////////////////////////////////////////////////////////////
template<typename T>
class managed_ptr {
  private:
    T* m_mem;

  public:
    managed_ptr(T* _mem) : m_mem{_mem} {}
    ~managed_ptr() { delete m_mem; }

          T&  operator*()       { return *m_mem; }
    const T&  operator*() const { return *m_mem; }
          T* operator->()       { return  m_mem; }
    const T* operator->() const { return  m_mem; }
};