#include "gtest/gtest.h"
#include "rnd.h"

TEST(RandomNumberTest, CountTest) { 
    int minv = std::numeric_limits<int>::min();
    int maxv = std::numeric_limits<int>::max();
    for (int i=0; i<1'000'000; i+=1'000) {
        std::vector<int> randvalues = RND<int>(minv, maxv, i);
        EXPECT_EQ(randvalues.size(), i) << "The number of random values was not correct";
    }
}

TEST(RandomNumberTest, BoundsTest) { 
    int count = 1'000'000;
    int minv = std::numeric_limits<int>::min();
    int maxv = std::numeric_limits<int>::max();
    std::vector<int> randvalues = RND<int>(minv, maxv, count);
    for (const int i: randvalues) {
        EXPECT_GE (i, minv) << "Value is less than the minimum value" << i;
        EXPECT_LT (i, maxv) << "Value is greater than or equal to the minimum value" << i;
    }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}