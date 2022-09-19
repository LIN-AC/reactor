/*
 * @Author: cell_lin 1335954640@qq.com
 * @Date: 2022-09-19 21:43:29
 * @LastEditors: cell_lin 1335954640@qq.com
 * @LastEditTime: 2022-09-19 21:58:20
 * @FilePath: /Linux/tcpv2/tcp/bin/test.cc
 * @Description:
 *
 * Copyright (c) 2022 by cell_lin 1335954640@qq.com, All Rights Reserved.
 */
#include "../include/tcpconnection.hh"
#include "../threadpool/threadpool.hh"
#include "../include/tcpserver.hh"
#include <iostream>
#include <unistd.h>

using namespace std;
using namespace yuki;

Threadpool *threadpool = nullptr;

class MyTask
{
public:
    MyTask(const string &msg, const TcpConnectionPtr &con)
        : _msg(msg), _con(con)
    {
    }
    void process()
    {
        //在_msg此处进行消息的处理
        //....
        //....
        // msg1
        //真正进行数据收发的肯定是原始的read和write，但是这两个被SockIO
        //进行了封装，被TcpConnection封装起来了(在V1版本中TcpConnection)
        //具有收发数据的能力,而到了V2版本中TcpConnection的创建在EventLoop
        //类中，EventLoop具有收发数据的能力.
        //在此处需要将数据的收发交给EventLoop/Reactor进行处理
        //数据收发也就是IO操作，所以可以将EventLoop称为IO线程
        //而线程池引进来的目的就是做也业务逻辑的处理，也就是做计算，将
        //做计算的线程称为计算线程
        //需要将数据的发送任务从计算线程交给IO线程,会涉及到IO线程与计算线程
        //进行通信(需要学习线程之间进行通信的方式eventfd)
        _con->send_loop(_msg);
        //数据的发送转到TcpConnection，TcpConnection需要将消息转给EventLoop
        // TcpConnection需要知道EventLoop的一个存在，关联关系
    }

private:
    string _msg;
    TcpConnectionPtr _con;
};

void onConnection(const TcpConnectionPtr &con)
{
    cout << con->to_string() << " has connect！" << endl;
}

void onMessage(const TcpConnectionPtr &con)
{
    string msg = con->recive();
    cout << ">>recv client " << msg << endl;
    // msg进行业务逻辑的处理
    // msg1
    MyTask task(msg, con);
    threadpool->submit(std::bind(&MyTask::process, task));
    /* con->send(msg); */
}

void onClose(const TcpConnectionPtr &con)
{
    cout << con->to_string() << " has closed！" << endl;
}

void test()
{
    Acceptor acceptor("127.0.0.1", 8888);
    acceptor.ready(); //此时处于监听状态

    Eventloop loop(acceptor);
    loop.set_connection_callback(std::move(onConnection));
    loop.set_message_callback(std::move(onMessage));
    loop.set_close_callback(std::move(onClose));
    loop.loop();
}

void test2()
{
    Tcpserver server("127.0.0.1", 8888);
    server.set_callback(std::move(onConnection), std::move(onMessage), std::move(onClose));
    server.start();
}

void test3()
{
    Threadpool threadPool(5);
    threadPool.init();
    threadpool = &threadPool;

    Tcpserver server("127.0.0.1", 8888);
    server.set_callback(std::move(onConnection), std::move(onMessage), std::move(onClose));
    server.start();
}

int main(int argc, char **argv)
{
    test3();
    return 0;
}
