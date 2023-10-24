/*
    --TODO: File
        · File: 表示文件句柄，用于进行文件的读取和写入操作。
        · Open Options: 结构体，用于配置文件的打开选项
*/

use std::fs::{File, OpenOptions};
use std::io::{BufRead, BufReader, Seek, Write};

// -> 存放数据 
pub struct Record 
{
    pub id: i32,
    pub content: String,
}

// -> 数据库
pub struct Database
{
    pub file: File,
}

// -> 解析记录行
pub fn parse_record_line(line: &str) -> Record 
{
    let fields: Vec<&str> = line.split(',').collect();

    // 处理空行的情况
    if fields.len() == 1
    {
        return Record {
            id: 0,
            content: "".to_string(),
        };
    }

    let content = fields[1..].join(",");
    // -> parse::<i32>() 这是一个字符串解析方法，用于将字符串解析为指定的类型。
    Record {
        id: fields[0].parse::<i32>().unwrap(),
        content,
    }
}


// -> 为Database 实现一个open方法，参数接收一个文件名，返回一个Database实例
impl Database 
{
    // 打开数据库文件
    pub fn open(filename: &str) -> Database
    {
        let file = OpenOptions::new()
                    .create(true)
                    .read(true)
                    .write(true)
                    .open(filename)
                    .unwrap();
        Database { file }

    }

    pub fn add_record(&mut self, record: &Record) -> Result<(), std::io::Error>
    {
        let line = format!("{}, {}\n", record.id, record.content);
        writeln!(self.file, "{}", line).unwrap();
        println!(" Item added: {}", record.content);
    }

    // -> 删除记录
    pub fn remove_record(&mut self, id: i32) -> Result<(), std::io::Error>
    {
        // 使用BufReader读取文件
        let reader = BufReader::new(&self.file);
        // -> 将BufReader的lines方法返回的迭代器使用enumerate方法进行索引标记，以便我们可以跟踪行号。
        let mut lines = reader.lines().enumerate();
        // 根据id找出对应的行
        /*
            · let line = lines.find();: 使用find方法在迭代器中查找满足条件的元素
            · |(_, line)| {...}: 闭包表达式，接受一个元组参数，包含迭代器中的索引和行内容
            · let record: 将行内容解析为Record结构体，前提是行内容不为空
            .as_ref().unwrap()对line进行空值检查
         */
        let line = lines.find(|(_, line)| {
            let record = parse_record_line(line.as_ref().unwrap());
            record.id == id
        });
        match line
        {
            Some((i, _)) =>
            {
                // 读取源文件内容
                let contents = std::fs::read_to_string(".rodorc").unwrap();

                /*  
                    过滤掉对应的行，这里使用的对应API可以查看Rust标准库

                    并将剩余行长信组合成一个新的字符串new_contents

                    · content.lines(): 将字符串content按行拆分为一个迭代器，每个迭代项时字符串的一行
                    · .enumerate(): 对行的迭代器使用enumerate方法，将每行与其索引配对
                    · .filter(|(j, _)| *j != i): 使用filter方法过滤掉索引值等于i的行，保留其他行
                    · .map(|(_, line)| line): 对剩余的每一行应用map方法，将元组解构，只保留行的内容
                    · .collect::<Vec<_>>(): 将处理后的行内容收集到一个Vec向量中
                    · .join("\n"): 使用\n将向量中的行内容连接成一个新的字符串

                    使用类型推断(::<_>)来指定收集到的向量类型，根据上下文自动推断为Vec<String>.
                */
                let new_contents = contents
                                    .lines()
                                    .enumerate()
                                    .filter(|(j, _)| *j != i)
                                    .map(|(_, line)| line)
                                    .collect::<Vec<_>>()
                                    .join("\n");

                // 将新的内容写入到源文件中
                /*
                    self.file.seek():: 通过调用文件的seek方法，将文件指针移动到文件的开头位置(0)
                    self.file.write_all(new_contents.as_bytes()): 通过调用文件的write_all方法，将new_contents字符串的字节写入文件
                    self.file.set_len(new_contents.len() as u64): 通过调用文件的set_len方法，设置文件的长度为new_contents字符串的长度。
                 */
                self.file.seek(std::io::SeekFrom::Start(0)).unwrap();
                self.file.write_all(new_contents.as_bytes()).unwrap();
                self.file.set_len(new_contents.len() as u64).unwrap();

                println!(" ❌ Item removed!\n");
                Ok(())
            }
            None => Err(std::io::Error::new(
                std::io::ErrorKind::Other,
                format!("No such record: {}", id),
            )),
        }
    }

    pub fn read_records(&mut self) -> Vec<Record> 
    {
        // -> 创建一个BufReader实例，用于从文件中读取数据。BufReader是一个带有缓冲区的读取器，可以提供更高效的文件读取。
        let reader = BufReader::new(&self.file);
        /* 
            .lines(): 调用BufReader的lines方法，返回一个迭代器，该迭代器产生文件的每一行
            .map_while(): 将迭代器中的每个元素转换为Result类型并通过Result::ok过滤掉产生错误的元素。这将返回一个仅包含成功结果的迭代器
            .filter(|line| !line.is_empty()): 使用filter方法，过滤掉迭代器中空行的元素
            .map(|line| parse_record_line(&line)): 对剩下的每一行应用parse_record_line函数，将每行解析为Record结构体。
            .collect(): 将经过处理的元素收集到一个Vec<Record>向量中
        */
        reader.lines()
            .map_while(Result::ok)
            .filter(|line| !line.is_empty())
            .map(|line| parse_record_line(&line))
            .collect()
    }
}