#ifndef __THREAD_H
#define __THREAD_H

#include <utility>
#include <functional>
#include <deque>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <memory>
#include <string>

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

template <typename Fn>
std::shared_ptr<Task<Fn>> make_task_helper(Fn &&fn)
{
	return std::make_shared<Task<Fn>>(std::forward<Fn>(fn));
}

template <typename ...Args>
std::shared_ptr<TaskBase> make_task(Args &&...args)
{
	return make_task_helper(std::bind(std::forward<Args>(args)...));
}

class Thread;

class TaskQueue: public std::deque<std::shared_ptr<TaskBase>> {
private:
	std::mutex queue_mtx_;
	std::condition_variable queue_cv_;

public:
	void PushTask(std::shared_ptr<TaskBase> task) {
		std::lock_guard<std::mutex> lck(queue_mtx_);
		this->push_back(task);
        queue_cv_.notify_one();
	}	

	void PushTaskPrior(std::shared_ptr<TaskBase> task) {
		std::lock_guard<std::mutex> lck(queue_mtx_);
		this->push_front(task);
        queue_cv_.notify_one();
	}	

    friend class Thread;

private:
	void SwapTasks(std::deque<std::shared_ptr<TaskBase>> &task_queue) {
		std::unique_lock<std::mutex> lck(queue_mtx_);
        while (this->empty()) {
            queue_cv_.wait(lck);
        }
	    this->swap(task_queue);
	}
};

class Thread {
public:
    Thread(const std::string &name);
    ~Thread();

    void Start();

    void Stop();

    bool IsRunning() {
        return (thread_ ? true : false);
    }

    std::shared_ptr<TaskQueue> GetTaskQueue() {
        return task_queue_;
    }

    Thread(const Thread &) = delete;
    void operator =(const Thread &) = delete;

private:
    void Handler();

    std::string name_;
    std::shared_ptr<std::thread> thread_;
    std::shared_ptr<TaskQueue> task_queue_;
};

#endif 
