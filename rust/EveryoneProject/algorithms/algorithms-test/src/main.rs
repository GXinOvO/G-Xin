pub mod math;

use math::num::{
    Rational,
};

fn main() {
    let three = Rational::from(3);
    let six = Rational::from(6);
    let three_and = three + six;
    let half = three_and / six;
    let half_sub_six = half - six;

    println!("three_and_six: {:#?}", three_and);
    println!("half: {:#?}", half);
    println!("half_sub_six: {:#?}", half_sub_six);
}
