use std::ops::{
    Add,
    Sub,
    Mul,
    Div,
};

pub fn fast_gcd(
    mut a: i64,
    mut b: i64
) -> i64 {
    while b != 0 {
        a %= b;
        std::mem::swap(&mut a, &mut b);
    }
    a.abs()
}

#[derive(Clone, Copy, Debug)]
pub struct Rational
{
    pub num: i64,
    pub den: i64,
}

impl Rational
{
    pub fn new(
        num: i64,
        den: i64,
    ) -> Self {
        // signum()返回正负号
        let g = fast_gcd(num, den) * den.signum();
        Self {
            num: num / g,
            den: den / g,
        }
    }
    pub fn abs(
        self
    ) -> Self {
        Self {
            num: self.num.abs(),
            den: self.den,
        }
    }
    pub fn recip(
        self
    ) -> Self {
        let g = self.num.signum();
        Self {
            num: self.den / g,
            den: self.num / g,
        }
    }
 
}
impl From<i64> for Rational
{
    fn from(
        num: i64
    ) -> Self {
        Self {
            num,
            den: 1,
        }
    }
}
impl Add for Rational
{
    type Output = Self;
    fn add(
        self, 
        other: Self
    ) -> Self {
        Self::new(
            self.num * other.den + self.den * other.num,
            self.den * other.den,
        )
    }
}
impl Sub for Rational
{
    type Output = Self;
    fn sub(
        self,
        other: Self
    ) -> Self {
        Self::new(
            self.num * other.den - self.den * other.num,
            self.den * other.den,
        )
    }
}

impl Mul for Rational 
{
    type Output = Self;
    fn mul(
        self, 
        other: Self
    ) -> Self {
        Self::new(
            self.num * other.num,
            self.den * other.den,
        )
    }
}

impl Div for Rational
{
    type Output = Self;
    fn div(
        self,
        other: Self,
    ) -> Self {
        self * other.recip()
    }
}