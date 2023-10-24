/*
    创建了一个Cli结构体，用到#[derive(Parser)]来为Cli结构体实现Parser trait，这样就可以
  使用Cli::parse()方法来解析命令行参数了。注意要在Cargo.toml中添加features = ["derive"]

    #[clap(version, about)]: 会输出我们在Cargo.toml中定义的version和about字段
    #[clap(propagate_version = true)]: 会将version信息传递给子命令
    #[clap(subcommand)]会将Commands枚举中的所有命令作为子命令
    创建一个Commands枚举，用来表示不同的命令
    #[clap(about = "xxx")]: 会输出命令的相关说明
    #[clap(help = "xxx")]会输出命令的帮助信息
    #[clap(visible_aliases = &["xxx"])]: 会为命令添加别名
*/

use clap::{Parser, Subcommand};

#[derive(Parser)]
#[clap(version, about)]
#[clap(propagate_version = true)]
pub struct Cli
{
    #[clap(subcommand)]
    pub command: Commands,
}

#[derive(Debug, Subcommand)]
pub enum Commands 
{
    #[clap(about = "Show rodo info.")]
    Info,

    #[clap(about = "Add a todo item.")]
    Add {
        #[clap(help = "The item content to add.")]
        content: Option<String>,
    },

    #[clap(about = "Remove a todo item.")]
    #[clap(visible_aliases = &["rm"])]
    Remove {
        #[clap(help = "The item id to remove.")]
        id: Option<String>,
    },

    #[clap(about = "List all the todo items.")]
    #[clap(visible_aliases = &["ls", "ll", "la"])]
    List,
}