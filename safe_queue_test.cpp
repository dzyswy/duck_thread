#include "thread/queue.h"
#include <chrono>

using namespace duck::thread;

void creater_handle(SafeQueue<std::shared_ptr<int> >* queue) 
{
    for (int i = 0; i < 20; i++) {
        std::shared_ptr<int> value = std::make_shared<int>(i);
        queue->push(value);

        std::this_thread::sleep_for(std::chrono::seconds(2));
        LOG(INFO) << "create " << (*value)  << ".";
    }
}

void customer_handle(SafeQueue<std::shared_ptr<int> >* queue) 
{
    for (int i = 0; i < 20; i++) {
        std::shared_ptr<int> value =  queue->pop();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        LOG(INFO) << "custom " << *value  << ".";
    }
}


int main(int argc, char* argv[])
{
    google::InstallFailureSignalHandler();
    google::InitGoogleLogging(argv[0]);

    FLAGS_stderrthreshold = 0;
    FLAGS_minloglevel = 0;

    SafeQueue<std::shared_ptr<int> > queue(4);

    std::thread t1(creater_handle, &queue);
    std::thread t2(customer_handle, &queue);

    t1.join();
    t2.join();

    std::cout << "wait key..." << std::endl;
    std::getchar(); 

    std::cout << "bye!" << std::endl;

    return 0;
}








