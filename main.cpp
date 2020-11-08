#include "include/RegexpStackMachine.h"

int main() {
  std::cout << "Enter Regexp in reverse polish notation, "
               "the letter that the suffixes will consist of "
               "and the degree of that letter:\n";
  std::string regexp; char letter_to_find;
  uint32_t degree;
  std::cin >> regexp >> letter_to_find >> degree;
  RegexpStackMachine regexp_machine(regexp);
  try {
    size_t result =
        regexp_machine.FindShortestWordWithSuffix(letter_to_find, degree);
    if (result == INF) {
      std::cout << "INF";
    } else {
      std::cout << result;
    }
  } catch (std::exception& err) {
    std::cout << err.what();
  }
}