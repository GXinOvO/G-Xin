mod event;

use std::{
    error::Error, 
    io,
    thread,
    time::Duration
};

#[allow(dead_code)]
use termion::{
    raw::IntoRawMode, 
    screen::AlternateScreen, 
    input::MouseTerminal
};

use tui::{
    backend::CrosstermBackend,
    Terminal
};

use crossterm::{
    event::{
        EnableMouseCapture,
        DisableMouseCapture,
    },
    execute,
    terminal::{
        disable_raw_mode,
        enable_raw_mode,
        EnterAlternateScreen,
        LeaveAlternateScreen,
    },
};

use event::{
    Config,
    Events,
    Event,
};

fn main() -> Result<(), Box<dyn Error>>
{
    enable_raw_mode()?;
    let mut stdout = io::stdout();
    
    /*
        · execute!: 用于执行一系列终端操作的宏，可以帮助我在终端中执行多个操作
        · EnterAlternateScreen: 将终端切换到备用屏幕模式
        · EnableMouseCapture: 启用了鼠标捕获功能
     */
    execute!(
        stdout, 
        EnterAlternateScreen, 
        EnableMouseCapture
    )?;
    // let stdout = MouseTerminal::from(stdout);
    // let stdout = AlternateScreen::from(stdout);
    let backend = CrosstermBackend::new(stdout);
    let mut terminal = Terminal::new(backend)?;

    let config = Config {
        tick_rate: Duration::from_millis(250),
        ..Default::default()
    };
    
    let events = Events::with_config(config);
    // thread::sleep(Duration::from_millis(5000));

    let mut app = App::new();

    disable_raw_mode()?;
    execute!(
        terminal.backend_mut(),
        LeaveAlternateScreen,
        DisableMouseCapture,
    )?;

    terminal.show_cursor()?;

    Ok(())
}