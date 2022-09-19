/*
 * @Author: cell_lin 1335954640@qq.com
 * @Date: 2022-09-15 16:28:41
 * @LastEditors: cell_lin 1335954640@qq.com
 * @LastEditTime: 2022-09-19 22:27:16
 * @FilePath: /Linux/tcpv2/tcp/include/eventloop.hh
 * @Description:
 *
 * Copyright (c) 2022 by cell_lin 1335954640@qq.com, All Rights Reserved.
 */
#pragma once

#include <sys/epoll.h>
#include <vector>
#include <map>
#include <memory>
#include <functional>
#include <mutex>

namespace yuki
{
    class Acceptor;
    class Tcpconnection;

    const int SIZE = 1024;
    using TcpConnectionPtr = std::shared_ptr<Tcpconnection>;
    using TcpConnectionCallback = std::function<void(const TcpConnectionPtr &)>;
    using Task = std::function<void()>;

    class Eventloop
    {
    private:
        int epfd_;    // epollfd
        int eventfd_; //进程通信fd

        std::vector<struct epoll_event> evtlist_;
        bool isloop_;
        Acceptor &acceptor_;
        std::map<int, TcpConnectionPtr> conns_; //已连接

        TcpConnectionCallback on_connection_;
        TcpConnectionCallback on_message_;
        TcpConnectionCallback on_close_;

        std::vector<Task> pending_cb_;
        std::mutex eventloop_mtx_;

    public:
        Eventloop(Acceptor &);
        ~Eventloop();
        void loop();
        void unloop();

        //设置三个回调函数
        void set_connection_callback(TcpConnectionCallback &&);
        void set_message_callback(TcpConnectionCallback &&);
        void set_close_callback(TcpConnectionCallback &&);

        void run_in_loop(Task &&t); //循环等待
        void wakeup();              //唤醒进程
        void do_pending_func();     //添加任务到任务队列
        void handler_read();        //收到eventfd发送的信号，读取完毕

    private:
        int init_epollfd();            //初始化epollfd
        int init_eventfd();            //初始化eventfd
        void add_epoll_readfd(int fd); //对fd添加读监听
        void del_epoll_readfd(int fd); //对fd删除读监听

        void wait_epollfd();
        void handler_newconnection();
        void handler_message(int fd);
    };
} // namespace yuki
