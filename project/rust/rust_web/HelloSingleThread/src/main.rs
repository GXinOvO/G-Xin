// -> net用于处理网络相关的功能， TcpListener是net模块中的一个结构体，用于创建和管理TCP连接的监听器。
// TcpListener结构体的作用是监听指定的网络地址，等待客户端发起连接。
use std::net::TcpListener;

fn main()
{
    // 监听地址: 127.0.0.1:7878     bind()将实例绑定到此地址端口上
    // -> unwrap()可以获取成功绑定的TclListener实例，如果绑定失败，unwrap会产生一个panic
    let listener = TcpListener::bind("127.0.0.1:7878").unwrap();

    // -> incoming()返回一个迭代器，他每一次迭代都会返回一个新的连接stream(客户端发起，web服务器监听接受)
    for stream in listener.incoming()
    {
        // -> 这里及逆行unwrap()处理，原因在于我们并不是在迭代一个一个连接，而是在迭代处理一个一个请求建立连接的尝试，而这种尝试可能会失败！
        let stream = stream.unwrap();

        println!("Connection established!");
    }
}