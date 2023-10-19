/*
    --TODO: Rust集合与字符串
        集合(Collection)是数据结构中最普遍的数据存放形式，Rust标准库中提供了丰富的集合类型
      帮助开发者处理数据结构的操作。

    --TODO: 向量
        向量(Vector)是一个存放多值的单数据结构，该结构将相同类型的值线性的存放在内存中。
        向量是线性表，在Rust中的表示是Vec<T>
        向量的使用方式类似于列表(List)，我们可以通过以下方式创建指定类型的向量:

    let vector: Vec<i32> = Vec::new();
    let vector = vec![1, 2, 3, 4];
*/


// -> 使用线性表常常会用到追加操作，但是追加和栈的push操作本质是一样的，所以向量只有push方法来追加单个元素:
fn main()
{
    let mut vector = vec![1, 2, 4, 8];
    vector.push(16);
    vector.push(32);
    vector.push(64);
    println!("{:?}", vector);

    /*
        --TODO: 
            append方法用于将一个向量拼接到另一个向量的尾部
     */
    let mut v1: Vec<i32> = vec![1, 2, 4, 8];
    let mut v2: Vec<i32> = vec![16, 32, 64];
    v1.append(&mut v2);
    println!("{:?}", v1);

    /*
        --TODO:
            get方法用于取出向量中的值

            因为向量的长度无法从逻辑上推断，get方法无法保证一定取到值，所以get方法的返回值是Option枚举类，有可能为空。
          这是一种安全的取值方法，但是书写起来有些麻烦。如果能够保证取值的下标不会超出向量下标取值范围，也可以使用
          数组取值语法
     */
    let mut v = vec![1, 2, 4, 8];
    println!("{}", match v.get(2) {
        Some(value) => value.to_string(),
        None => "None".to_string()
    });

    let b = vec![1, 2, 4, 8];
    println!("{}", v[1]);

    /*
        --TODO:
            如果遍历过程中需要更改变量的值
     */
    let mut z = vec![100, 32, 57];
    for i in &mut z 
    {
        *i += 50;
    }
    println!("z = {:?}", z);


    /*
        --TODO: 字符串
     */
    let string = String::new();

    // -> 基础类型转换成字符串
    let one = 1.to_string();            // 整数到字符串
    let float = 1.3.to_string();        // 浮点数到字符串
    let slice = "slice".to_string();    // 字符串切片到字符串    

    let mut s = String::from("run");
    s.push_str("oob");
    s.push('!');

    println!("s = {}", s);
}