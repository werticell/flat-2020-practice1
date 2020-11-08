#include "include/RegexpStackMachine.h"
#include <gtest/gtest.h>
const size_t INF_ = std::numeric_limits<size_t>::max();


TEST(First_example_test, FIRST) {
  std::string regexp = "ab+c.aba.*.bac.+.+*";
  RegexpStackMachine regexp_machine(regexp);
  size_t result =
      regexp_machine.FindShortestWordWithSuffix('b', 2);
  EXPECT_EQ(result, INF_);
}

TEST(Second_example_test, SECOND) {
  std::string regexp = "acb..bab.c.*.ab.ba.+.+*a.";
  RegexpStackMachine regexp_machine(regexp);
  size_t result =
      regexp_machine.FindShortestWordWithSuffix('a', 2);
  EXPECT_EQ(result, 4);
}


int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}