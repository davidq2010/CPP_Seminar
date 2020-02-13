////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief A brief overview of RAII and Smart Pointers.
///
/// Outline
/// - Resources
/// - Resource Acquisition Is Initialization (RAII)
///   - Example with smart pointer.
/// - Smart pointers in the standard library
///   - std::unique_ptr
///   - std::shared_ptr
///   - std::weak_ptr
/// - Pointer miscellany
////////////////////////////////////////////////////////////////////////////////

// STL
#include <exception>
#include <fstream>
#include <iostream>
#include <string>

#include "1_raii.h"

////////////////////////////////////////////////////////////////////////////////
/// Resources
///
/// - Limited, shared component of a computer, its operating system, or a 
///   program.
/// - Examples
///   - Memory - a program is limited typically by physical memory of a machine.
///   - Files  - the operating system can only have so many file pointers at a 
///              time.
///   - Thread/Processes - The number of processes that can be managed is
///                        limited by the operating system.
///     - Mutex Locks - A section of a program that only a limited number of 
///                     threads can execute at a time.
///   - Graphics objects - a "pointer" to entities living on the GPU which has
///                        limited memory.
///   - Etc.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// Resource Acquisition Is Initialization (RAII)
///
/// - Motivating example is below in (parse_some_file) which you track a file 
///   pointer and you have to somehow give it back to the system. In this case,
///   the method in question has many exits (throw/return). So you as a 
///   programmer would have to remember to close the file at each exit point, 
///   which is error prone. RAII solves this motivating example.
/// - A fundamental design of C++ from its inception.
/// - Simply put, RAII dictates that a constructor allocates resources and a 
///   destructor deallocates resources. The example (parse_some_file_with_RAII)
///   is shown below to help explain further.
/// - The compiler can automatically generate these methods for an object with
///   a  well defined construction/destruction order of its member variables 
///   (more on this in another lecture).
/// - Constructors are automatically invoked when statically constructing an
///   object, and destructors are automatically invoked on statically allocated
///   data when they go out of scope. This excess code is automatically inserted
///   by the constructor, so you should never invoke a destructor by yourself.
///   - Static allocation - memory requirements and location, i.e., offset, are 
///                         determined at compile time. This does not imply the 
///                         function call stack.
///   - Dynamical allocation - memory requirements or location are determined
///                            during runtime. This does not always imply the 
///                            "heap".
///   - Destructor is guaranteed to be called and will be called in a 
///     predictable and defined fashion, i.e., you can rely on this feature.
/// - See a simple example of a memory managed pointer (smart pointer) defined 
///   in the accompanying header file, and use below.
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////
/// @brief Motivating RAII Example
void parse_some_file(const std::string& _filename) {
  FILE* file; // A File pointer
  file = fopen(_filename.c_str(), "r"); // Open for reading
  // You must close the file pointer on all possible exits or else there will be
  // a resource leak of a file pointer!
  if(file != nullptr) {
    // Complex logic of parsing
    // Read a string for example
    char buffer[10];
    if(fgets(buffer, 10, file) != nullptr) {
      // Worked
    }
    else {
      // Bad file format...you must remember to close!
      fclose(file);
      throw std::invalid_argument("Bad file format.");
    }
    // Etc...Many places this can go wrong.

    // Remember to close the pointer here too when done.
    fclose(file);
  }
  else { // File not existing
    throw std::invalid_argument("File not found.");
  }
}

void parse_some_file_with_RAII(const std::string& _filename) {
  std::ifstream ifs(_filename); ///< This is an object containing a file pointer 
                           ///  implemented with a good RAII design. It closes
                           ///  in the destructor.
  if(ifs) {
    // Complex logic of parsing
    std::string tag;
    if(ifs >> tag) {
      // Worked
    }
    else {
      // Bad file format
      // RAII will destruct ifs, i.e., close the file pointer
      throw std::invalid_argument("Bad file format.");
    }
    // Many places this can go wrong.
  }
  else { // File not existing
    throw std::invalid_argument("File not found.");
  }
  // Because of RAII in C++ ofs's destructor is called here to ensure the file
  // pointer is released.
}

///////////////////////////////////////
/// @brief Example of RAII use of
///        memory managed pointer.
void
example_memory_managed_ptr() {
  int* i = new int(5); // After using, I am required to delete.
  // Use i
  delete i; // I have to remember this.

  // Or with a memory managed ptr!
  {
    managed_ptr<int> i = managed_ptr<int>(new int(5));
    // Use
    (*i)++;
    std::cout << "I: " << *i << std::endl;
    // Destructs here where it goes out of scope and it gets deleted.
  }

  // Similar example with a memory managed object
  {
    managed_ptr<std::string> s = 
      managed_ptr<std::string>(new std::string("Hello"));
    s->append(" World!");
    std::cout << "S: " << *s << std::endl;
    // Destructs here.
  }
}

///////////////////////////////////////
/// @brief Main
int
main() {
  example_memory_managed_ptr();
}