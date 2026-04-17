#include<iostream>
#include<muduo/net/TcpServer.h>
#include<muduo/net/EventLoop.h>
#include<functional>
#include<string>
using namespace std;
using namespace muduo;
using namespace muduo::net;
using namespace std::placeholders;

/*基于muduo网络开发库开发服务器程序
1.组合TcpServer对象
2.创建EventLoop事件循环对象的指针
3.明确TcpServer构造函数需要什么参数，输出ChatServer的构造函数
4.在当前服务器类的构造函数中，注册处理连接的回调函数和处理读写事件的回调函数
5.设置合适的服务器端线程数量，muduo库会自己分配连接线程和读写线程
*/

class ChatServer{
public:
        ChatServer(EventLoop* loop,                 //事件循环，相当于epoll树根epfd
        const InetAddress& listenAddr,              //IP+Port，socket+socketaddr
        const string& nameArg)                      //服务器的名字
        :_server(loop, listenAddr, nameArg){
        //给服务器注册用户连接的创建和断开回调
        _server.setConnectionCallback(bind(&ChatServer::onConnection, this, _1));
        //给服务器注册用户读写事件回调
        _server.setMessageCallback(bind(&ChatServer::onMessage, this, _1, _2, _3));
        //设置服务器端的线程数量 1个I/O线程，其他worker线程
        _server.setThreadNum(4);
}
        //开启事件循环   
        void start() {
                _server.start();
        }    
           
private:
        //专门处理用户的连接创建和断开 epoll listen accept
        void onConnection(const TcpConnectionPtr& conn){
                if(conn->connected()){
                        cout<<conn->peerAddress().toIpPort()<<"->"
                        <<conn->localAddress().toIpPort()<<" state:online"<<endl;
                }else{
                        cout<<conn->peerAddress().toIpPort()<<"->"
                        <<conn->localAddress().toIpPort()<<" state:offline"<<endl;
                        conn->shutdown();//close(fd)
                        // _loop->quit(); //直接关闭epoll树，free(epfd)
                }
        }
        //专门处理读写事件
        void onMessage(const TcpConnectionPtr& conn,    //连接
                            Buffer* buffer,             //缓冲区
                            Timestamp receiveTime){     //接收到数据的时间信息
                string buf = buffer->retrieveAllAsString();
                cout<<"recv data:"<<buf<<"time:"<<receiveTime.toString()<<endl;
                conn->send(buf);
        }
        TcpServer _server;// #1
        // EventLoop *_loop; // #2 epoll
};

int main(){
        EventLoop loop;
        InetAddress addr("127.0.0.1", 6666);
        ChatServer server(&loop, addr, "ChatServer");

        server.start(); //
        loop.loop();    //epoll_wait()以阻塞方式等待新用户的连接，已连接用户的速写时间等操作
        return 0;
}

