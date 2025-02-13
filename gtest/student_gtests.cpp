#include <gtest/gtest.h>
#include "../src/hashtable.h"
#include "../src/stats.h"
#include "../src/hasher.h"
#include <vector>
#include <string>

TEST(HashTableTest, IFR) {
    ChatGPTHasher hasher;
    HashTable table(hasher, 10);
    table.insert("mustard");
    table.insert("salt");
    table.insert("food");
    table.insert("bar");
    EXPECT_TRUE(table.find("mustard"));
    EXPECT_TRUE(table.find("salt"));
    EXPECT_TRUE(table.find("food"));
    EXPECT_TRUE(table.find("bar"));
    EXPECT_EQ(table.number_of_entries(), 4);
    table.remove("salt");
    EXPECT_FALSE(table.find("salt"));
    EXPECT_TRUE(table.find("mustard"));
    EXPECT_TRUE(table.find("food"));
    EXPECT_TRUE(table.find("bar"));
}


