//
// Created by c on 30/01/2019 10:43 PM
//

#ifndef TOYS_VALUE_LIST_HH
#define TOYS_VALUE_LIST_HH

/* include section */

#include "toys/detail/value_list_impl.hh"

/* class & function section */

namespace toys {

// forward declarations
template<class T, T... Values> class value_list;

namespace detail {

// convert detail::ValueList to value_list
template<class List> struct value_list_converter;

template<class T, T... Values>
struct value_list_converter<detail::ValueList<T, Values...>> {
	using type = value_list<T, Values...>;
};

} // namespace detail

template<class T, T... Values>
class value_list {
protected:
	// type alias
	using value_type = T;
	using list = detail::ValueList<T, Values...>;

public:
	// element access
	/* front */
	struct front {
		static constexpr T value = detail::ListFront<list>::value;
	};

	static constexpr T front_v = front::value;

	/* back */
	struct back {
		static constexpr T value = detail::ListBack<list>::value;
	};

	static constexpr T back_v = back::value;

	/* index */
	template<unsigned I>
	struct get {
		static constexpr T value = detail::ListGet<list, I>::value;
	};

	template<unsigned I>
	static constexpr T get_v = get<I>::value;

	// capacity method
	/* empty */
	struct empty { static constexpr bool value = detail::ListEmpty<list>::value; };

	static constexpr bool empty_v = empty::value;

	/* size */
	struct size { static constexpr size_t value = detail::ListSize<list>::value; };

	static constexpr size_t size_v = size::value;

	// modifiers
	/* pop front */
	struct pop_front {
		using type = typename detail::value_list_converter<
			typename detail::ListPopFront<list>::type
			>::type;
	};

	using pop_front_t = typename pop_front::type;

	/* push front */
	template<T Value>
	struct push_front {
		using type = typename detail::value_list_converter<
			typename detail::VListPushFront<list, T, Value>::type
			>::type;
	};

	template<T Value>
	using push_front_t = typename push_front<Value>::type;

	/* pop back */
	struct pop_back {
		using type = typename detail::value_list_converter<
			typename detail::ListPopBack<list>::type
			>::type;
	};

	using pop_back_t = typename pop_back::type;

	/* push back */
	template<T Value>
	struct push_back {
		using type = typename detail::value_list_converter<
			typename detail::VListPushBack<list, T, Value>::type
			>::type;
	};

	template<T Value>
	using push_back_t = typename push_back<Value>::type;
};

} // namespace toys

#endif//


