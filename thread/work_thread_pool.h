#pragma once

#include "thread/work_thread.h"
#include "thread/queue.h"

namespace duck {
namespace thread {


class WorkThreadPool
{
public:
    WorkThreadPool(int thread_num) : thread_pool_(thread_num)  {

        for (int i = 0; i < thread_num; i++) {
            std::shared_ptr<WorkThread> thread = std::make_shared<WorkThread>(this); 
            push(thread);
            thread->start();
        }

    }

    void push(std::shared_ptr<WorkThread> thread) {
        thread_pool_.push(thread);
    }

    std::shared_ptr<WorkThread> pop() {
        return thread_pool_.pop();
    }

    int thread_num() {
        return thread_pool_.deep();
    }

protected:
    SafeQueue<std::shared_ptr<WorkThread> > thread_pool_;

};




}//namespace thread
}//namespace duck






