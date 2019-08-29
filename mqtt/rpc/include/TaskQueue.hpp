#ifndef MINI_UTILS_TASK_QUEUE_INC
#define MINI_UTILS_TASK_QUEUE_INC

#include <memory>
#include <deque>
#include <functional>
#include <utility>
#include <mutex>
#include <condition_variable>

namespace mini_utils {

struct TaskBase {
    virtual ~TaskBase() {}
    virtual void run() = 0;
};

template <typename Fn>
struct Task: public TaskBase {
    Task(Fn &&fn): f_(std::forward<Fn>(fn)) {}

    virtual void run() { f_(); }

    Fn f_;
};

typedef std::shared_ptr<TaskBase> TaskPtr;

template <typename Fn>
std::shared_ptr<Task<Fn>> make_task_aux(Fn &&fn)
{
    return std::make_shared<Task<Fn>>(std::forward<Fn>(fn));
}

template <typename ...Args>
std::shared_ptr<TaskBase> make_task(Args &&...args)
{
    return make_task_aux(std::bind(std::forward<Args>(args)...));
}

typedef std::deque<TaskPtr> TaskPtrList;

class TaskQueue: public std::deque<std::shared_ptr<TaskBase>> {
private:
    std::mutex queueMtx_;
    std::condition_variable queueCV_;

public:
    template <typename ...Args>
    void pushTask(Args &&...args)
    {
        this->pushTask(make_task(std::forward<Args>(args)...));
    }

    void pushTask(std::shared_ptr<TaskBase> task) 
    {
        std::lock_guard<std::mutex> lck(queueMtx_);
        this->push_back(task);
        queueCV_.notify_one();
    }

	std::shared_ptr<TaskBase> popTask() 
    {
        std::unique_lock<std::mutex> lck(queueMtx_);
        while (this->empty()) {
            queueCV_.wait(lck);
        }
        auto task = this->front();
        this->pop_front();
        return task;
	}

    void popTask(std::deque<std::shared_ptr<TaskBase>> &task_list)
    {
        std::unique_lock<std::mutex> lck(queueMtx_);
        while (this->empty()) {
            queueCV_.wait(lck);
        }
        this->swap(task_list);
    }
};

}	// namespace mini_utils

#endif
