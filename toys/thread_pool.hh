//
// Created by c on 09/01/2019 11:28
//

#ifndef TOYS_THREAD_POOL_HH
#define TOYS_THREAD_POOL_HH

/* include section */

#include <vector>
#include <thread>
#include <future>
#include <functional>
#include "toys/safe_queue.hh"

/* class & function section */

namespace toys {

template<size_t cnt>
class ThreadPool {
private:
	// members
	std::atomic_bool done_;
	std::mutex mtx_;
	std::vector<std::thread> threads_;
	SafeQueue<std::function<void()>> task_queue_;

	// thread function
	void work_() {
		for (;;) {
			std::function<void()> task;
			if (!task_queue_.wait_pop(task)) {
				continue;
			}
			task();
		}
	}

public:
	// constructor & destructor
	ThreadPool() {
		for (size_t i = 0; i < cnt; ++i) {
			threads_.emplace_back(std::thread(&ThreadPool::work_, this));
		}
	}
	ThreadPool(ThreadPool const&) = delete;
	ThreadPool& operator=(ThreadPool const&) = delete;
	~ThreadPool() { for (auto& t : threads_) { t.join(); }}

	// interface
	template<class F, class... Args>
	void submit(F&& f, Args&&... args) {
		auto task = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
		task_queue_.push(task);
	}

	// another interface for direct std::function object
	void submit(std::function<void()>&& f) {
		task_queue_.push(std::forward<std::function<void()>>(f));
	}

};

} // toys


#endif//


