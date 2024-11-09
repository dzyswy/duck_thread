#pragma once
#include <chrono>
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

    enum ENUM_TASK_TYPE type() {
        return type_;
    }

    void set_data(std::shared_ptr<TaskData> data) {
        data_ = data;
    }

    virtual void process() {}

protected:
    std::shared_ptr<TaskData> data_;
    enum ENUM_TASK_TYPE type_;
};



class QuitTask : public Task
{
public:
    QuitTask() : Task(QUIT_TASK) {}
};



}//namespace thread
}//namespace duck




