#include <gtest/gtest.h>
#include <vector>
#include "../src/main.cpp"

TEST(
    TestRemoveDuplicates, CheckTest1
) {
    std::vector<int> nums = {1, 1, 2};
    
    int result = remove_duplicates(nums);

    EXPECT_EQ(result, 2);
}

TEST(
    TestRemoveDuplicates, CheckTest2
) {
    std::vector<int> nums = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
    
    int result = remove_duplicates(nums);

    EXPECT_EQ(result, 5);
}

int
main(
    int argc,
    char **argv
) {
    std::cout << "Running main() from " << __FILE__ << std::endl;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}