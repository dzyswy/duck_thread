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


    std::cout << "wait key..." << std::endl;
    std::getchar(); 

    std::cout << "bye!" << std::endl;

    return 0;
}





