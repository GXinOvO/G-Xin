use std::error::Error;
use std::fs;

pub struct Config
{
    pub query: String,
    pub file_path: String,
}


/*
    Result<(), Box<dyn Error>>返回类型，首先我们的程序无需返回任何值，但是为了满足Result<T, E>的要求，因此使用了Ok(())返回一个单元类型()。
    这是一个Error的特征对象，表hi是函数返回一个类型，该类型实现了Error特征，这样我们就无需指定具体的错误类型，否则还需要查看fs::read_to_string
  返回的错误类型，然后复制到我们的run函数返回中，这么做一个是麻烦，最主要的是，一旦这么做，意味着我们无法在上层调用时统一处理错误，但是
  Box<dyn Error>不同，其他函数也可以返回这个特征对象，然后调用者就可以使用同一的方式来处理不同函数返回的Box<dyn Error>

    Box<dyn Error>表示失败时返回一个堆分配的实现了Error trait的错误对象。Error trait时Rust标准库中定义的用于表示错误的trait，它提供了错误
  类型应该具备的一些功能。Box<dyn Error>表示一个动态分发的错误类型，可以容纳任意实现了Error trait的具体类型的错误对象。
*/
pub fn run(config: Config) -> Result<(), Box<dyn Error>>
{
    /* 
    // -> std::fs引入文件操作包，然后通过fs::read_to_string读取指定的文件内容，最后返回的contents
    //std::io::Result<String>类型
    // -> expect()接受一个字符串参数，该字符串将作为panic的错误消息显示。如果操作成功，expect返回成功的值
    //如果操作失败，他将引发一个panic，并显示提供的错误消息。
    let contents = fs::read_to_string(config.file_path)
                    .expect("Should have been able to read the file");
    
    --TODO: 
        我们同样希望 错误处理最好同意在一个地方完成，这样极其有利于后续的代码维护。
    */
    // -> ?运算符用于处理可能得错误，如果在读取文件时发生错误，它会立即返回错误并当前函数的执行
    let contents = fs::read_to_string(config.file_path)?;

    for line in search(&config.query, &contents)
    {
        println!("{line}");
    }
    // println!("With text:\n{contents}");

    // Ok(())是一种特殊情况，其中()是Rust中的单元类型(unit type)，表示一个不包含任何有用信息的值。在某些情况下，
    //当操作成功但不需要返回实际值时，可以使用Ok(())作为成功的结果
    Ok(())
}

// -> Config中存储的并不是&str这样的引用类型，而是一个String字符串，也就是Config并没有去
//借用外部的字符串，而是拥有内部字符串的所有权。

/*
-- TODO：clone的得与失
    除了使用clone，还有其他办法来达到同样的目的，单clone无疑是最简单的方法: 直接完整的复制目标数据，无需被所有权、
  借用等问题所困扰，但是他也有其缺点，那就是有一定的性能损耗。
    因此是否使用clone更多是一种性能上的权衡，对于上面的使用而言，由于是配置的初始化，因此整个程序只需要执行一次，
  性能损耗几乎是可以忽略不计的。

总之，判断是否使用clone:
    · 是否严肃的项目，玩具项目直接用`clone`就行，简单不好吗？
    · 要看所在的代码路径是否是热点路径(hot path)，例如执行次数较多的显然就是热点路径，热点路径就值得去使用性能更好
    的实现方式

fn parse_config(args: &[String]) -> Config
{
    let query = args[1].clone();
    let file_path = args[2].clone();

    Config {query, file_path}
}
*/
// -> 通过构造函数来初始化一个Config实例
impl Config
{
    /* 
    --TODO: 
        fn new(args: &[String]) -> Config
    {
        if args.len() < 3
        {
            panic!("not enough arguments");
        }
        
        panic对于使用用户并不是一个友好的信息，它更适合开发者。
        所以，我们可以返回一个Result。
    但有一点需要额外注意下，从代码惯例的角度出发，new往往不会失败，毕竟新建一个实例没道理失败，因此修改为build更合适

    */
    pub fn build(args: &[String]) -> Result<Config, &'static str> 
    {
        if args.len() < 3
        {
            return Err("nor enough arguments");
        }
        let query = args[1].clone();
        let file_path = args[2].clone();

        Ok(Config { query, file_path })
    }
}

pub fn search<'a>(query: &str, contents: &'a str) -> Vec<&'a str> 
{
    let mut results = Vec::new();
    // -> 一个字符串切片的方法，用于按行迭代字符串内容。
    for line in contents.lines()
    {
        // -> 检查看这一行是否包含查询字符串query
        if line.contains(query) 
        {
            results.push(line);    
        }
    }
    results
}

#[cfg(test)]
mod tests 
{
    use super::*;

    #[test]
    fn one_result()
    {
        let query = "duct";
        let contents = "\
Rust:
safe, fast, productive.
Pick three.";

        assert_eq!(vec!["safe, fast, productive."], search(query, contents));
    }
}