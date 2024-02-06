use crate::game::{Game, Grid};

pub struct App 
{
    pub x: f64,
    pub y: f64,
    pub box_size: f64,
    game: Game,
    queue: Vec<Command>,
    score: i32,
}

impl App 
{
    pub fn new() -> App
    {
        let game = Game::new();
        let mut app = App {
            x: 0.0,
            y: 0.0,
            box_size: 40.0,
            game,
            queue: Vec::new(),
            score: 0
        };

        app.game.start()

        app        
    }
}