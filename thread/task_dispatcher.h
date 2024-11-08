#pragma once


#include "thread/thread.h"
#include "thread/task.h"
#include "thread/queue.h"
#include "thread/work_thread_pool.h"

namespace duck {
namespace thread {



class TaskDispatcher : public Thread
{
public:
    TaskDispatcher(int task_max_num, int thread_num) 
        : task_queue_(task_max_num), thread_pool_(thread_num) {
    }

    void process() {

        while(true) {

            std::shared_ptr<Task> task = task_queue_.pop();
            LOG(INFO) << "pop a task from task_queue_!";

            if (task->type() == QUIT_TASK) {
                for (int i = 0; i < thread_pool_.thread_num(); i++) {
                    std::shared_ptr<WorkThread> thread = thread_pool_.pop();
                    thread->assign(task);
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

    void push_task(std::shared_ptr<Task> task) {
        task_queue_.push(task);
    }

    void stop() { 
        std::shared_ptr<Task> quit_task = std::make_shared<Task>();//QUIT_TASK
   
        push_task(quit_task);
        for (int i = 0; i < thread_pool_.thread_num(); i++) {
            std::shared_ptr<WorkThread> thread = thread_pool_.pop();
            thread->join();
        }
        join();
        
    }


protected:
    WorkThreadPool thread_pool_;
    SafeQueue<std::shared_ptr<Task> > task_queue_;
};




}//namespace thread
}//namespace duck







