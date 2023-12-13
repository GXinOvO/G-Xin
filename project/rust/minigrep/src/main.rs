use std::env;
use std::process;

use minigrep::Config;

fn main() {
    // -> 通过use引入标准库的env包，然后env::args方法会读取并分析传入的命令行参数，最终通过collect
    // 方法输出一个集合类型Vector

/* 
    // -> collect()方法并不是std::env包提供的，而是迭代器自带的方法(env::args()会返回一个迭代器)
    let args: Vec<String> = env::args().collect();

    // -> unwrao_or_else() 是定义在Result<T, E>上的常用方法，如果Result是Ok，那该方法就类似unwrap: 返回Ok内部的值
    //如果是Err，就调用闭包中的自定义代码对错误进行进一步处理。
    let config  = Config::build(&args).unwrap_or_else(|err| {

    由于env::args可以直接返回一个迭代器，再作为Config::build的参数传入
*/   
    let config = Config::build(env::args()).unwrap_or_else(|err|)
    {
        eprintln!("Problem parsing arguments: {err}");
        // -> 用于退出程序并返回指定的退出码的函数调用，会立即终止程序的执行。
        process::exit(1);
    });

    println!("Searching for {}", config.query);
    println!("In file {}", config.file_path);

    // -> 我们并不关注run返回的Ok值，因此只需要用if let去匹配是否存在错误即可
    if let Err(e) = minigrep::run(config)
    {
        eprintln!("Application error: {e}");
        process::exit(1);
    };

    // dbg!(&args);
}