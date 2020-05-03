////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief Example use of polymorphic class hierarchy for stack of data 
///        transforms.
////////////////////////////////////////////////////////////////////////////////

// STL
#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
/// @brief Base class for data transformations.
////////////////////////////////////////////////////////////////////////////////
class DataTransform {
  public:
    DataTransform(std::string&& _s) : m_name{std::move(_s)} {}
    virtual ~DataTransform() = default;

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Non-virtual Interface for applying the transform.
    /// @param _v Data
    void apply(std::vector<int>& _v) {
      std::cout << "Applying: " << m_name << std::endl;
      this->forward(_v);
    }
    ////////////////////////////////////////////////////////////////////////////
    /// @brief Non-virtual Interface for undoing the transform.
    /// @param _v Data
    void undo(std::vector<int>& _v) {
      std::cout << "Undoing: " << m_name << std::endl;
      this->backward(_v);
    }

  private:
    ////////////////////////////////////////////////////////////////////////////
    /// @brief Applying a transform.
    /// @param _v Data
    virtual void forward(std::vector<int>& _v) = 0;
    ////////////////////////////////////////////////////////////////////////////
    /// @brief Undo a transform.
    /// @param _v Data
    virtual void backward(std::vector<int>& _v) = 0;

    std::string m_name; ///< Name of a transform
};

////////////////////////////////////////////////////////////////////////////////
/// @brief Reversing data transform.
////////////////////////////////////////////////////////////////////////////////
class ReverseTransform : public DataTransform {
  public:
    ReverseTransform() : DataTransform("Reverse") {}

  private:
    void forward(std::vector<int>& _v) override {
      std::reverse(_v.begin(), _v.end());
    }
    void backward(std::vector<int>& _v) override {
      std::reverse(_v.begin(), _v.end());
    }
};

////////////////////////////////////////////////////////////////////////////////
/// @brief Reversing data transform.
////////////////////////////////////////////////////////////////////////////////
class SubstituteTransform : public DataTransform {
  public:
    SubstituteTransform(size_t _i, int _v) : DataTransform("Substitute"), 
      m_i{_i}, m_v{_v} {}

  private:
    void forward(std::vector<int>& _v) override {
      m_o = _v[m_i];
      _v[m_i] = m_v;
    }
    void backward(std::vector<int>& _v) override {
      _v[m_i] = m_o;
    }

    size_t m_i; ///< Index.
    int    m_v; ///< New value.
    int    m_o; ///< Old value.  
};

////////////////////////////////////////////////////////////////////////////////
/// @brief Main driver.
/// @return Success/fail.
int
main() {
  using namespace std;

  // Setup
  vector<int> data;
  for(size_t i = 0; i < 10; ++i)
    data.emplace_back(i);

  vector<unique_ptr<DataTransform>> transforms;
  transforms.emplace_back(new ReverseTransform());
  transforms.emplace_back(new SubstituteTransform(1, -1));
  transforms.emplace_back(new SubstituteTransform(8, -8));
  transforms.emplace_back(new ReverseTransform());

  // Baseline
  cout << "Data before transformations:";
  for(auto& i : data)
    cout << " " << i;
  cout << endl;

  // Testing apply
  for(auto& t : transforms)
    t->apply(data);
  cout << "Data after transformations: ";
  for(auto& i : data)
    cout << " " << i;
  cout << endl;

  // Testing undo
  for(auto trit = transforms.rbegin(); trit != transforms.rend(); ++trit)
    (*trit)->undo(data);
  cout << "Data after undoing: ";
  for(auto& i : data)
    cout << " " << i;
  cout << endl;
}