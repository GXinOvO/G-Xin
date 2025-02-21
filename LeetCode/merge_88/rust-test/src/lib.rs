pub fn merge(nums1: &mut Vec<i32>, m: i32, nums2: &mut Vec<i32>, n: i32) {
    let m = m as usize;
    let n = n as usize;

    let mut p1 = if m > 0 { m - 1 } else { 0 }; // 避免负值
    let mut p2 = if n > 0 { n - 1 } else { 0 };
    let mut p = m + n - 1;

    while p2 < n {
        if p1 < m && nums1[p1] > nums2[p2] {
            nums1[p] = nums1[p1];
            if p1 == 0 { break; } // 避免负值
            p1 -= 1;
        } else {
            nums1[p] = nums2[p2];
            if p2 == 0 { break; } // 避免负值
            p2 -= 1;
        }
        if p == 0 { break; } // 避免负值
        p -= 1;
    }
}
