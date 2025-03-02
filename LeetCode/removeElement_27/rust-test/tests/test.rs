#[cfg(test)]
mod tests{
    use rust_test::removeElement;

    #[test]
    fn 
    check_test1(

    ) {
        let mut nums = vec![3, 2, 2, 3]; 

        let result = removeElement(&mut nums, 3);
        assert_eq!(result, 2);
    }

    #[test]
    fn
    check_test2(

    ) {
        let mut nums = vec![0, 1, 2, 2, 3, 0, 4, 2];

        let result = removeElement(&mut nums, 2);
        assert_eq!(result, 5);
    }
}