#include <iostream>



#include "thread/task_dispatcher.h"
#include "thread/task_add.h"
#include "thread/task_sub.h"

 
using namespace duck::thread;

void test();
int main(int argc, char* argv[])
{
    google::InstallFailureSignalHandler();
    google::InitGoogleLogging(argv[0]);

    FLAGS_stderrthreshold = 0;
    FLAGS_minloglevel = 0;

    //test();

    int max_task_num = 10;
    int thread_num = 4;
    TaskDispatcher disp(max_task_num, thread_num);

    disp.start();
    disp.stop();
    
    std::cout << "wait key..." << std::endl;
    std::getchar(); 

    std::cout << "bye!" << std::endl;
    return 0;
}


void test()
{
    WorkThreadPool pool(4); 

    std::shared_ptr<WorkThread> thread = pool.pop();
    std::cout << "thread: ptr=" << (void*)&thread << ", use_count=" << thread.use_count() << std::endl;
    std::shared_ptr<WorkThread> thd = thread->get_shared_ptr();
    std::cout << "thd: ptr=" << (void*)&thd << ", use_count=" << thd.use_count() << std::endl;
}








