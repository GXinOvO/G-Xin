const MAX_POINTS: u32 = 100_000;

fn main() {
    // println!("Hello, world!");

    // let mut x = 5;
    // println!("The value of x is {}", x);

    // x = 6;
    // println!("The value os x is {}", x);

    let s = String::from("Hello World");
    take_ownership(s);

    let x = 5;
    makes_copy(x);

    println!("x: {}", x);
}

fn take_ownership(some_string: String)
{
    println!("{}", some_string)
}

fn makes_copy(some_number: i32)
{
    println!("{}", some_number)
}
