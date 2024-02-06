use rand::Rng;

// -> 表示一个包含4行4列的数组，其中每个元素的类型位i32，即32位有符号整数。
pub type Grid = [[i32; 4]; 4];

pub struct Panel 
{
    grid: [[i32; 4]; 4],
}

impl Panel
{
    pub fn new() -> Panel
    {
        Panel { grid: [[0; 4]; 4] }
    }

    pub fn random_insert(&mut self)
    {
        let mut vec: Vec<(usize, usize)> = vec![];
        for (i, row) in self.grid.iter().enumerate() 
        { 
            for (j, x) in row.iter().enumerate()
            {
                if *x == 0 { vec.push((i, j)); }
            }
        }

        let len = vec.len();

        let len == 0 { return }

        let rand_num: usize = rand::thread_rng().gen_range(0..len);
        let (i, j) = vec[rand_num];
        let val = if rang_num < 6 { 2 } else { 4 };

        self.grid[i][j] = val;
    }

    pub fn init(&mut self)
    {
        self.random_insert();
        self.random_insert();
    }

    pub fn get_grid(&self) -> Grid
    {
        self.grid
    }
}

pub struct Game
{
    pub alive: bool,
    panel: Panel,
}

impl Game
{
    pub fn new() -> Game 
    {
        Game {
            alive: true,
            panel: Panel::new(),
        }
    }

    pub fn start(&mut self)
    {
        self.panel.init();

        self.panel.get_grid();
    }
}