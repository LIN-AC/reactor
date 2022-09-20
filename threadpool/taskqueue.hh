#pragma once

#include <queue>
#include <mutex>

template <typename T>
class Taskqueue
{
private:
    std::mutex mtx_;          //同步锁
    std::queue<T> taskqueue_; //线程安全任务队列
    size_t size_;             //队列大小

public:
    Taskqueue(const size_t size = 1024)
        : size_(size)
    {
    }
    Taskqueue(const Taskqueue &other) = delete;
    Taskqueue &operator=(const Taskqueue &) = delete;
    ~Taskqueue()
    {
    }

public:
    int size()
    {
        std::unique_lock<std::mutex> lock(mtx_);
        return size_;
    }
    bool empty()
    {
        std::unique_lock<std::mutex> lock(mtx_);
        return taskqueue_.empty();
    }
    bool full()
    {
        std::unique_lock<std::mutex> lock(mtx_);
        return taskqueue_.size() == size_;
    }
    //任务进入任务队列
    bool enqueue(T &task)
    {
        if (full())
        {
            perror("enqueue");
            return false;
        }
        std::unique_lock<std::mutex> lock(mtx_);
        taskqueue_.push(task);
        return true;
    }
    //任务出队执行
    bool dequeue(T &task)
    {
        if (taskqueue_.empty())
            return false;
        std::unique_lock<std::mutex> lock(mtx_);
        task = std::move(taskqueue_.front());
        taskqueue_.pop();
        return true;
    }
};
