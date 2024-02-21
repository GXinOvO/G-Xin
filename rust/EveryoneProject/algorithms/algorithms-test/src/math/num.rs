use std::ops::{
    Add,
    Sub,
    Mul,
    Div,
    Neg,
    Index,
    IndexMut,
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

#[derive(Clone, Copy, Debug, Eq, PartialEq)]
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
impl Neg for Rational
{
    type Output = Self;
    fn neg(
        self
    ) -> Self {
        Self {
            num: -self.num,
            den: self.den,
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
impl Ord for Rational
{
    fn cmp(
        &self, 
        other: &Self
    ) -> std::cmp::Ordering {
        (self.num * other.den).cmp(&(self.den * other.num))
    }
}
impl PartialOrd for Rational
{
    fn partial_cmp(
        &self,
        other: &Self,
    ) -> Option<std::cmp::Ordering> {
        Some(self.cmp(other))
    }
}

#[derive(Clone, Copy, Debug, PartialEq)]
pub struct Complex 
{
    pub real: f64,
    pub imag: f64,
}
impl Complex 
{
    pub fn new(
        real: f64,
        imag: f64,
    ) -> Self {
        Self {
            real,
            imag,
        }
    }
    pub fn abs_square(
        self
    ) -> f64 {
        self.real * self.real + self.imag * self.imag
    }
    pub fn argument(
        self
    ) -> f64 {
        self.imag.atan2(self.real)
    }
    pub fn recip(
        self
    ) -> Self {
        let denom = self.abs_square();
        Self::new(self.real / denom, -self.imag / denom)
    }
}

impl From<f64> for Complex 
{
    fn from(
        real: f64
    ) -> Self {
        Self::new(real, 0.0)
    }
}

impl Add for Complex 
{
    type Output = Self;
    fn add(
        self,
        other: Self
    ) -> Self {
        Self::new(self.real + other.real, self.imag + other.imag)
    }
}
impl Sub for Complex 
{
    type Output = Self;
    fn sub(
        self,
        other: Self
    ) -> Self {
        Self::new(
            self.real - other.real, 
            self.imag - other.imag,
        )
    }
}

impl Mul for Complex
{
    type Output = Self;
    fn mul(
        self, 
        other: Self
    ) -> Self {
        let real = self.real * other.real - self.imag * other.imag;
        let imag = self.imag * other.real + self.real * other.imag;
        Self::new(real, imag)

    }
}
impl Div for Complex 
{
    type Output = Self;
    fn div(
        self,
        other: Self
    ) -> Self {
        self * other.recip()
    }
}
impl Neg for Complex
{
    type Output = Self;
    fn neg(
        self
    ) -> Self {
        Self::new(-self.real, -self.imag)
    }
}

#[derive(Copy, Clone, Debug)]
pub struct Modulo<const M: i64>
{
    pub val: i64,
}
impl<const M: i64> Modulo<M>
{
    pub fn pow(
        mut self, 
        mut n: u64,
    ) -> Self {
        let mut result = Self::from_small(1);
        while n > 0 {
            if n % 2 == 1 {
                result = result * self;
            }
            self = self * self;
            n /= 2;
        }
        result 
    }
    pub fn vec_of_recips(
        n: i64
    ) -> Vec<Self> {
        let mut recips = vec![Self::from(0), Self::from(1)];
        for i in 2..=n {
            let (md, dv) = (M % i, M / i);
            recips.push(recips[md as usize] * Self::from_small(-dv));
        }
        recips
    }
    pub fn from_small(
        s: i64
    ) -> Self {
        let val = if s < 0 { s + M } else { s };
        Self { val }
    }
    pub fn recip(
        self
    ) -> Self {
        // println!("M: {:?}", M);
        self.pow(M as u64 - 2)
    }
    
}

impl<const M: i64> From<i64> for Modulo<M>
{
    fn from(
        val: i64
    ) -> Self {
        Self::from_small(val % M)
    }
}
impl<const M: i64> Add for Modulo<M>
{
    type Output = Self;
    fn add(
        self, 
        other: Self
    ) -> Self {
        Self::from_small(self.val + other.val - M)
    }
}
impl<const M: i64> Sub for Modulo<M>
{
    type Output = Self;
    fn sub(
        self,
        other: Self
    ) -> Self {
        Self::from_small(self.val - other.val)
    }
}
impl<const M: i64> Mul for Modulo<M>
{
    type Output = Self;
    fn mul(
        self,
        other: Self,
    ) -> Self {
        Self::from(self.val * other.val)
    }
}
impl<const M: i64> Div for Modulo<M>
{
    type Output = Self;
    fn div(
        self,
        other: Self
    ) -> Self {
        self * other.recip()
    }
}
pub const COMMON_PRIME: i64 = 998_244_353;
pub type CommonField = Modulo<COMMON_PRIME>;

#[derive(Debug)]
pub struct Matrix
{
    pub cols: usize,
    pub inner: Box<[f64]>,
}
impl Matrix
{
    pub fn zero(
        rows: usize,
        cols: usize,
    ) -> Self {
        let inner = vec![0.0; rows * cols].into_boxed_slice();
        Self { cols, inner }
    }
    pub fn one(
        cols: usize
    ) -> Self {
        let mut matrix = Self::zero(cols, cols);
        for i in 0..cols {
            for j in 0..cols {
                matrix.inner[i * cols + j] = 1.0;
            }
        }
        matrix
    }
    pub fn vector(
        vec: &[f64],
        as_row: bool
    ) -> Self {
        let cols = if as_row { vec.len( ) } else { 1 };
        let inner = vec.to_vec().into_boxed_slice();
        Self { cols, inner }
    }
    pub fn rows(
        &self
    ) -> usize {
        self.inner.len() / self.cols
    }
}
impl Index<usize> for Matrix 
{
    type Output = [f64];
    fn index(
        &self,
        row: usize
    ) -> &Self::Output {
        let start = self.cols * row;
        &self.inner[start..start + self.cols]
    }
}
impl IndexMut<usize> for Matrix 
{
    fn index_mut(
        &mut self, 
        row: usize
    ) -> &mut Self::Output {
        let start = self.cols * row;
        &mut self.inner[start..start + self.cols]
    }
}