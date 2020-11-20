#pragma once
#include <string>
#include <stack>
#include <cstdint>
#include <vector>
#include <utility>
#include <iostream>
#include <string_view>

enum : size_t {
  UNARY_VALENCE = 1,
  BINARY_VALENCE = 2
};

const size_t INF = std::numeric_limits<size_t>::max();


class IncorrectRegexpInput : public std::exception {
private:
  std::string error_string;

public:
  explicit IncorrectRegexpInput(std::string error) : error_string(std::move(error)) {}


  [[nodiscard]] const char * what() const noexcept override {
    return error_string.c_str(); }

};