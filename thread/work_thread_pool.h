#pragma once

#include "thread/work_thread.h"
#include "thread/queue.h"

namespace duck {
namespace thread {


class WorkThreadPool : public Thread
{
public:
    WorkThreadPool(int thread_num) : thread_pool_(thread_num)  {

        for (int i = 0; i < thread_num; i++) {
            std::shared_ptr<WorkThread> thread = std::make_shared<WorkThread>(this); 
            thread_pool_.push(thread);
            thread_vec_.push_back(thread);
        }
        quit_task_ = std::make_shared<QuitTask>();
    }

    void process() {

        while(true)
        {
            std::shared_ptr<Task> task = task_queue_.pop();
            LOG(INFO) << "pop a task from task_queue_!";

            if (task->type() == QUIT_TASK) {
                for (size_t i = 0; i < thread_num(); i++) { 
                    thread_vec_[i]->assign(quit_task_);
                }
                for (size_t i = 0; i < thread_num(); i++) { 
                    thread_vec_[i]->join();
                }
                break;
            } else {
                std::shared_ptr<WorkThread> thread = thread_pool_.pop();
                LOG(INFO) << "pop a thread from thread_pool_!";
                thread->assign(task);
                LOG(INFO) << "assign a task to thread!";
            }

        }
    }

    void start() {
        for (size_t i = 0; i < thread_num(); i++) { 
            thread_vec_[i]->start();
        }
        Thread::start();
    }

    void stop() {
        push_task(quit_task_);
        Thread::join();
    }

    void push_task(std::shared_ptr<Task> task) {
        task_queue_.push(task);
    }

    void push_thread(std::shared_ptr<WorkThread> thread) {
        thread_pool_.push(thread);
    }



    int thread_num() {
        return thread_vec_.size();
    }

protected:
    std::vector<std::shared_ptr<WorkThread> > thread_vec_;
    SafeQueue<std::shared_ptr<WorkThread> > thread_pool_;
    std::shared_ptr<Task> quit_task_;
    SafeQueue<std::shared_ptr<Task> > task_queue_;
};




}//namespace thread
}//namespace duck






