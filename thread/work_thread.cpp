#include "work_thread.h"
#include "work_thread_pool.h"



using namespace duck::thread;




void WorkThread::process() 
{

    while(true) {

        std::unique_lock<std::mutex> lock(mutex_);

        while(task_ == nullptr) {
            cond_.wait(lock);
        }

        if (task_->type() == QUIT_TASK) {
            LOG(INFO) << "receive quit task, quit thread...";
            task_ = nullptr; 
            LOG(INFO) << "quit thread ok!";
            break;
        } else {
            LOG(INFO) << "Got a normal task, run now!";
            task_->process();
            task_ = nullptr;
            thread_pool_->push_thread(get_shared_ptr());
            LOG(INFO) << "finished task!";
        }
    } 
}
















