#ifndef MINI_UTILS_WORKER_THREAD_INC
#define MINI_UTILS_WORKER_THREAD_INC

#include <thread>
#include <string>

#include "TaskQueue.hpp"

namespace mini_utils {

class WorkerThread {
public:
    WorkerThread(const std::string &name);

    ~WorkerThread();

    void start();

    void stop();

    bool isRun();

    std::shared_ptr<TaskQueue> getTaskQueue();

    const std::string &getName() const;

private:
    WorkerThread(const WorkerThread &) = delete;
    void operator =(const WorkerThread &) = delete;

private:
    std::string name_;
    std::shared_ptr<std::thread> thread_;
    std::shared_ptr<TaskQueue> taskQueue_;
};

namespace current_worker_thread {

std::shared_ptr<TaskQueue> get_task_queue();

const std::string &get_name();

}   // namespace this_thread

}	// namespace mini_utils

#endif 
