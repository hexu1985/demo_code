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

struct Task_base {
	virtual ~Task_base() {}
	virtual void run() = 0;
};

template <typename Fn>
struct Task: public Task_base {
	Task(Fn &&fn): f_(std::forward<Fn>(fn)) {}

	virtual void run() { f_(); }

	Fn f_;
};

template <typename Fn>
std::shared_ptr<Task<Fn>> make_task_aux(Fn &&fn)
{
	return std::make_shared<Task<Fn>>(std::forward<Fn>(fn));
}

template <typename ...Args>
std::shared_ptr<Task_base> make_task(Args &&...args)
{
	return make_task_aux(std::bind(std::forward<Args>(args)...));
}

class Thread;

class Task_queue: public std::deque<std::shared_ptr<Task_base>> {
private:
	std::mutex queue_mtx_;
	std::condition_variable queue_cv_;

public:
	void push_task(std::shared_ptr<Task_base> task) {
		std::lock_guard<std::mutex> lck(queue_mtx_);
		this->push_back(task);
        queue_cv_.notify_one();
	}	

    friend class Thread;

private:
	void swap_task_queue(std::deque<std::shared_ptr<Task_base>> &task_queue) {
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

    void start();

    void stop();

    bool is_run() {
        return (thread_ ? true : false);
    }

    std::shared_ptr<Task_queue> get_task_queue() {
        return task_queue_;
    }

    Thread(const Thread &) = delete;
    void operator =(const Thread &) = delete;

private:
    void task_process();

    std::string name_;
    std::shared_ptr<std::thread> thread_;
    std::shared_ptr<Task_queue> task_queue_;
};

#endif 
