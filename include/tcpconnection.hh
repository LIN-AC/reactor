/*
 * @Author: cell_lin 1335954640@qq.com
 * @Date: 2022-09-14 20:39:41
 * @LastEditors: cell_lin 1335954640@qq.com
 * @LastEditTime: 2022-09-15 20:36:01
 * @FilePath: /Linux/search/src/include/tcpconnection.hh
 * @Description: 建立tcp连接
 *
 * Copyright (c) 2022 by cell_lin 1335954640@qq.com, All Rights Reserved.
 */

#pragma once

// #include <memory>
// #include <functional>
#include <sys/socket.h>
#include <functional>
#include <memory>
#include "socket.hh"
#include "socketio.hh"
#include "initaddress.hh"
#include "eventloop.hh"

namespace yuki
{
    const int BUFFSIZE = 10240; //设置缓冲区大小
    class Tcpconnection : public std::enable_shared_from_this<Tcpconnection>
    {
        using TcpConnectionPtr = std::shared_ptr<Tcpconnection>;
        using TcpConnectionCallback = std::function<void(const TcpConnectionPtr &)>;

    private:
        Eventloop *eventloop_;
        SocketIo socketio_;
        Socket socket_;
        Initaddress localaddr_;
        Initaddress peeraddr_;

        TcpConnectionCallback on_connection_;
        TcpConnectionCallback on_message_;
        TcpConnectionCallback on_close_;

    private:
        Initaddress get_local_address();
        Initaddress get_peer_address();

    public:
        Tcpconnection(int fd, Eventloop *eventloop);
        ~Tcpconnection();
        void send(const std::string &); //发送数据
        std::string recive();           //接受数据
        std::string to_string();

        void send_loop(const std::string &); //将参数转发给Eventloop，由Eventloop进行发送
        bool isclosed();                     //判断是否连接已经关闭
        //设置三个回调函数
        void set_connection_callback(const TcpConnectionCallback &);
        void set_message_callback(const TcpConnectionCallback &);
        void set_close_callback(const TcpConnectionCallback &);

        void handler_connection_callback();
        void handler_message_callback();
        void handler_close_callback();
    };
}