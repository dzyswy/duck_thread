#pragma once

#include "thread/task.h"
 

namespace duck {
namespace thread {


class SubTaskData : public TaskData
{
public:
    SubTaskData(int adda, int addb) : adda_(adda), addb_(addb), sum_(0) {}

public: 
    int adda_;
    int addb_;
    int sum_;
};

class SubTask : public Task
{
public:
    SubTask(std::shared_ptr<SubTaskData> data) : Task(data) {

    }

    void process() {
        // std::shared_ptr<SubTaskData> data = std::dynamic_pointer_cast<SubTaskData>data_;
        // data->sum_ = data->adda_ - data->addb_;
        // LOG(INFO) << "adda: " << data->adda_ << " - addb: " << data->addb_ << " = sum_: " << data->sum_ << std::endl;
    }
};


}//namespace thread
}//namespace duck

