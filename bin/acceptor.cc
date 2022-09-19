/*
 * @Author: cell_lin 1335954640@qq.com
 * @Date: 2022-09-14 22:44:06
 * @LastEditors: cell_lin 1335954640@qq.com
 * @LastEditTime: 2022-09-15 15:27:23
 * @FilePath: /Linux/search/src/bin/acceptor.cc
 * @Description:
 *
 * Copyright (c) 2022 by cell_lin 1335954640@qq.com, All Rights Reserved.
 */
#include "../include/acceptor.hh"

namespace yuki
{
    Acceptor::Acceptor(const char *ip, unsigned int port)
        : sock_(), addr_(ip, port)
    {
    }
    Acceptor::~Acceptor()
    {
    }
    void Acceptor::ready()
    {
        set_reuse_port();
        set_reuse_port();
        bind();
        listen();
    }
    void Acceptor::set_reuse_addr()
    {
        int on = 1;
        if (setsockopt(sock_.fd(), SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)))
        {
            perror("set_reuse_addr");
            return;
        }
    }

    void Acceptor::set_reuse_port()
    {
        int on = 1;
        if (setsockopt(sock_.fd(), SOL_SOCKET, SO_REUSEPORT, &on, sizeof(on)))
        {
            perror("set_reuse_port");
            return;
        }
    }
    void Acceptor::bind()
    {
        if (-1 == ::bind(sock_.fd(), (struct sockaddr *)addr_.getsockaddr(), sizeof(struct sockaddr)))
        {
            perror("bind");
            return;
        }
    }
    void Acceptor::listen()
    {
        if (-1 == ::listen(sock_.fd(), contions))
        {
            perror("listen");
            return;
        }
    }
    int Acceptor::accept()
    {
        int ret = ::accept(sock_.fd(), nullptr, nullptr);
        if (-1 == ret)
        {
            perror("accept");
            return -1;
        }
        return ret;
    }
    int Acceptor::fd() const
    {
        return sock_.fd();
    }

} // namespace yuki
