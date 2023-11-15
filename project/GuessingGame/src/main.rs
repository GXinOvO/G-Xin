use std::io;
use std::cmp::Ordering;
use rand::Rng;

fn main() {
    println!("Guess the number!");

    /*
    --TODO: 随机数
        rand::thread_rng函数提供实际使用的随机数生成器: 它位于当前执行线程的本地环境中，
      并从操作系统获取seed。接着调用随机数生成器的gen_range方法。这个方法由use rand::Rng
      语句引入到作用域的Rng trait定义。gen_range方法获取一个范围表达式(range expression)
      作为参数，并生成一个在此范围之间的随机数。
     */

    /*
    注意:
        你不可能凭空就知道应该use哪个trait以及该从crate中调用哪个方法，因此每个crate由使用
      说明文档。Cargo有一个很棒的功能是: 运行cargo doc --open命令来构建所有本地依赖提供的
      文档，并在浏览器中打开。
     */
    let secret_number = rand::thread_rng().gen_range(1..=100);

    println!("Please input your guess.");

    let mut guess = String::new();

    io::stdin()
        .read_line(&mut guess)
        .expect("Failed to read line");
    
    println!("You guessed: {guess}");

    let x = 5;
    let y = 10;

    println!("x = {x} and y + 2 = {}", y + 2);

    match guess.cmp(&secret_number)
    {
        Ordering::Less => println!("Too small!"),
        Ordering::Greater => println!("Too big!"),
        Ordering::Equal => println!("You win!"),
    }
}
