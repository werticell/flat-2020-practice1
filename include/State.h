#pragma once

#include "Init.h"

class State {
private:
  uint64_t min_word_length_ = 0;
  std::vector<uint64_t> min_word_length_with_suffix_;

public:
  State(uint64_t min_word_length,  uint32_t degree);
  State() = default;

  State(const State&) = default;
  State(State&& other) = default;
  State& operator=(const State&) = default;
  State& operator=(State&&) = default;


  State operator^(int);
  State operator*(const State & other);
  State operator+(const State & other);

  uint64_t &operator[](size_t ind);

};


