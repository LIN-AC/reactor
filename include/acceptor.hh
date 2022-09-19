/*
 * @Author: cell_lin 1335954640@qq.com
 * @Date: 2022-09-14 22:37:58
 * @LastEditors: cell_lin 1335954640@qq.com
 * @LastEditTime: 2022-09-14 23:01:23
 * @FilePath: /Linux/search/src/include/acceptor.hh
 * @Description:
 *
 * Copyright (c) 2022 by cell_lin 1335954640@qq.com, All Rights Reserved.
 */
#pragma once

#include "initaddress.hh"
#include "socket.hh"

namespace yuki
{
    const int contions = 1024;
    class Acceptor
    {
    private:
        Socket sock_;
        Initaddress addr_;

    public:
        Acceptor(const char *ip, unsigned int port);
        ~Acceptor();
        void ready(); //初始化
        void set_reuse_port();
        void set_reuse_addr();
        void bind();    //绑定
        void listen();  //监听
        int accept();   //建立连接,返回连接标识符fd
        int fd() const; //返回连接标识符
    };

} // namespace yuki
