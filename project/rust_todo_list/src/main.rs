mod database;


use std::env;   // 使用标准库中的env::args()方法获取命令行参数
use database::Database;

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
    let mut db = Database::open(".rodorc");
    match command.as_str()
    {
        "add" => {
            if args.len() < 3
            {
                println!("Usage: rodo add [contents]");
                return ;
            }
            let contents = &args[2..].join(" ");
            /*
                · db.read_records(): 调用数据库db的read_records方法
                · .last(): 调用向量的last方法，返回向量中的最后一个元素
                · .map(|r| r.id + 1): 对获取的最后一条记录应用map方法，将其id值加一
                · .unwrap_or(1): 对Option类型的值应用unwrap_or方法，如果存在值则返回该值，否则返回提供的默认值1
             */
            let id = db.read_records().last().map(|r| r.id + 1).unwrap_or(1);
            db.add_record(&database::Record {
                id,
                content: contents.to_string(),
            });
        }
        "rm" => {
            if args.len() < 3 
            {
                println!("Usage: rodo rm [id]");
                return ;
            }
            let id = args[2].parse::<i32>().unwrap();
            db.remove_record(id);
        }
        "ls" => {
            println!("List");
            let records = db.read_records();
            if records.is_empty()
            {
                println!("No records. You can add one with `rodo add [content]`");
                return ;
            }
            for record in records
            {
                println!(" ⬜️ {}: {}", record.id, record.content);
            }
        }
        _ => {
            println!("Unknown command: {}", command);
        }
    }
}
