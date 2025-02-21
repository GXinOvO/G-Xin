import unittest
from merge import merge

class TestMerge(unittest.TestCase):
    def test_check_test1(self):
        nums1 = [1, 2, 3, 0, 0, 0]
        nums2 = [2, 5, 6]
        m = 3
        n = 3
        merge(nums1, m, nums2, n)
        self.assertEqual(nums1, [1, 2, 2, 3, 5, 6])

    def test_check_test2(self):
        nums1 = [1]
        nums2 = []
        m = 1
        n = 0
        merge(nums1, m, nums2, n)
        self.assertEqual(nums1, [1])

    def test_check_test3(self):
        nums1 = [0]
        nums2 = [1]
        m = 0
        n = 1
        merge(nums1, m, nums2, n)
        self.assertEqual(nums1, [1])

if __name__ == '__main__':
    unittest.main()
