use super::num::{
    CommonField,
    Complex,
    PI,
};

struct BitRevIterator 
{
    a: usize,
    n: usize,
}
impl BitRevIterator
{
    fn new(
        n: usize
    ) -> Self {
        assert!(n.is_power_of_two());
        Self { a: 2 * n - 1, n}
    }
}

pub trait FFT: Sized + Copy
{
    type F: Sized
        + Copy
        + From<Self>
        + Neg
        + Add<Output = Self::F>
        + Div<Output = Self::F>
        + Mul<Output = Self::F>
        + Sub<Output = Self::F>;

    const ZERO: Self;

    fn get_roots(
        n: usize,
        inverse: bool
    ) -> Vec<Self::F>;

    fn get_factor(
        n: usize,
        inverse: bool
    ) -> Self::F;

    fn extract(
        f: Self::F
    ) -> Self;
}
impl FFT for f64 
{
    type F = Complex;
    
    const ZERO: f64 = 0.0;

    fn get_roots(
        n: usize,
        inverse: bool
    ) -> Vec<Self::F> {
        let step = if inverse { -2.0 } else { 2.0 } * PI / n as f64;
        (0..n / 2)
            .map( |i| Complex::from_polar(1.0, step * i as f64))
            .collect()
    }
}
pub fn dft_from_reals<T: FFT>(
    v: &[T],
    desired_len: usize,
) -> Vec<T::F> {
    assert!(v.len() <= desired_len);

    let complex_v = v
                    .iter()
                    .cloned()
                    .chain(std::iter::repeat(T::ZERO))
                    .take(desired_len.next_power_of_two())
                    .map(T::F::from)
                    .collect::<Vec<_>>();
    fft::<T>(&complex_v, false)
}