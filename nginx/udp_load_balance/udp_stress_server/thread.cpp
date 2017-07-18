#include <assert.h>
#include <iostream>

#include "thread.h"

namespace {

void this_thread_exit(void *)
{
	std::cout << "task to stop process thread" << std::endl;
	pthread_exit(NULL);
}

}

Thread::Thread(const std::string &name): name_(name) {
}

Thread::~Thread() {
    if (is_run()) {
        stop();
    }
}

void Thread::start() {
    assert(!thread_ && !task_queue_);
    task_queue_ = std::make_shared<Task_queue>();
    thread_ = std::make_shared<std::thread>(&Thread::task_process, this);
}

void Thread::stop() {
    task_queue_->push_task(make_task(&this_thread_exit, (void *) 0));
    thread_->join();
    thread_.reset();
    task_queue_.reset();
}

void Thread::task_process()
{
    Task_queue &incoming_queue = *task_queue_;
	std::deque<std::shared_ptr<Task_base>> working_queue;
	while (true) {
		while (!working_queue.empty()) {
			std::shared_ptr<Task_base> task = working_queue.front();
			working_queue.pop_front();
			task->run();
		}
		incoming_queue.swap_task_queue(working_queue);
	}
}
