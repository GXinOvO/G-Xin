#include <gtest/gtest.h>
#include <vector>
#include "../src/main.cpp"

TEST(
    TestMerge, CheckTest1
) {
    std::vector<int> nums1 = {1, 2, 3, 0, 0, 0};
    std::vector<int> nums2 = {2, 5, 6};
    int m = 3, n = 3;
    
    merge(nums1, m, nums2, n);

    std::vector<int> result = {1, 2, 2, 3, 5, 6};
    EXPECT_EQ(nums1, result);
}

TEST(
    TestMerge, CheckTest2
) {
    std::vector<int> nums1 = {1};
    std::vector<int> nums2 = {};
    int m = 1, n = 0;
    
    merge(nums1, m, nums2, n);

    std::vector<int> result = {1};
    EXPECT_EQ(nums1, result);
}

TEST(
    TestMerge, CheckTest3
) {
    std::vector<int> nums1 = {0};  // 确保nums1有足够的空间
    std::vector<int> nums2 = {1};
    int m = 0, n = 1;
    
    merge(nums1, m, nums2, n);

    std::vector<int> result = {1};
    EXPECT_EQ(nums1, result);
}

int
main(
    int argc, 
    char **argv
) {
    std::cout <<"Running main() from " << __FILE__ << std::endl;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}