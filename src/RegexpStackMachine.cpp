#include "../include/RegexpStackMachine.h"

static const char ALPHABET [] = {'a', 'b', 'c', '1'};
static const char OPERATORS [] = {'.', '*', '+'};
static const char UNARY_OPERATORS [] = {'*'};
static const char EPSILON = '1';

RegexpStackMachine::RegexpStackMachine(std::string_view regexp) : regexp_(regexp) {}


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

std::pair<State, State>
RegexpStackMachine::GetTopTwoElements(std::stack<State>& st) const {
  State rhs = st.top();
  st.pop();
  State lhs = st.top();
  st.pop();
  return {lhs, rhs};
}
State RegexpStackMachine::GetTopElement(std::stack<State> &st) const {
  State result = st.top();
  st.pop();
  return result;
}

State
RegexpStackMachine::GetOperationResult(std::stack<State>& st, char operator_symbol) const {
  State result;
  size_t operator_valence = GetOperatorValence(operator_symbol);
  if (st.size() < operator_valence)  {
    throw IncorrectRegexpInput("ERROR. Invalid regexp");
  } else {
    switch(operator_symbol) {
    case '+': {
      auto [lhs, rhs] = GetTopTwoElements(st);
      result = lhs + rhs;
      break;
    }
    case '.': {
      auto [lhs, rhs] = GetTopTwoElements(st);
      result = lhs * rhs;
      break;
    }
    case '*': {
      result = GetTopElement(st);
      result.IterateState();
    }
    default:
      break;
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