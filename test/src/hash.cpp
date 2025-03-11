#include <gtest/gtest.h>

#include <omen/hash.h>

using omen::hash::hash_value;
using omen::hash::HashId;

TEST(hash_value, hashString) {
  EXPECT_EQ(hash_value("Hello, World!"), 0x6ef05bd7cc857c54);
  EXPECT_EQ(hash_value("core/boot/boot.lua"), 0x5ca5d2cbbd841194);
}

TEST(hash_value, emptyValue) {
  EXPECT_EQ(hash_value(nullptr, 0), 0xcbf29ce484222325);
}

TEST(HashId, hashString) {
  HashId hash1("Hello, World!");
  HashId hash2("core/boot/boot.lua");
  EXPECT_EQ(hash1.get(), 0x6ef05bd7cc857c54);
  EXPECT_EQ(hash2.get(), 0x5ca5d2cbbd841194);
}

TEST(HashId, comparison) {
  HashId hash1("abcdefg");
  HashId hash2("abcdefg");
  HashId hash3("1234567");

  EXPECT_FALSE(hash1 == hash3);
  EXPECT_TRUE(hash1 == hash2);

  EXPECT_FALSE(hash1 != hash2);
  EXPECT_TRUE(hash2 != hash3);
}
