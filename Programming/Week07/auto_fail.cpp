////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief Failure of auto with vector<bool>.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
/// @brief Generate bitfield.
/// @param _b 3rd Bit
/// @return Bit field of size 5.
std::vector<bool>
bitField(bool _b) {
  return std::vector<bool>({true, true, _b, true, true});
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Process
/// @param _bit Bit
void
process(bool _bit) {
  std::cout << "Bit: " << _bit << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Main driver.
/// @return Success/fail.
int
main() {
  // Auto here deduces std::vector<bool>::reference which is a proxy class, not
  // a bool as we might expect. Only holds true for vector<bool>.
  std::cout << "Incorrect behavior" << std::endl;
  auto bit1 = bitField(true)[2];
  auto bit2 = bitField(false)[2];
  process(bit1); // Should print 1, but prints 0!
  process(bit2); // Should print 0, but behavior is undefined.

  // Correct behavior
  std::cout << "\nCorrect behavior" << std::endl;
  bool bit3 = bitField(true)[2];
  bool bit4 = bitField(false)[2];
  process(bit3);
  process(bit4);
}