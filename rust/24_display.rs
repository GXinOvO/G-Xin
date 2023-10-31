/*
--TODO: 显示
    fmt::Debug通常看起来不太简介，因此自定义输出的外观经常使更可取的。这需要通过手动
  实现fmt::Display来做到。fmt::Display采用{}标记。
*/

// -> 使用use导入fmt模块使 fmt::Display 可用
use std::fmt;

struct Structure(i32);

impl fmt::Display for Structure
{
    // 这个trait要求`fmt`使用与下面的函数完全一致签名
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result
    {
        // 仅将self的第一个元素写入到给定的输出流f。返回fmt::Result，此
        // 结果表明操作成功或失败
        write!(f, "{}", self.0)
    }
}