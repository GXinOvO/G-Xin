#include <vector>
#include <iostream>

int
removeElement(
    std::vector<int>& nums,
    int val
) {
    int left = 0, right = nums.size();
    while (left < right) {
        if (nums[left] == val) {
            nums[left] = nums[right - 1];
            right--;
        } else {
            left++;
        }
    }
    return left;
}