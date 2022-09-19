/*
 * @Author: cell_lin 1335954640@qq.com
 * @Date: 2022-09-14 20:59:27
 * @LastEditors: cell_lin 1335954640@qq.com
 * @LastEditTime: 2022-09-14 21:43:31
 * @FilePath: /Linux/search/src/include/initaddress.hh
 * @Description:
 *
 * Copyright (c) 2022 by cell_lin 1335954640@qq.com, All Rights Reserved.
 */
#pragma once

#include <arpa/inet.h>
#include <string>
#include <stdio.h>
#include <string.h>
namespace yuki
{

    class Initaddress
    {
    private:
        struct sockaddr_in addr_;

    public:
        Initaddress(short port);                       //只设置端口，允许任何ip访问
        Initaddress(const char *ip, short port);       //设置端口和访问ip
        Initaddress(const sockaddr_in &addr);          //根据sockaddr_in设置
        const struct sockaddr_in *getsockaddr() const; //获取addr
        std::string ip() const;
        unsigned short port() const;
        ~Initaddress();
    };

}