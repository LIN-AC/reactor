/*
 * @Author: cell_lin 1335954640@qq.com
 * @Date: 2022-09-19 09:24:51
 * @LastEditors: cell_lin 1335954640@qq.com
 * @LastEditTime: 2022-09-19 09:39:46
 * @FilePath: /Linux/tcp/threadpool/mutexlock.hh
 * @Description: 封装mutex
 *
 * Copyright (c) 2022 by cell_lin 1335954640@qq.com, All Rights Reserved.
 */
#pragma once

#include "../include/nocopyable.hh"
#include <pthread.h>
#include <stdio.h>

namespace yuki
{
    class Mutexlock : public Nocopyable
    {
    private:
        pthread_mutex_t mtx_;

    public:
        Mutexlock();
        ~Mutexlock();
        pthread_mutex_t *get_mutex();
        void lock();
        void unlock();
    };

    Mutexlock::Mutexlock()
    {
        if (pthread_mutex_init(&mtx_, nullptr))
        {
            perror("pthread_mutex_init");
        }
    }

    Mutexlock::~Mutexlock()
    {
        if (pthread_mutex_destroy(&mtx_))
            perror("pthread_destroy");
    }
    pthread_mutex_t *Mutexlock::get_mutex()
    {
        return &mtx_;
    }
    void Mutexlock::lock()
    {
        if (pthread_mutex_lock(&mtx_))
        {
            perror("pthread_mutex_lock");
        }
    }
    void Mutexlock::unlock()
    {
        if (pthread_mutex_unlock(&mtx_))
        {
            perror("pthread_mutex_unlock");
        }
    }

    //自动加锁解锁
    class MutexLockGuard
    {
    private:
        Mutexlock &mtx_;

    public:
        MutexLockGuard(Mutexlock &);
        ~MutexLockGuard();
    };

    MutexLockGuard::MutexLockGuard(Mutexlock &mtx)
        : mtx_(mtx)
    {
        mtx_.lock();
    }

    MutexLockGuard::~MutexLockGuard()
    {
        mtx_.unlock();
    }

} // namespace yuki
