/*
 * @Author: cell_lin 1335954640@qq.com
 * @Date: 2022-09-19 10:55:56
 * @LastEditors: cell_lin 1335954640@qq.com
 * @LastEditTime: 2022-09-19 11:37:43
 * @FilePath: /Linux/tcp/threadpool/test.cc
 * @Description:
 *
 * Copyright (c) 2022 by cell_lin 1335954640@qq.com, All Rights Reserved.
 */
#include "threadpool.hh"
#include <iostream>

using namespace std;

void add(int x, int y)
{
    int out = x + y;
    cout << x << " + " << y << " = " << out << endl;
}

void mutiply(int &out, int x, int y)
{
    out = x * y;
    cout << x << " * " << y << " = " << out << endl;
}

void decrease(int &out, int x, int y)
{
    out = x - y;
    cout << "x - y = " << out << endl;
}
int main()
{
    Threadpool threadpool(3);
    threadpool.init();
    int output;
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 1; j < 10; ++j)
        {
            threadpool.submit(add, i, j);
        }
    }
    auto f1 = threadpool.submit(mutiply, std::ref(output), 5, 6);
    f1.get();
    cout << "the last add result is " << output << endl;
    threadpool.shutdown();
    return 0;
}