#include "thread/queue.h"
#include "thread/thread.h"
#include <chrono>


using namespace duck::thread;

SafeQueue<std::shared_ptr<int> > g_queue(4);


class CreaterThread : public Thread
{
public:
    void process() {

        for (int i = 0; i < 20; i++) {
            std::shared_ptr<int> value = std::make_shared<int>(i);
            g_queue.push(value);

            std::this_thread::sleep_for(std::chrono::seconds(2));
            LOG(INFO) << "create " << (*value)  << ".";
        }

    }
};

class CustomerThread : public Thread
{
public:
    void process() {
        for (int i = 0; i < 20; i++) {
            std::shared_ptr<int> value =  g_queue.pop();
            std::this_thread::sleep_for(std::chrono::seconds(1));
            LOG(INFO) << "custom " << *value  << ".";
        }
    }

};




int main(int argc, char* argv[])
{
    google::InstallFailureSignalHandler();
    google::InitGoogleLogging(argv[0]);

    FLAGS_stderrthreshold = 0;
    FLAGS_minloglevel = 0;

    CreaterThread creater_thd;
    CustomerThread customer_thd;

    creater_thd.start();
    customer_thd.start();

    creater_thd.join();
    customer_thd.join();

    std::cout << "wait key..." << std::endl;
    std::getchar(); 

    std::cout << "bye!" << std::endl;

    return 0;
}








