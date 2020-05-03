////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief Simple comparison between copy and move construction.
///
/// This exercise demonstrates various options for copying vs moving data. The
/// conclusion is to appreciate moving, and to ensure move when possible.
///
/// So:
///   - Use pass by const-ref when you do not copy the data
///   - Use pass by move-ref when you *can*
///   - Consider pass by value then move, i.e., a smart pass-by-value to either
///     force a copy or 2-moves.
////////////////////////////////////////////////////////////////////////////////

// STL
#include <chrono>
#include <iomanip>
#include <iostream>
#include <ratio>
#include <string>
#include <vector>
using namespace std;

using my_clock = chrono::high_resolution_clock;
using seconds = chrono::duration<float>;

////////////////////////////////////////////////////////////////////////////////
/// @brief Holder of a string.
////////////////////////////////////////////////////////////////////////////////
class MyStringByVal {
  public:
    ////////////////////////////////////////////////////////////////////////////
    /// @brief Construct by string value.
    /// @param _str String.
    explicit MyStringByVal(string _str) : m_str(_str) {}

  private:
    string m_str; ///< String
};

////////////////////////////////////////////////////////////////////////////////
/// @brief Holder of a string.
////////////////////////////////////////////////////////////////////////////////
class MyStringByValM {
  public:
    ////////////////////////////////////////////////////////////////////////////
    /// @brief Construct by string value.
    /// @param _str String.
    explicit MyStringByValM(string _str) : m_str(move(_str)) {}

  private:
    string m_str; ///< String
};

////////////////////////////////////////////////////////////////////////////////
/// @brief Holder of a string.
////////////////////////////////////////////////////////////////////////////////
class MyStringByConstRef {
  public:
    ////////////////////////////////////////////////////////////////////////////
    /// @brief Construct by string const reference.
    /// @param _str String.
    explicit MyStringByConstRef(const string& _str) : m_str(_str) {}

  private:
    string m_str; ///< String
};

////////////////////////////////////////////////////////////////////////////////
/// @brief Holder of a string.
////////////////////////////////////////////////////////////////////////////////
class MyStringByRValRef {
  public:
    ////////////////////////////////////////////////////////////////////////////
    /// @brief Construct by string rvalue reference.
    /// @param _str String.
    explicit MyStringByRValRef(string&& _str) : m_str(move(_str)) {}

  private:
    string m_str; ///< String
};

////////////////////////////////////////////////////////////////////////////////
/// @brief Main method.
int
main() {

  cout << setw(8) << "n"
    << setw(12) << "Val"
    << setw(12) << "Val 1 Move"
    << setw(12) << "Val 2 Moves"
    << setw(12) << "Const Ref"
    << setw(12) << "RVal Ref" << endl;
  for(size_t i = 0; i < 68; ++i) cout << "-";
  cout << endl;
  cout << setprecision(7);
  cout << fixed;

  for(size_t n = 2; n < 20000000; n*=2) {

    ///////////////////////////////////
    // Create a bunch of stock data
    vector<string> strs; strs.reserve(10);
    for(size_t i = 0; i < 10; ++i) {
      strs.emplace_back(n, static_cast<char>(i + 65));
    }

    cout << setw(8) << n;

    my_clock::time_point start;

    ///////////////////////////////////
    // Test by value

    start = my_clock::now();

    vector<MyStringByVal> mystrvals;
    for(size_t i = 0; i < 10; ++i)
      mystrvals.emplace_back(strs[i]);

    cout << setw(12)
      << chrono::duration_cast<seconds>(my_clock::now() - start).count()/10.;

    ///////////////////////////////////
    // Test by value 1 move

    start = my_clock::now();

    vector<MyStringByValM> mystrval1ms;
    for(size_t i = 0; i < 10; ++i)
      mystrval1ms.emplace_back(strs[i]);

    cout << setw(12)
      << chrono::duration_cast<seconds>(my_clock::now() - start).count()/10.;

    ///////////////////////////////////
    // Test by value 2 moves

    start = my_clock::now();

    vector<MyStringByValM> mystrval2ms;
    for(size_t i = 0; i < 10; ++i)
      mystrval2ms.emplace_back(move(strs[i]));

    cout << setw(12)
      << chrono::duration_cast<seconds>(my_clock::now() - start).count()/10.;

    ///////////////////////////////////
    // Regenerate a bunch of stock data
    strs.clear(); strs.reserve(10);
    for(size_t i = 0; i < 10; ++i) {
      strs.emplace_back(n, static_cast<char>(i + 65));
    }

    ///////////////////////////////////
    // Test by const ref

    start = my_clock::now();

    vector<MyStringByConstRef> mystrconstrefs;
    for(size_t i = 0; i < 10; ++i)
      mystrconstrefs.emplace_back(strs[i]);

    cout << setw(12)
      << chrono::duration_cast<seconds>(my_clock::now() - start).count()/10.;

    ///////////////////////////////////
    // Test by rvalue ref

    start = my_clock::now();

    vector<MyStringByRValRef> mystrrvalrefs;
    for(size_t i = 0; i < 10; ++i)
      mystrrvalrefs.emplace_back(std::move(strs[i]));

    cout << setw(12)
      << chrono::duration_cast<seconds>(my_clock::now() - start).count()/10.;

    cout << endl;
  }
}
