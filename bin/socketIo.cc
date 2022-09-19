/*
 * @Author: cell_lin 1335954640@qq.com
 * @Date: 2022-09-14 21:50:52
 * @LastEditors: cell_lin 1335954640@qq.com
 * @LastEditTime: 2022-09-15 15:47:28
 * @FilePath: /Linux/search/src/bin/socketIo.cc
 * @Description:
 *
 * Copyright (c) 2022 by cell_lin 1335954640@qq.com, All Rights Reserved.
 */
#include "../include/socketio.hh"
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
namespace yuki
{
    SocketIo::SocketIo(int fd)
        : fd_(fd)
    {
    }
    SocketIo::~SocketIo()
    {
    }

    size_t SocketIo::readn(char *buf, size_t count)
    {
        size_t left = count;
        char *pstr = buf;
        int ret = 0;
        while (left > 0)
        {
            ret = ::read(fd_, pstr, left);
            if (-1 == ret)
            {
                if (errno == EINTR)
                    continue;
                perror("read error");
                return count - ret;
            }
            else if (0 == ret)
            {
                break;
            }
            pstr += ret;
            left -= ret;
        }
        return count - left;
    }

    size_t SocketIo::writen(const char *buf, size_t count)
    {
        size_t left = count;
        const char *pbuf = buf;
        int ret;
        while (left > 0)
        {
            ret = ::write(fd_, pbuf, left);
            if (-1 == ret)
            {
                if (errno == EINTR)
                    continue;
                perror("write error");
                return count - ret;
            }
            pbuf += ret;
            left -= ret;
        }
        return count - left;
    }
    size_t SocketIo::recv_peek(char *buf, size_t count)
    {
        int ret;
        do
        {
            // MSG_PEEK不会将缓冲区中的数据进行清空,只会进行拷贝操作
            ret = ::recv(fd_, buf, count, MSG_PEEK);
        } while (ret == -1 && errno == EINTR);
        return ret;
    }
    size_t SocketIo::read_line(char *buf, size_t count)
    {
        size_t left = count - 1;
        int ret = 0;
        size_t total = 0;
        char *pbuf = buf;
        while (left > 0)
        {
            ret = recv_peek(pbuf, left);
            if (ret <= 0)
                break;
            for (size_t i = 0; i != ret; ++i)
            {
                if (pbuf[i] == '\n')
                {
                    size_t nsize = i + 1;
                    if (readn(pbuf, nsize) != nsize)
                    {
                        perror("read line");
                        return total;
                    }
                    pbuf += nsize;
                    total += nsize;
                    *pbuf = '\0';
                    return total;
                }
            }
            if (readn(pbuf, ret) != ret)
            {
                perror("read line");
                return total;
            }
            pbuf += ret;
            total += ret;
            left -= ret;
        }
        *pbuf = '\0';
        return total - left;
    }
} // namespace yuki
