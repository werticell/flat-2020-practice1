#pragma once
#include "State.h"

class RegexpStackMachine {
private:
  std::string regexp_;

  static bool IsOperator(char symbol);
  static bool IsLetter(char symbol);
  static uint8_t GetOperatorValence(char symbol);
  static uint8_t GetLetterLength(char symbol);

  State GetOperationResult(std::stack<State>& st, char symbol) const;

public:
  explicit RegexpStackMachine(std::string_view regexp);

  RegexpStackMachine(const RegexpStackMachine&) = delete;
  RegexpStackMachine(RegexpStackMachine&&) = delete;
  RegexpStackMachine& operator=(const RegexpStackMachine&) = delete;
  RegexpStackMachine& operator=(RegexpStackMachine&&) = delete;

  [[nodiscard]] uint64_t FindShortestWordWithSuffix(char letter_to_find, uint32_t degree) const;

};


