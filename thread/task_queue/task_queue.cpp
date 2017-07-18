#include <utility>
#include <functional>
#include <queue>
#include <mutex>
#include <thread>
#include <memory>
#include <iostream>
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
Task<Fn> *make_task_helper(Fn &&fn)
{
	return new Task<Fn>(std::forward<Fn>(fn));
}

template <typename ...Args>
Task_base *make_task(Args &&...args)
{
	return make_task_helper(std::bind(std::forward<Args>(args)...));
}

class Task_queue: public std::queue<Task_base *> {
	std::mutex queue_mtx_;

public:
	void push_task(Task_base *task) {
		std::lock_guard<std::mutex> lck(queue_mtx_);
		this->push(task);
	}	

	void swap_task(std::queue<Task_base *> &task_queue) {
		std::lock_guard<std::mutex> lck(queue_mtx_);
		if (!this->empty()) {
			this->swap(task_queue);
		}
	}
	
};

void processor(Task_queue &incoming_queue)
{
	std::queue<Task_base *> work_queue;
	while (true) {
		while (!work_queue.empty()) {
			Task_base *task = work_queue.front();
			work_queue.pop();
			task->run();
			delete task;
		}
		incoming_queue.swap_task(work_queue);
	}
}

void print_int(int i)
{
	std::cout << __func__ << "(" << i << ")" << std::endl;
}

void print_string(std::string str)
{
	std::cout << __func__ << "(" << str << ")" << std::endl;
}

class Foo {
	int n_;
public:
	Foo(int n): n_(n) {}

	void print()
	{
		std::cout << "Foo::" << __func__ << "(" << n_++ << ")" << std::endl;
	}
};

void process_exit()
{
	std::cout << "task to stop process thread" << std::endl;
	pthread_exit(NULL);
}

int main()
{
	Foo foo(1);

	Task_queue task_queue;
	std::thread proc_thread(processor, std::ref(task_queue));
	for (int i = 0; i < 10; i++) {
		task_queue.push_task(make_task(print_int, i));
		task_queue.push_task(make_task(print_string, std::string("hello")));
		task_queue.push_task(make_task(&Foo::print, &foo));
	}
	task_queue.push_task(make_task(process_exit));
	proc_thread.join();
	return 0;
}

