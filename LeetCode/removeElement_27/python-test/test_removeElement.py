import unittest
from removeElement import removeElement

class TestRemoveElement(unittest.TestCase):
    def test_check_test1(self):
        nums = [3, 2, 2, 3]
        val = 3
        result = removeElement(nums, val)
        self.assertEqual(result, 2)

    def test_check_test2(self):
        nums = [0, 1, 2, 2, 3, 0, 4, 2]
        val = 2
        result = removeElement(nums, val)
        self.assertEqual(result, 5)

if __name__ == '__main__':
    unittest.main()