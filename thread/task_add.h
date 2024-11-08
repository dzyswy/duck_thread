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

class AddTask : public Task
{
public:
    AddTask(std::shared_ptr<AddTaskData> data) : Task(data) {

    }

    void process() {
        // std::shared_ptr<AddTaskData> data = std::dynamic_pointer_cast<AddTaskData>data_;
        // data->sum_ = data->adda_ + data->addb_;
        // LOG(INFO) << "adda: " << data->adda_ << " + addb: " << data->addb_ << " = sum_: " << data->sum_;
    }
};


}//namespace thread
}//namespace duck

