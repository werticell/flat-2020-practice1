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
  for (uint64_t& length : result.min_word_length_with_suffix_) {
    if (length != INF) {
      length += min_word_length_;
    }
  }

  for (size_t i = 1; i < other.min_word_length_with_suffix_.size(); ++i) {
    if (other.min_word_length_with_suffix_[i] == i) {
      for (size_t j = 1; i + j < min_word_length_with_suffix_.size() ; ++j) {
        // so we have suffix x^i and we try to concat with suffixes x^j
        if (i != INF && min_word_length_with_suffix_[j] != INF) {
          result.min_word_length_with_suffix_[i + j] =
              std::min(result.min_word_length_with_suffix_[i + j],
                       i + min_word_length_with_suffix_[j]);
        }

      }
    }
  }
  return result;
}


void State::IterateState() {
  min_word_length_ = 0;

  for (size_t i = 1; i < min_word_length_with_suffix_.size(); ++i) {
    // it means that we can iterate this suffix to get others which have length k * i
    if (min_word_length_with_suffix_[i] == i) {
      for (int32_t j = i; j < min_word_length_with_suffix_.size(); j += i) {
        min_word_length_with_suffix_[j] = j;
      }
    }
  }

  size_t k = min_word_length_with_suffix_.size();
  std::vector<int64_t> cost(k, INF);
  for (int32_t i = 0; i < k; ++i) {
    if (min_word_length_with_suffix_[i] == i) {
      cost[i] = i;
    }
  }
  std::vector<std::vector<uint64_t >> dp(k, std::vector<uint64_t > (k, INF));
  for (int32_t i = 0; i < k; ++i) {
    dp[i][0] = 0;
  }
  for (int32_t i = 1; i < k; ++i) {
    for (int32_t j = 1; j < k; ++j) {
      if (j >= i && dp[i - 1][j - i] != INF && cost[i] != INF) {
        dp[i][j] = std::min(dp[i - 1][j], dp[i - 1][j - i] + cost[i]);
      } else {
        dp[i][j] = dp[i - 1][j];
      }
    }
  }

  for (int32_t i = 0; i < k; ++i) {
    min_word_length_with_suffix_[i] = std::min(dp[k - 1][i], min_word_length_with_suffix_[i]);
  }

  for (int32_t i = 0; i < k; ++i) {
    if (min_word_length_with_suffix_[i] != i && min_word_length_with_suffix_[i] != INF) {
      for (int32_t j = 0;  i + j < k; ++j) {
         if (min_word_length_with_suffix_[j] == j) {
           min_word_length_with_suffix_[i + j] = std::min(min_word_length_with_suffix_[i + j],
                                                          min_word_length_with_suffix_[i] +
                                                          min_word_length_with_suffix_[j]);
         }
      }
    }
  }

  for (uint64_t i = 1; i < k; ++i) {
    if (min_word_length_with_suffix_[i] == i) {
      for (uint64_t j = 1; j < k; ++j) {
        int32_t shift = (j % i != 0) ? 1 : 0;
        min_word_length_with_suffix_[j] = std::min(min_word_length_with_suffix_[j],
                                                   (i) * (j / i + shift));
      }
    }
  }

}

uint64_t& State::operator[](size_t ind) {
  return min_word_length_with_suffix_[ind];
}