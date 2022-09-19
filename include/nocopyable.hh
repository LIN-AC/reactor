/*
 * @Author: cell_lin 1335954640@qq.com
 * @Date: 2022-09-14 20:47:04
 * @LastEditors: cell_lin 1335954640@qq.com
 * @LastEditTime: 2022-09-14 22:54:06
 * @FilePath: /Linux/search/src/include/nocopyable.hh
 * @Description: 禁止复制
 *
 * Copyright (c) 2022 by cell_lin 1335954640@qq.com, All Rights Reserved.
 */
#pragma once

class Nocopyable
{
public:
    Nocopyable(){};
    ~Nocopyable(){};

    Nocopyable(const Nocopyable &) = delete;
    Nocopyable(const Nocopyable &&) = delete;
    Nocopyable &operator=(const Nocopyable &) = delete;
};
