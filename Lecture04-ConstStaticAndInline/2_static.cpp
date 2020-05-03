#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
/// Static
///
/// 1) The static keyword is a note to place the memory in a static location in
///    memory. So "static" does imply "non-changing" but it really means that
///    the memory location does not change.
/// 2) Read "static" as "shared". So a static variable in a function is "shared" 
///    among all invocations, and a static class method is "shared" among all
///    instances.
/// 3) static memory is typically placed before the main method and the call 
///    stack. It is allocated before main begins and deallocated after main 
///    ends. Static variables in functions are not constructed until it is 
///    invoked for a first time.
/// 4) Example static.
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////
/// @brief Example class using static
///        to count instances.
///////////////////////////////////////
class A {
  public:

    A()  { ++m_num_instances; }
    ~A() { --m_num_instances; }

    static size_t get_num_instances() { return m_num_instances; }
  private:
    static size_t m_num_instances;
};

size_t A::m_num_instances{0};

///////////////////////////////////////
/// @brief Main driver.
int
main() {
  {
    A a, b, c;
    cout << A::get_num_instances() << endl;
    {
      A d, e;
      cout << A::get_num_instances() << endl;
    }
    cout << A::get_num_instances() << endl;
  }
  cout << A::get_num_instances() << endl;
}