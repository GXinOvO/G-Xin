/*
    --TODO: Rust并发编程
        安全高效的处理并发是Rust诞生的目的之一，主要解决的是服务器高负载承受能力
        并发(concurrent)的概念是指程序不同的部分独立执行，这与并行(parallel)的概念容易
      混淆，并行强调的是"同时执行"。并发往往会造成并行。


    --TODO: 线程
        线程(thread)是一个程序中独立运行的一个部分。
        线程不同于进程(process)的地方是线程是程序以内的概念，程序往往是在一个进程中执行的。
        在有操作系统的环境中进程往往被交替地调度得以执行，线程则在进程以内由程序进行调度。
        由于线程并发很有可能出现并行的情况，所以在并行中可能遇到的死锁、延宕错误常出现于含
      有并发机制的程序
        为了解决这些问题，很多其他语言(如Java、C#)采用特殊的运行时(runtime)软件来协调资源，但这样
      无疑极大地降低了程序的执行效率。
        C/C++语言在操作系统的最底层也支持多线程，且语言本身以及其编译器不具备侦察和避免并行错误的
      能力，这对于开发者来说压力很大，开发者需要花费大量的精力避免发生错误。
        Rust不依靠运行时环境，这一点像C/C++一样。
        但Rust在语言本身就设计了包括所有权机制在内的手段来尽可能地把最常见的错误消灭在编译阶段，
      这一点其他语言不具备。但这不意味着我们编程的时候可以不小心，迄今为止由于并发造成的问题还没有在
      公共范围内得到完全解决，仍有可能出现错误，并发编程时尽量新校


        Rust中通过std::thread::spawn函数创建新线程
*/
use std::thread;
use std::time::Duration;

fn spawn_function()
{
  for i in 0..5 
  {
    println!("spawned thread print {}", i);
    thread::sleep(Duration::from_millis(1));
  }
}

fn main()
{
  thread::spawn(spawn_function);

  for i in 0..3
  {
    println!("main thread print {}", i);
    thread::sleep(Duration::from_millis(1));
  }
}