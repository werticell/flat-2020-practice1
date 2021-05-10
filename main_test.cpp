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

TEST(Test_iterate, FIRST) {
  std::string regexp = "aa.aa.a.+aa.a.a.a.+"; // (aa + aaa + aaaaa)*
  RegexpStackMachine regexp_machine(regexp);
  size_t result =
      regexp_machine.FindShortestWordWithSuffix('a', 2);
  EXPECT_EQ(result, 2);
}

TEST(Test_iterate, SECOND) {
  std::string regexp = "aa.aa.a.+aa.a.a.a.+*"; // (aa + aaa + aaaaa)*
  RegexpStackMachine regexp_machine(regexp);
  size_t result =
      regexp_machine.FindShortestWordWithSuffix('a', 21);
  EXPECT_EQ(result, 21);
}

TEST(Test_iterate, Third) {
  std::string regexp = "ab.b.*"; // (abb)*
  RegexpStackMachine regexp_machine(regexp);
  size_t result =
      regexp_machine.FindShortestWordWithSuffix('b', 3);
  EXPECT_EQ(result, INF);
}

TEST(Test_iterate, Fourth) {
  std::string regexp = "ab.b.bb.+*"; // (abb+bb)*
  RegexpStackMachine regexp_machine(regexp);
  size_t result =
      regexp_machine.FindShortestWordWithSuffix('b', 3);
  EXPECT_EQ(result, 4);
}

TEST(Test_iterate, Fifth) {
  std::string regexp = "ab.bb.b.b.+*"; // (ab+bbbb)*
  RegexpStackMachine regexp_machine(regexp);
  size_t result =
      regexp_machine.FindShortestWordWithSuffix('b', 5);
  EXPECT_EQ(result, 6); // not 8
}


int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}