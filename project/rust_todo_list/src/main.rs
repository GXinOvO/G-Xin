use std::env;   // 使用标准库中的env::args()方法获取命令行参数

fn main() {
    /* 
        --TODO: 获取命令行参数
            · env::args() 是一个函数调用，返回一个迭代器，产生命令行参数的字符串
            · .collect() 是一个迭代器适配器，将迭代器的元素收集到一个集合中。在这种情况下，迭代器产生的字符串被收集到一个Vec<String>中
            · let args: Vec<String> = 是一个变量绑定的语法，将右侧表达式的结果赋值给args变量。这在里，args被声明为Vec<String>的变量
    */
    let args: Vec<String> = env::args().collect();

    // -> 如果没有参数: 输出提示信息
    if args.len() < 2
    {
        println!("Usage: rodo [add | rm | ls] [args]");
        return ;
    }

    let command = &args[1];
    match command.as_str()
    {
        
    }
}
