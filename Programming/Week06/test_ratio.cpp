////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief Test of the ratio class.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <sstream>

#include "ratio.h"

using namespace std;

int
main() {
  // Construction, conversion, negation
  {
    cout << "Test Construction, Conversion, Negation" << endl;
    ratio r1;
    cout << " Default: " << r1 << endl;
    ratio r2{2, 3};
    cout << "  Normal: " << r2 << endl;
    ratio r3 = -r2;
    cout << "Negation: " << r3 << endl;
    float x = r3;
    cout << "   Float: " << x << endl;
    double y = r3;
    cout << "  Double: " << y << endl;
  }

  // Binary operators
  {
    cout << "\nTest Binary Operators" << endl;
    ratio r1{4, 5}, r2{2, 3};
    cout << "      Addition: " << (r1+r2) << endl;
    cout << "   Subtraction: " << (r1-r2) << endl;
    cout << "Multiplication: " << (r1*r2) << endl;
    cout << "      Division: " << (r1/r2) << endl;
  }

  // Relational operators
  {
    cout << "\nTest Relational Operators" << endl;
    ratio r1{4, 5}, r2{2, 3}, r3{4, 6};
    cout << "                   Equal: " << (r1 == r2) << "\t" << (r2 == r3) << endl;
    cout << "                 Inequal: " << (r1 != r2) << "\t" << (r2 != r3) << endl;
    cout << "               Less-than: " << (r1 <  r2) << "\t" << (r2 <  r3) << endl;
    cout << "   Less-than-or-equal-to: " << (r1 <= r2) << "\t" << (r2 <= r3) << endl;
    cout << "            Greater-than: " << (r1 >  r2) << "\t" << (r2 >  r3) << endl;
    cout << "Greater-than-or-equal-to: " << (r1 >= r2) << "\t" << (r2 >= r3) << endl;
  }

  // Testing stream extraction
  {
    cout << "\nTest Stream Extraction" << endl;
    ratio r;
    istringstream iss("5");
    iss >> r;
    cout << "Read 1: " << r << endl;
    iss.clear();
    iss.str("4/3");
    iss >> r;
    cout << "Read 2: " << r << endl;
  }

  // Testing throwing
  {
    cout << "\nTest Exceptions" << endl;
    try {
      ratio r{1, 0};
    }
    catch(domain_error& d) {
      cout << "Caught error: " << d.what() << endl;
    }
    try {
      ratio r1{1, 2}, r2{0, 4};
      r1 /= r2;
    }
    catch(domain_error& d) {
      cout << "Caught error: " << d.what() << endl;
    }
  }
}