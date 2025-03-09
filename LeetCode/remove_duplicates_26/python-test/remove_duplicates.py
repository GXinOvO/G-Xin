from typing import List

def remove_duplicates(
    nums: List[int]
) -> int:
    n = len(nums)
    if n == 0:
        return 0
    
    slow, fast = 1, 1
    while fast < n:
        if nums[fast] != nums[fast - 1]:
            nums[slow] = nums[fast]
            slow += 1
        fast += 1
    return slow