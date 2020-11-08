#include "../include/State.h"

State::State(uint64_t min_word_length, uint32_t degree) : min_word_length_(min_word_length),
                                min_word_length_with_suffix_(degree + 1, INF) {}


State State::operator+(const State & other) {
  State result = other;

  for (size_t i = 1; i < result.min_word_length_with_suffix_.size(); ++i) {
    result.min_word_length_with_suffix_[i] =
        std::min(min_word_length_with_suffix_[i],
                 result.min_word_length_with_suffix_[i]);
  }

  result.min_word_length_ = std::min(result.min_word_length_, min_word_length_);
  return result;
}

State State::operator*(const State & other) {
  /* if in "other" vector x_i = i its means that we can get word fully of letters_to_find in some degree
   * so we can iterate with such suffix over "this" vector and try to improve already
   * counted suffixes
   */
  State result = other;
  result.min_word_length_ += min_word_length_;
  // just try to concat "other" with the word with the minimal possible length from "this"
  for (uint64_t & i : result.min_word_length_with_suffix_) {
    if (i != INF) {
      i += min_word_length_;
    }
  }

  for (size_t i = 1; i < other.min_word_length_with_suffix_.size(); ++i) {
    if (other.min_word_length_with_suffix_[i] == i) {
      for (size_t j = 1; i + j < min_word_length_with_suffix_.size() ; ++j) {
        // so we have suffix x^i and we try to concat with suffixes x^j
        if (other.min_word_length_with_suffix_[i] != INF && min_word_length_with_suffix_[j] != INF) {
          result.min_word_length_with_suffix_[i + j] =
              std::min(result.min_word_length_with_suffix_[i + j],
                       other.min_word_length_with_suffix_[i] + min_word_length_with_suffix_[j]);
        }

      }
    }
  }
  return result;
}


State State::operator^(int) {
  State result = *this;
  result.min_word_length_ = 0;

  for (size_t i = 1; i < result.min_word_length_with_suffix_.size(); ++i) {
    // it means that we can iterate this suffix to get others which have length k * i
    if (result.min_word_length_with_suffix_[i] == i) {
      for (int j = i; j < result.min_word_length_with_suffix_.size(); j += i) {
        result.min_word_length_with_suffix_[j] = j;
      }
    }
  }
  return result;
}

uint64_t& State::operator[](size_t ind) {
  return min_word_length_with_suffix_[ind];
}