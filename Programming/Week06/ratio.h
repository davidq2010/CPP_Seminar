////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief Ratio class.
////////////////////////////////////////////////////////////////////////////////

#include <exception>
#include <iostream>
#include <string>

////////////////////////////////////////////////////////////////////////////////
/// @brief Ratio class (numerator/denumenator).
////////////////////////////////////////////////////////////////////////////////
class ratio {
  public:
    ////////////////////////////////////////////////////////////////////////////
    /// @name Constructors and special member functions
    /// @{

    /// @brief No-arg constructor setting ratio to 0
    ratio() = default;
    /// @brief Regular constructor
    /// @param _n Numerator
    /// @param _d Denuminator
    ratio(long _n, long _d) : m_num{_n}, m_den{_d} {
      reduce();
    }

    // While destructor, copy, move will be included by default, I am deciding
    // to explicitely include them.

    /// @brief Destructor
    ~ratio() = default;
    /// @brief Copy constructor
    ratio(const ratio&) = default;
    /// @brief Move constructor
    ratio(ratio&&) = default;
    /// @brief Copy assignment
    ratio& operator=(const ratio&) = default;
    /// @brief Move assignment
    ratio& operator=(ratio&&) = default;

    /// @}
    ////////////////////////////////////////////////////////////////////////////
    
    ////////////////////////////////////////////////////////////////////////////
    /// @name Conversion and unary operators
    /// @{

    /// @brief Convert ratio to a float
    operator float() const noexcept {
      return (float)m_num/m_den;
    }
    /// @brief Convert ratio to a double
    operator double() const noexcept {
      return (double)m_num/m_den;
    }

    /// @brief Negation operator
    friend ratio operator-(const ratio& _a) {
      return ratio(-_a.m_num, _a.m_den);
    }

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Binary operators
    /// @{

    /// @brief Addition-assignment operator
    ratio& operator+=(const ratio& _o) & noexcept {
      long n = m_num*_o.m_den + m_den*_o.m_num;
      long d = m_den*_o.m_den;
      m_num = n;
      m_den = d;
      reduce();
      return *this;
    }
    /// @brief Subtraction-assignment operator
    ratio& operator-=(const ratio& _o) & noexcept {
      long n = m_num*_o.m_den - m_den*_o.m_num;
      long d = m_den*_o.m_den;
      m_num = n;
      m_den = d;
      reduce();
      return *this;
    }
    /// @brief Multiplication-assignment operator
    ratio& operator*=(const ratio& _o) & noexcept {
      m_num *= _o.m_num;
      m_den *= _o.m_den;
      reduce();
      return *this;
    }
    /// @brief Division-assignment operator
    ratio& operator/=(const ratio& _o) & {
      m_num *= _o.m_den;
      m_den *= _o.m_num;
      reduce();
      return *this;
    }

    /// @brief Addition operator
    friend ratio operator+(ratio _a, const ratio& _b) noexcept {
      _a += _b;
      return _a;
    }
    /// @brief Subtraction operator
    friend ratio operator-(ratio _a, const ratio& _b) noexcept {
      _a -= _b;
      return _a;
    }
    /// @brief Multiplication operator
    friend ratio operator*(ratio _a, const ratio& _b) noexcept {
      _a *= _b;
      return _a;
    }
    /// @brief Division operator
    friend ratio operator/(ratio _a, const ratio& _b) {
      _a /= _b;
      return _a;
    }
    
    /// @}
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    /// @name Relational Operators
    /// @{

    /// @brief Equality operator
    friend bool operator==(const ratio& _a, const ratio& _b) noexcept {
      return _a.m_num == _b.m_num && _a.m_den == _b.m_den;
    }
    /// @brief Inequality operator
    friend bool operator!=(const ratio& _a, const ratio& _b) noexcept {
      return !(_a == _b);
    }
    /// @brief Less-than operator
    friend bool operator<(const ratio& _a, const ratio& _b) noexcept {
      return _a.m_num*_b.m_den < _a.m_den*_b.m_num;
    }
    /// @brief Less-than-or-equal-to operator
    friend bool operator<=(const ratio& _a, const ratio& _b) noexcept {
      return _a.m_num*_b.m_den <= _a.m_den*_b.m_num;
    }
    /// @brief Greater-than operator
    friend bool operator>(const ratio& _a, const ratio& _b) noexcept {
      return !(_a <= _b);
    }
    /// @brief Greater-than-or-equal-to operator
    friend bool operator>=(const ratio& _a, const ratio& _b) noexcept {
      return !(_a < _b);
    }

    /// @}
    ////////////////////////////////////////////////////////////////////////////
    
    ////////////////////////////////////////////////////////////////////////////
    /// @name Put/Get Operators
    /// @{

    /// @brief Stream insertion operator
    friend std::ostream& operator<<(std::ostream& _os, const ratio& _r) {
      if(_r.m_den == 1)
        return _os << _r.m_num;
      else
        return _os << _r.m_num << '/' << _r.m_den;
    }

    /// @brief Stream extraction operator
    friend std::istream& operator>>(std::istream& _is, ratio& _r) {
      std::string frac;
      _is >> frac;
      size_t pos = frac.find('/');
      if(pos == std::string::npos) {
        _r.m_num = atol(frac.c_str());
        _r.m_den = 1;
      }
      else {
        _r.m_num = atol(frac.substr(0, pos).c_str());
        _r.m_den = atol(frac.substr(pos+1).c_str());
      }
      return _is;
    }

    /// @}
    ////////////////////////////////////////////////////////////////////////////

  private:

    ////////////////////////////////////////////////////////////////////////////
    /// @name Private helper methods
    /// @{

    /// @brief Reduce to lowest terms
    void reduce() {
      if(m_den == 0)
        throw std::domain_error("Division by zero.");
      long g = gcd(abs(m_num), abs(m_den));
      m_num /= g;
      m_den /= g;
      if(m_den < 0) {
        m_num *= -1;
        m_den *= -1;
      }
    }

    /// @brief Compute greatest common divisor
    /// @param _a Number
    /// @param _b Number
    /// @return GCD of @c _a and @c _b
    static long gcd(long _a, long _b) noexcept {
      while(_b != 0) {
        long t = _b;
        _b = _a % _b;
        _a = t;
      }
      return _a;
    }

    /// @}
    ////////////////////////////////////////////////////////////////////////////

    long m_num{1}; ///< Numerator.
    long m_den{1}; ///< Denominator.
};