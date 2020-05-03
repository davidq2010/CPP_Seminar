////////////////////////////////////////////////////////////////////////////////
/// Smart pointers in the standard library
///
/// - std::unique_ptr - a single ownership model of a pointer. When the object
///                     is destructed, it deletes its managed pointer, i.e., it
///                     is synonymous to the managed_ptr from before.
///   - Used when the "owner" of a piece of memory is known, so when the owner 
///     is destructed then the owned memory is subsequently deleted.
///   - Ownership can be transfered, and thus unique_ptr can be moved but not
///     copied.
/// - std::shared_ptr - a multiply owned pointer which is tracked through 
///                     reference counting. A copy construction increments the 
///                     count (or copy assignment), and the destruction 
///                     decrements the count. When the count goes to 0, the 
///                     memory is deleted.
///   - Used for shared ownership (or "no" ownership).
/// - std::weak_ptr - pointer to shared ownership that is not memory managed, 
///                   but it is still protected from misuse to avoid 
///                   segmentation faults.
///   - Used in conjunction with a shared_ptr.
/// - Best practices
///   - Do not resort to pointers. Remember they are to (1) extend object scope,
///     (2) to conserve memory in passing or ownership in a data structure, and 
///     (3) support polymorphism.
///   - Design deliberately! Ask yourself the ownership question to decide.
///   - Prefer unique_ptr.
///   - Prefer use of std::make_shared and std::make_unique.
////////////////////////////////////////////////////////////////////////////////

#include <memory>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
/// Pointer miscellany
///
/// - Know the difference between:
///   -       T*       - pointer to a T
///   - const T*       - pointer to a const T ("read only" pointer)
///   -       T* const - const pointer (cannot switch what it points to) to a T
///   - const T* const - const pointer to a const T
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////
/// @brief Main with examples
int 
main() {
  unique_ptr<int> my_int_ptr(new int{5});
  unique_ptr<string> my_string_ptr = make_unique<string>("Hello world!");
  auto my_complex_ptr = make_unique<vector<pair<double, string>>>();
  // Use them like pointers.
}