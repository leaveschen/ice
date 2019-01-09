//
// Created by c on 09/01/2019 10:54
//

#ifndef TOYS_TYPES_HH
#define TOYS_TYPES_HH

/* include section */

#include <type_traits>
#include <utility>

/* class & function section */

namespace toys {

using Index = size_t;
using Real = float;

// singleton
template<class T>
struct Singleton {
	using value_type = T;
	static T& instance() {
		static T t;
		return t;
	}
};


// list of types
template<class...> struct type_list {};

/*
 * concatenate types into type_list
 */
template<class...> struct type_concat;

template<class T, class... Rest>
struct type_concat<T, Rest...> { using type = type_list<T, Rest...>; };

template<class T, class... Rest>
struct type_concat<T, type_list<Rest...>> { using type = type_list<T, Rest...>; };

template<>
struct type_concat<> { using type = type_list<>; };

/*
 * split types into T & type_list<Rest>
 */
template<class...> struct type_split;

template<> struct type_split<type_list<>>;

template<class T>
struct type_split<type_list<T>> {
	using first = T;
	using rest = type_list<>;
};

template<class T, class... Rest>
struct type_split<type_list<T, Rest...>> {
	using first = T;
	using rest = type_list<Rest...>;
};

/*
 * filter types with condition
 * type parameter: condition
 */
template<template<class> class Condition, class...> struct type_filter;

template<template<class> class Condition, class T, class... Rest>
struct type_filter<Condition, T, Rest...> {
	using type = typename std::conditional<
		Condition<T>::value,
		typename type_concat<T, typename type_filter<Condition, Rest...>::type>::type,
		typename type_filter<Condition, Rest...>::type
			>::type;
};

template<template<class> class Condition>
struct type_filter<Condition> { using type = type_list<>; };

} // namespace toys

#endif//


