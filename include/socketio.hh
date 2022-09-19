/*
 * @Author: cell_lin 1335954640@qq.com
 * @Date: 2022-09-14 21:44:58
 * @LastEditors: cell_lin 1335954640@qq.com
 * @LastEditTime: 2022-09-15 14:54:52
 * @FilePath: /Linux/search/src/include/socketio.hh
 * @Description: 通过socket进行收发信息
 *
 * Copyright (c) 2022 by cell_lin 1335954640@qq.com, All Rights Reserved.
 */
#pragma once

#include <stdio.h>

namespace yuki
{
    class SocketIo
    {
    private:
        int fd_;

    public:
        SocketIo(int fd);
        ~SocketIo();
        size_t readn(char *buf, size_t count);        //通过socketfd接受数据
        size_t writen(const char *buf, size_t count); //发送数据
        size_t read_line(char *buf, size_t count);    //通过socketfd读取一行数据

    private:
        size_t recv_peek(char *buf, size_t count);
    };

} // namespace yuki
