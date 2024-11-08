#include "work_thread.h"
#include "work_thread_pool.h"



using namespace duck::thread;




void WorkThread::process() 
{

    while(true) {

        std::unique_lock<std::mutex> lock(mutex_);

        while(!task_) {
            cond_.wait(lock);
        }
        //lock.unlock();

        // if (task_->type() == QUIT_TASK) {
        //     LOG(INFO) << "receive quit task, quit thread...";
        //     task_ = nullptr;
        //     //thread_pool_->push(get_shared_ptr());
        //     LOG(INFO) << "quit thread ok!";
        //     break;
        // } else {
        //     LOG(INFO) << "Got a normal task, run now!";
        //     task_->process();
        //     task_ = nullptr;
        //     thread_pool_->push(get_shared_ptr());
        //     LOG(INFO) << "finished task!";
        // }
        break;
    }
}
















