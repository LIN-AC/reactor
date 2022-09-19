/*
 * @Author: cell_lin 1335954640@qq.com
 * @Date: 2022-09-14 20:54:22
 * @LastEditors: cell_lin 1335954640@qq.com
 * @LastEditTime: 2022-09-15 15:32:08
 * @FilePath: /Linux/search/src/include/socket.hh
 * @Description:初始化socket连接
 *
 * Copyright (c) 2022 by cell_lin 1335954640@qq.com, All Rights Reserved.
 */
#pragma once

#include "nocopyable.hh"
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
namespace yuki
{
    class Initaddress;
    class Socket : public Nocopyable
    {
    private:
        int fd_;

    public:
        Socket();
        ~Socket();
        explicit Socket(int fd);
        int fd() const;
        void shutdownwrite();
    };

}