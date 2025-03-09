#[cfg(test)]
mod tests {
    use rust_test::remove_duplicates;

    #[test]
    fn check_test1() {
        let mut nums = vec![1, 1, 2];
        let res = remove_duplicates(&mut nums);
        assert_eq!(res, 2);
    }

    #[test]
    fn check_test2() {
        let mut nums = vec![0, 0, 1, 1, 1, 2, 2, 3, 3, 4];
        let res = remove_duplicates(&mut nums);
        assert_eq!(res, 5);
    }
}