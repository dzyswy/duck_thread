#pragma once

#include "thread/task.h"
 

namespace duck {
namespace thread {


class AddTaskData : public TaskData
{
public:
    AddTaskData(int adda, int addb) : adda_(adda), addb_(addb), sum_(0) {}

public: 
    int adda_;
    int addb_;
    int sum_;
};

class AddTask : public WorkTask
{
public:
    AddTask(std::shared_ptr<TaskData> data) : WorkTask(data) {

    }


    void process() {
        std::shared_ptr<AddTaskData> data = std::static_pointer_cast<AddTaskData>(data_);
        data->sum_ = data->adda_ + data->addb_;
        LOG(INFO) << "AddTask adda: " << data->adda_ << " + addb: " << data->addb_ << " = sum_: " << data->sum_;
        std::this_thread::sleep_for(std::chrono::seconds(1)); 
    }
};


}//namespace thread
}//namespace duck

