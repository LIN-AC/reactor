/*
 * @Author: cell_lin 1335954640@qq.com
 * @Date: 2022-09-15 14:21:21
 * @LastEditors: cell_lin 1335954640@qq.com
 * @LastEditTime: 2022-09-19 22:00:58
 * @FilePath: /Linux/tcpv2/tcp/bin/tcpconnection.cc
 * @Description:
 *
 * Copyright (c) 2022 by cell_lin 1335954640@qq.com, All Rights Reserved.
 */
#include "../include/tcpconnection.hh"
#include <sstream>
namespace yuki
{
    Tcpconnection::Tcpconnection(int fd, Eventloop *eventloop)
        : eventloop_(eventloop),
          socketio_(fd),
          socket_(fd),
          localaddr_(get_local_address()),
          peeraddr_(get_peer_address())
    {
    }
    Tcpconnection::~Tcpconnection()
    {
    }
    void Tcpconnection::send(const std::string &msg)
    {
        socketio_.writen(msg.c_str(), msg.length());
    }
    std::string Tcpconnection::recive()
    {
        char buf[BUFFSIZE];
        socketio_.read_line(buf, BUFFSIZE);
        return std::string(buf);
    }
    Initaddress Tcpconnection::get_local_address()
    {
        struct sockaddr_in addr;
        socklen_t len = sizeof(struct sockaddr);
        int ret = getsockname(socket_.fd(), (struct sockaddr *)&addr, &len); //获取本地address放入addr中
        if (-1 == ret)
        {
            perror("getsockname");
        }
        return Initaddress(addr);
    }
    Initaddress Tcpconnection::get_peer_address()
    {
        struct sockaddr_in addr;
        socklen_t len = sizeof(struct sockaddr);
        int ret = getpeername(socket_.fd(), (struct sockaddr *)&addr, &len);
        if (-1 == ret)
        {
            perror("getpeername");
        }
        return Initaddress(addr);
    }

    std::string Tcpconnection::to_string()
    {
        std::ostringstream os;
        os << localaddr_.ip() << ":"
           << localaddr_.port() << "-->"
           << peeraddr_.ip() << ":"
           << peeraddr_.port();
        return os.str();
    }

    bool Tcpconnection::isclosed()
    {
        char buf[10] = {0};
        return ::recv(socket_.fd(), buf, 10, MSG_PEEK) == 0;
    }

    void Tcpconnection::send_loop(const std::string &msg)
    {
        if (eventloop_)
        {
            eventloop_->run_in_loop(std::bind(&yuki::Tcpconnection::send, this, msg));
        }
    }

    void Tcpconnection::set_connection_callback(const TcpConnectionCallback &cb)
    {
        on_connection_ = cb;
    }

    void Tcpconnection::set_message_callback(const TcpConnectionCallback &cb)
    {
        on_message_ = cb;
    }

    void Tcpconnection::set_close_callback(const TcpConnectionCallback &cb)
    {
        on_close_ = cb;
    }

    void Tcpconnection::handler_connection_callback()
    {
        if (on_connection_)
        {
            on_connection_(shared_from_this());
        }
    }
    void Tcpconnection::handler_message_callback()
    {
        if (on_message_)
        {
            on_message_(shared_from_this());
        }
    }
    void Tcpconnection::handler_close_callback()
    {
        if (on_close_)
        {
            on_close_(shared_from_this());
        }
    }
} // namespace yuki
