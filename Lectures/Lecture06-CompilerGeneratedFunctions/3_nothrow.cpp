////////////////////////////////////////////////////////////////////////////////
/// noexcept
///
/// - noexcept is a keyword to note that no exceptions will be thrown by a 
///   method. It is not verified by the compiler. It does however let the
///   compiler perform more agressive optimizations to the function.
/// - Best practices
///   - Add noexcept to functions that cannot throw!
///   - Default is still to not have noexcept.
/// - noexcept can also be conditional on a function being noexcept.
/// - Examples
////////////////////////////////////////////////////////////////////////////////

#include <algorithm>

///////////////////////////////////////
/// @brief Example
///////////////////////////////////////
class A {  
  private:
    int m_i;

  public:
    A() = default;
    A(int _i) : m_i{_i} {}

    int getI() const noexcept {return m_i;} // No exceptions.

    void swap(int _i) noexcept(noexcept(std::swap(m_i, _i))) { // Conditional on swap
      std::swap(m_i, _i);
    }

};

int
main() {
  A a{5};
  a.swap(8);
}