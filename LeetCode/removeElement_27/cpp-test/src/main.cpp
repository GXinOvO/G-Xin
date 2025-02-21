#include <vector>
#include <iostream>

int
removeElement(
    std::vector<int>& nums,
    int val
) {
    int count = 0;
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] != val) count++;
    }
    return count;
}