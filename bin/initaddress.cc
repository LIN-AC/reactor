/*
 * @Author: cell_lin 1335954640@qq.com
 * @Date: 2022-09-14 21:30:10
 * @LastEditors: cell_lin 1335954640@qq.com
 * @LastEditTime: 2022-09-15 15:30:30
 * @FilePath: /Linux/search/src/bin/initaddress.cc
 * @Description:
 *
 * Copyright (c) 2022 by cell_lin 1335954640@qq.com, All Rights Reserved.
 */
#include "../include/initaddress.hh"

namespace yuki
{
    Initaddress::Initaddress(short port)
    {
        ::memset(&addr_, 0, sizeof(addr_));
        addr_.sin_family = AF_INET;
        addr_.sin_port = htons(port);
        addr_.sin_addr.s_addr = INADDR_ANY;
    }

    Initaddress::Initaddress(const char *ip, short port)
    {
        ::memset(&addr_, 0, sizeof(addr_));
        addr_.sin_family = AF_INET;
        addr_.sin_port = htons(port);
        addr_.sin_addr.s_addr = inet_addr(ip);
    }

    Initaddress::Initaddress(const struct sockaddr_in &addr)
        : addr_(addr)
    {
    }
    Initaddress::~Initaddress()
    {
    }
    const struct sockaddr_in *Initaddress::getsockaddr() const
    {
        return &addr_;
    }
    std::string Initaddress::ip() const
    {
        return std::string(inet_ntoa(addr_.sin_addr));
    }

    unsigned short Initaddress::port() const
    {
        return ntohs(addr_.sin_port);
    }
}
