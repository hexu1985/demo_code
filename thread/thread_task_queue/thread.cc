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
    if (IsRunning()) {
        Stop();
    }
}

void Thread::Start() {
    assert(!thread_ && !task_queue_);
    task_queue_ = std::make_shared<TaskQueue>();
    thread_ = std::make_shared<std::thread>(&Thread::Handler, this);
}

void Thread::Stop() {
    task_queue_->PushTaskPrior(make_task(&this_thread_exit, (void *) 0));
    thread_->join();
    thread_.reset();
    task_queue_.reset();
}

void Thread::Handler()
{
    TaskQueue &incoming_queue = *task_queue_;
	std::deque<std::shared_ptr<TaskBase>> working_queue;
	while (true) {
		while (!working_queue.empty()) {
			std::shared_ptr<TaskBase> task = working_queue.front();
			working_queue.pop_front();
			task->run();
		}
		incoming_queue.SwapTasks(working_queue);
	}
}
