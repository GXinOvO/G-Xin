
pub struct SuffixArray 
{
    pub sfx: Vec<usize>,

    pub rank: Vec<Vec<usize>>,
}

impl SuffixArray
{
    pub fn new(text: impl IntoIterator<Item = u8>) -> Self
    {
        
    }
}

fn main()
{
    let text1 = "bobocel";
    let text2 = "banana";

    let sfx1 = SuffixArray::new(text1.bytes());
    let sfx2 = SuffixArray::new(text2.bytes());
}