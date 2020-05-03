////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief Use case for static method in a class.
///
/// Singleton pattern. When you have a class designed for a single instance, a
/// static method can be used to acquire the single instance. The example 
/// follows a use of a window in a GUI.
////////////////////////////////////////////////////////////////////////////////

// STL
#include <iostream>
#include <string>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
/// @brief Window as a singleton.
////////////////////////////////////////////////////////////////////////////////
class Window {
  public:
    ////////////////////////////////////////////////////////////////////////////
    /// @brief Access the singleton.
    /// @return Singleton.
    static Window& getSingleton() {  // This is static to the class.
      static Window window;          // This is static to this function.
      return window;
    }

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Display the window name.
    void display() {
      cout << m_name << endl;
    }

  private:
    ////////////////////////////////////////////////////////////////////////////
    /// @brief Can only be privately constructed, not publically.
    Window() : m_name{"The one window to rule them all."} {}

    string m_name; ///< Name of window.
};

////////////////////////////////////////////////////////////////////////////////
/// @brief Main driver.
/// @return Success/fail.
int
main() {
  // Window w; // Error!
  Window::getSingleton().display();
}