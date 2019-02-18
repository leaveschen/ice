//
// Created by c on 18/02/2019 08:44 PM
//

#ifndef TOYS_THREAD_UTILITY_HH
#define TOYS_THREAD_UTILITY_HH

/* include section */

#include <utility>
#include <future>
#include <type_traits>

/* class & function section */

namespace toys {

template<class Callable>
class asynchronize {
protected:
	/* member */
	Callable f_;

public:
	/* ctor */
	explicit asynchronize(Callable f) : f_{f} {
		static_assert(std::is_function_v<typename std::remove_pointer<Callable>::type>,
				"argument must be a callable object");
	}

	/* operator() */
	template<class... Args>
	decltype(auto) operator()(Args&&... args) {
		return std::async(std::launch::async, f_, std::forward<Args>(args)...);
	}
};


namespace detail {

template<class Callable>
class future_unwrap {
protected:
	/* member */
	Callable f_;

public:
	/* ctor */
	explicit future_unwrap(Callable f) : f_{f} {
		static_assert(std::is_function_v<typename std::remove_pointer<Callable>::type>,
				"argument must be a callable object");
	}

	/* operator() */
	template<class... Args>
	decltype(auto) operator()(Args&&... args) {
		// call std::future::get to get the parameter
		return f_(std::forward<Args>(args).get()...);
	}
};

} // namespace detail


template<class Callable>
class async_adapter {
protected:
	/* member */
	Callable f_;

public:
	explicit async_adapter(Callable f) : f_{f} {
		static_assert(std::is_function_v<typename std::remove_pointer<Callable>::type>,
				"argument must be a callable object");
	}

	/* operator() */
	template<class... Args>
	decltype(auto) operator()(Args&&... args) {
		return std::async(std::launch::async,
				detail::future_unwrap{f_},
				std::forward<Args>(args)...);
	}
};

} // namespace toys

#endif//


