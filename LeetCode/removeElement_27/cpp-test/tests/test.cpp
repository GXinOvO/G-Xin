#include <gtest/gtest.h>
#include <vector>
#include <benchmark/benchmark.h>
#include "../src/main.cpp"

// Google Test cases
TEST(TestRemoveElement, CheckTest1) {
    std::vector<int> nums = {3, 2, 2, 3};
    int val = 3;

    int output = removeElement(nums, val);

    EXPECT_EQ(output, 2);
}

TEST(TestRemoveElement, CheckTest2) {
    std::vector<int> nums = {0, 1, 2, 2, 3, 0, 4, 2};
    int val = 2;

    int output = removeElement(nums, val);

    EXPECT_EQ(output, 5);
}

// Benchmark function
static void BM_RemoveElement_Test1(benchmark::State& state) {
    std::vector<int> nums = {3, 2, 2, 3};
    for (auto _ : state) {
        removeElement(nums, 3);
    }
}
BENCHMARK(BM_RemoveElement_Test1);

static void BM_RemoveElement_Test2(benchmark::State& state) {
    std::vector<int> nums = {0, 1, 2, 2, 3, 0, 4, 2};
    for (auto _ : state) {
        removeElement(nums, 2);
    }
}
BENCHMARK(BM_RemoveElement_Test2);

// Main function
int main(int argc, char **argv) {
    std::cout << "Running main() from " << __FILE__ << std::endl;
    ::testing::InitGoogleTest(&argc, argv);
    int test_result = RUN_ALL_TESTS();

    ::benchmark::Initialize(&argc, argv);
    if (::benchmark::ReportUnrecognizedArguments(argc, argv)) return 1;
    ::benchmark::RunSpecifiedBenchmarks();
    // ::benchmark::Shutdown();

    return test_result;
}