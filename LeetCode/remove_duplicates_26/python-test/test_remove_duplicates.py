import unittest
from remove_duplicates import remove_duplicates

class TestRemoveDuplicates(unittest.TestCase):
    def test_check_test1(self):
        nums = [1, 1, 2]
        self.assertEqual(remove_duplicates(nums), 2)
        
    def test_check_test2(self):
        nums = [0, 0, 1, 1, 1, 2, 2, 3, 3, 4]
        self.assertEqual(remove_duplicates(nums), 5)
    
if __name__ == '__main__':
    unittest.main()