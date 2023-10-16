/*
  --TODO: error
    Rust有一套独特的处理异常情况的机制，他并不像其他语言中的try机制那样简单。
    首先，程序中一般会出现两种错误: 可恢复错误和不可恢复错误。
    可恢复错误的典型案例是文件访问错误，如果访问一个文件失败，有可能是因为它正在
  被占用，是正常的，我们可以通过等待来解决。
    但还有一种错误是由编程中无法解决的逻辑错误导致的，例如访问数组末尾以外的位置。
    大多数编程语言不区分这两种错误，并用Exception(异常)类来表示错误，在Rust种没有Exception
    对于可恢复错误用Result<T, E>类来处理，对于不可恢复错误使用panic!宏来处理
 */

 fn main()
 {
     /* 
         程序是无法运行到println!，而是在panic!宏被调用时停止了运行
         不可恢复的错误一定会导致程序收到致命的打击而终止运行
     thread 'main' panicked at 'error occured', src\main.rs:3:5
     note: run with `RUST_BACKTRACE=1` environment variable to display a backtrace.
         第一行输出了panic!宏调用的位置以及其输出的错误信息
         第二行是一句提示，翻译成中文就是 "通过'RUST_BACKTRACE=1'环境变量运行以显示回溯"
 
         RUST_BACKTRACE=1 cargo run
      */
     panic!("error occured");
     println!("Hello, Rust");
    /*
        回溯是不可恢复错误的另一种方式，他会展开运行的栈并输出所有的信息，然后程序依然会退出。
      */
 }