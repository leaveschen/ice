//
// Created by c on 26/01/2019 04:05 PM
//

#ifndef TOYS_TYPE_LIST_HH
#define TOYS_TYPE_LIST_HH

/* include section */

#include "toys/detail/type_list_impl.hh"

/* class & function section */

namespace toys {

// forward declarations
template<class... Types> class type_list;

namespace detail {

// convert detail::TypeList to type_list
template<class List> struct type_list_converter;

template<class... Types>
struct type_list_converter<detail::TypeList<Types...>> {
	using type = type_list<Types...>;
};

} // namespace detail

template<class... Types>
class type_list {
protected:
	// type alias
	using list = detail::TypeList<Types...>;

public:
	// element access
	/* front */
	struct front { using type = typename detail::ListFront<list>::type; };

	using front_t = typename front::type;

	/* back */
	struct back { using type = typename detail::ListBack<list>::type; };

	using back_t = typename back::type;

	/* index */
	template<unsigned I>
	struct at { using type = typename detail::ListAt<list, I>::type; };

	template<unsigned I>
	using at_t = typename at<I>::type;

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
		using type = typename detail::type_list_converter<
			typename detail::ListPopFront<list>::type
			>::type;
	};

	using pop_front_t = typename pop_front::type;

	/* push front */
	template<class T>
	struct push_front {
		using type = typename detail::type_list_converter<
			typename detail::ListPushFront<list, T>::type
			>::type;
	};

	template<class T>
	using push_front_t = typename push_front<T>::type;

	/* pop back */
	struct pop_back {
		using type = typename detail::type_list_converter<
			typename detail::ListPopBack<list>::type
			>::type;
	};

	using pop_back_t = typename pop_back::type;

	/* push back */
	template<class T>
	struct push_back {
		using type = typename detail::type_list_converter<
			typename detail::ListPushBack<list, T>::type
			>::type;
	};

	template<class T>
	using push_back_t = typename push_back<T>::type;
};

} // namespace toys

#endif// TOYS_TYPE_LIST_HH


