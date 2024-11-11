#include "thread/work_thread_pool.h"
#include "thread/task_add.h"
#include "thread/task_sub.h"
#include <chrono>




using namespace duck::thread;







int main(int argc, char* argv[])
{
    google::InstallFailureSignalHandler();
    google::InitGoogleLogging(argv[0]);

    FLAGS_stderrthreshold = 0;
    FLAGS_minloglevel = 0;


    std::shared_ptr<TaskData> add_data = std::make_shared<AddTaskData>(12, 34); 
    std::shared_ptr<TaskData> sub_data = std::make_shared<SubTaskData>(124, 456); 

    std::shared_ptr<AddTask> task_add = std::make_shared<AddTask>(add_data);
    std::shared_ptr<SubTask> task_sub = std::make_shared<SubTask>(sub_data);

    int thread_num = 4;

    WorkThreadPool thread_pool(4);
    thread_pool.start();
    thread_pool.push_task(task_add);
    thread_pool.push_task(task_add);
    thread_pool.push_task(task_add);
    thread_pool.push_task(task_sub);
    thread_pool.push_task(task_sub);

    thread_pool.stop();

#if 0
    std::vector<std::shared_ptr<WorkThread> > thread_vec;
    SafeQueue<std::shared_ptr<WorkThread> > thread_pool(thread_num);
    for (int i = 0; i < thread_num; i++) {
        std::shared_ptr<WorkThread> thread = std::make_shared<WorkThread>();
        //std::shared_ptr<WorkThread> thread(new WorkThread);
        thread_vec.push_back(thread);
        thread_pool.push(thread);
    }

    for (int i = 0; i < thread_num; i++) {
        std::shared_ptr<WorkThread> thread = thread_pool.pop();
        thread->start();
        thread_pool.push(thread);
    }

    for (int i = 0; i < thread_num; i++) {
        std::shared_ptr<WorkThread> thread = thread_pool.pop();
        if (thread)
            thread->join();
    }
#endif



#if 0
    SafeQueue<WorkThread*> thread_pool(thread_num);
    for (int i = 0; i < thread_num; i++) {
        WorkThread* thread = new WorkThread;
        thread_pool.push(thread);
    }

    for (int i = 0; i < thread_num; i++) {
        WorkThread* thread = thread_pool.pop();
        thread->start();
        thread_pool.push(thread);
    }

    for (int i = 0; i < thread_num; i++) {
        WorkThread* thread = thread_pool.pop();
        thread->join();
    }
#endif

    std::cout << "wait key..." << std::endl;
    std::getchar(); 

    std::cout << "bye!" << std::endl;

    return 0;
}





