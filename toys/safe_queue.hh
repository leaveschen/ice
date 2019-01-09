//
// Created by c on 09/01/2019 11:09
//

#ifndef TOYS_SAFE_QUEUE_HH
#define TOYS_SAFE_QUEUE_HH

/* include section */

#include <atomic>
#include <memory>
#include <mutex>
#include <queue>
#include <condition_variable>

/* class & function section */

namespace toys {

template<class T>
class SafeQueue {
private:
	// members
	std::atomic_bool valid_;
	std::queue<T> queue_;
	std::mutex mtx_;
	std::condition_variable cond_;

public:
	// constructor and destructor
	SafeQueue() : valid_(true) {}
	SafeQueue(SafeQueue const&) = delete;
	SafeQueue& operator=(SafeQueue const&) = delete;
	~SafeQueue() {
		std::lock_guard<std::mutex> lk(mtx_);
		valid_ = false;
		cond_.notify_all();
	}

	// interface
	void push(T const& v) {
		std::lock_guard<std::mutex> lk(mtx_);
		queue_.push(v);
		cond_.notify_one();
	}

	inline bool wait_pop(T& v) {
		std::unique_lock<std::mutex> lk(mtx_);
		cond_.wait(lk, [&](){ return !queue_.empty() || !valid_; });
		if (!valid_) { return false; }
		v = std::move(queue_.front());
		queue_.pop();
		return true;
	}

	inline bool try_pop(T& v) {
		std::lock_guard<std::mutex> lk(mtx_);
		if (queue_.empty()) {
			return false;
		} else {
			v = std::move(queue_.front());
			queue_.pop();
		}
		return true;
	}
};

} // toys

#endif//


