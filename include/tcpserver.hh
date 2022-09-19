/*
 * @Author: cell_lin 1335954640@qq.com
 * @Date: 2022-09-19 21:43:29
 * @LastEditors: cell_lin 1335954640@qq.com
 * @LastEditTime: 2022-09-19 21:54:07
 * @FilePath: /Linux/tcpv2/tcp/include/tcpserver.hh
 * @Description:
 *
 * Copyright (c) 2022 by cell_lin 1335954640@qq.com, All Rights Reserved.
 */
#pragma once

#include "acceptor.hh"
#include "eventloop.hh"

namespace yuki
{
    class Tcpserver
    {
    private:
        Acceptor acceptor_;
        Eventloop eventloop_;

    public:
        Tcpserver(const char *ip, unsigned int port);
        ~Tcpserver();

        void start();
        void stop();
        void set_callback(TcpConnectionCallback &&on_connection_callback,
                          TcpConnectionCallback &&on_message_callback,
                          TcpConnectionCallback &&on_close_callback);
    };

    Tcpserver::Tcpserver(const char *ip, unsigned int port)
        : acceptor_(ip, port),
          eventloop_(acceptor_)
    {
    }

    Tcpserver::~Tcpserver()
    {
    }
    void Tcpserver::start()
    {
        acceptor_.ready();
        eventloop_.loop();
    }
    void Tcpserver::stop()
    {
        eventloop_.unloop();
    }

    void Tcpserver::set_callback(TcpConnectionCallback &&on_connection_callback,
                                 TcpConnectionCallback &&on_message_callback,
                                 TcpConnectionCallback &&on_close_callback)
    {
        eventloop_.set_connection_callback(std::move(on_connection_callback));
        eventloop_.set_message_callback(std::move(on_message_callback));
        eventloop_.set_close_callback(std::move(on_close_callback));
    }
} // namespace yuki
