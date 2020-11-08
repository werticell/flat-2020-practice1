#include "../include/RegexpStackMachine.h"

RegexpStackMachine::RegexpStackMachine(std::string_view regexp) {
  std::copy_if(regexp.cbegin(), regexp.cend(),
               std::back_inserter(regexp_),
               [](char sym) {return sym != ' ';});
}


bool RegexpStackMachine::IsOperator(char symbol) {
  return std::any_of(std::begin(OPERATORS), std::end(OPERATORS),
               [symbol](char sym) {return sym == symbol;});

}

bool RegexpStackMachine::IsLetter(char symbol) {
  return std::any_of(std::begin(ALPHABET), std::end(ALPHABET),
                     [symbol](char sym) {return sym == symbol;});
}


uint8_t RegexpStackMachine::GetOperatorValence(char symbol) {
  if(std::any_of(std::begin(UNARY_OPERATORS), std::end(UNARY_OPERATORS),
                     [symbol](char sym) {return sym == symbol;})) {
    return UNARY_VALENCE;
  } else {
    return BINARY_VALENCE;
  }
}
uint8_t RegexpStackMachine::GetLetterLength(char symbol) {
  return (symbol == EPSILON) ? 0 : 1;
}

State
RegexpStackMachine::GetOperationResult(std::stack<State>& st, char symbol) const {
  State result;
  size_t operator_valence = GetOperatorValence(symbol);
  if (st.size() < operator_valence)  {
    throw IncorrectRegexpInput("ERROR. Invalid regexp");
  } else {
    result = st.top(); st.pop();
    
    for (size_t i = 0; i < operator_valence - 1; ++i) {
      State temp = st.top(); st.pop();

      switch(symbol) {
      case '+': {
        result = temp + result;
        break;
      }
      case '.': {
        result = temp * result;
        break;
      }
      default:
        break;
      }
    }
    if (symbol == '*') {
      result = result ^(0);
    }
  }
  return result;
}

uint64_t
RegexpStackMachine::FindShortestWordWithSuffix(char letter_to_find, uint32_t degree) const {
  std::stack<State> regexp_processing;

  for (char symbol : regexp_) {

    if (IsLetter(symbol)) {
      regexp_processing.emplace(GetLetterLength(symbol), degree);
      if (symbol == letter_to_find) {
        regexp_processing.top()[1] = 1;
      }
    } else if (IsOperator(symbol)) {
      regexp_processing.push(GetOperationResult(regexp_processing, symbol));
    } else {
      throw IncorrectRegexpInput("ERROR. Invalid character "
                                 "not from the alphabet");
    }
  }
  if (regexp_processing.size() > 1) {
    throw IncorrectRegexpInput("ERROR. Invalid regexp");
  }
  return regexp_processing.top()[degree];
}