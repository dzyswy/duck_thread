#pragma once
#include <chrono>
#include <memory>
#include <glog/logging.h>


namespace duck {
namespace thread {


enum ENUM_TASK_TYPE
{
    WORK_TASK = 0,
    QUIT_TASK,
};


class TaskData
{ 
public:
    std::string name_;
};



class Task
{
public:
    Task(enum ENUM_TASK_TYPE type = WORK_TASK) : type_(type) {}

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



class WorkTask : public Task
{
public:
    WorkTask(std::shared_ptr<TaskData> data) : Task(WORK_TASK) {
        set_data(data);
    }
};

class QuitTask : public Task
{
public:
    QuitTask() : Task(QUIT_TASK) {}
};



}//namespace thread
}//namespace duck




