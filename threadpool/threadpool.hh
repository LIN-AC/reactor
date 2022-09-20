#pragma once

#include "taskqueue.hh"
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <utility>
#include <vector>

class Threadpool
{
private:
    std::vector<std::thread> threadpool_;
    Taskqueue<std::function<void()>> taskqueue_;
    std::mutex mtx_;
    std::condition_variable cv_lock_;
    bool shutdowned_;
    class ThreadWorker
    {
    private:
        int pid_; //工作线程id
        Threadpool *pool_;

    public:
        ThreadWorker(Threadpool *threadpool, const int id)
            : pid_(id), pool_(threadpool)
        {
        }
        ~ThreadWorker() {}
        //重载()运算符
        void operator()()
        {
            std::function<void()> func;
            bool dequeued;
            while (!pool_->shutdowned_)
            {
                { //为工作线程加锁
                    std::unique_lock<std::mutex> lock(pool_->mtx_);
                    //如果任务队列为空，则阻塞等待唤醒
                    if (pool_->taskqueue_.empty()) //防止虚假唤醒
                    {
                        pool_->cv_lock_.wait(lock);
                    }
                    //取出任务队列元素
                    dequeued = pool_->taskqueue_.dequeue(func);
                }
                if (dequeued)
                    func();
            }
        }
    };

public:
    Threadpool(const int size)
        : threadpool_(std::vector<std::thread>(size)), shutdowned_(false)
    {
    }
    //禁止复制
    Threadpool(const Threadpool &) = delete;
    Threadpool(Threadpool &&) = delete;
    //禁止移动构造复制
    Threadpool &operator=(const Threadpool &) = delete;
    Threadpool &operator=(Threadpool &&) = delete;

    //初始化
    void init()
    {
        for (int i = 0; i < threadpool_.size(); ++i)
        {
            threadpool_[i] = std::thread(ThreadWorker(this, i));
        }
    }

    //关闭线程池
    void shutdown()
    {
        shutdowned_ = true;
        cv_lock_.notify_all();

        for (int i = 0; i < threadpool_.size(); ++i)
        {
            if (threadpool_[i].joinable())
                threadpool_[i].join();
        }
    }

    template <typename F, typename... Args>
    auto submit(F &&f, Args &&...args) -> std::future<decltype(f(args...))>
    {
        std::function<decltype(f(args...))()> func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
        auto task_ptr = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);
        std::function<void()> wrapper_func = [task_ptr]()
        {
            (*task_ptr)();
        };
        taskqueue_.enqueue(wrapper_func);
        cv_lock_.notify_one();
        return task_ptr->get_future(); //执行
    }
};
