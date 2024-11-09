#pragma once

#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>

#include "thread/thread.h"
#include "thread/task.h"

namespace duck {
namespace thread {


class WorkThreadPool;

//, public std::enable_shared_from_this<WorkThread>
class WorkThread : public Thread, public std::enable_shared_from_this<WorkThread>
{
public: 
    WorkThread(WorkThreadPool* thread_pool) : thread_pool_(thread_pool) {}

    void assign(std::shared_ptr<Task> task)  
    {
        std::unique_lock<std::mutex> lock(mutex_);
        task_ = task;
        cond_.notify_one();
    }

    void process();

    std::shared_ptr<WorkThread> get_shared_ptr() {
       return shared_from_this();
    }


protected:  
    WorkThreadPool* thread_pool_;
    std::shared_ptr<Task> task_;
    std::mutex mutex_;
    std::condition_variable cond_;


};


}//namespace thread
}//namespace duck


