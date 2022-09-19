/*
 * @Author: cell_lin 1335954640@qq.com
 * @Date: 2022-09-14 21:18:53
 * @LastEditors: cell_lin 1335954640@qq.com
 * @LastEditTime: 2022-09-15 15:36:12
 * @FilePath: /Linux/search/src/bin/socket.cc
 * @Description:
 *
 * Copyright (c) 2022 by cell_lin 1335954640@qq.com, All Rights Reserved.
 */
#include "../include/socket.hh"

using namespace yuki;

Socket::Socket()
{
    fd_ = ::socket(AF_INET, SOCK_STREAM, 0);
}
Socket::Socket(int socketfd)
    : fd_(socketfd)
{
}

Socket::~Socket()
{
    close(fd_);
}
int Socket::fd() const
{
    return fd_;
}

void Socket::shutdownwrite()
{
    //关闭写端
    int ret = shutdown(fd_, SHUT_WR);
    if (ret)
    {
        perror("shutdown");
        return;
    }
}