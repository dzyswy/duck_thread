#pragma once

#include "thread/task.h"
 

using namespace duck::thread;

namespace duck {
namespace task {


class SubTaskData : public TaskData
{
public:
    SubTaskData(int adda, int addb) : adda_(adda), addb_(addb), sum_(0) {}

public: 
    int adda_;
    int addb_;
    int sum_;
};

class SubTask : public WorkTask
{
public:
    SubTask(std::shared_ptr<TaskData> data) : WorkTask(data) {

    }

    void process() {
        std::shared_ptr<SubTaskData> data = std::static_pointer_cast<SubTaskData>(data_);
        data->sum_ = data->adda_ - data->addb_;
        LOG(INFO) << "SubTask adda: " << data->adda_ << " - addb: " << data->addb_ << " = sum_: " << data->sum_ << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
};


}//namespace task
}//namespace duck

