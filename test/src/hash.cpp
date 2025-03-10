#include <gtest/gtest.h>

#include <omen/hash.h>

TEST(hash, stringHash) {
  using omen::hash::hash_value;
  EXPECT_EQ(hash_value("Hello, World!"), 0x6ef05bd7cc857c54);
  EXPECT_EQ(hash_value("core/boot/boot.lua"), 0x5ca5d2cbbd841194);
}
