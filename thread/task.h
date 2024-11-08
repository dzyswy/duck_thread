#pragma once

#include <memory>
#include <glog/logging.h>


namespace duck {
namespace thread {


enum ENUM_TASK_TYPE
{
    NORMAL_TASK = 0,
    QUIT_TASK,
};


class TaskData
{ 

};



class Task
{
public:
    Task(enum ENUM_TASK_TYPE type = NORMAL_TASK) : type_(type) {}
    Task(std::shared_ptr<TaskData> data, enum ENUM_TASK_TYPE type = NORMAL_TASK) : data_(data), type_(type) {}

    enum ENUM_TASK_TYPE type() {
        return type_;
    }

    virtual void process() {}

protected:
    std::shared_ptr<TaskData> data_;
    enum ENUM_TASK_TYPE type_;
};



}//namespace thread
}//namespace duck




