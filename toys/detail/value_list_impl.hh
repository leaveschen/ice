//
// Created by c on 30/01/2019 01:18 PM
//

#ifndef TOYS_DETAIL_VALUE_LIST_IMPL_HH
#define TOYS_DETAIL_VALUE_LIST_IMPL_HH

/* include section */

#include "toys/detail/forward_declaration.hh"

/* class & function section */

namespace toys {
namespace detail {

// basic value list definition
template<class T, T... Values> struct ValueList {};


// element access
/* front */
template<class T> struct ListFront<ValueList<T>> {}; // invalid case

template<class T, T Front, T... Rest>
struct ListFront<ValueList<T, Front, Rest...>> { static constexpr T value = Front; };


/* back */
template<class T> struct ListBack<ValueList<T>> {}; // invalid case

template<class T, T Value>
struct ListBack<ValueList<T, Value>> { static constexpr T value = Value; };

template<class T, T Front, T... Rest>
struct ListBack<ValueList<T, Front, Rest...>> {
	static constexpr T value = ListBack<ValueList<T, Rest...>>::value;
};


/* index */
template<unsigned I, class T>
struct ListGet<ValueList<T>, I> {}; // invalid case

template<class T, T Front, T... Values>
struct ListGet<ValueList<T, Front, Values...>, 0> {
	static constexpr T value = Front;
};

template<unsigned I, class T, T Front, T... Values>
struct ListGet<ValueList<T, Front, Values...>, I> {
	static constexpr T value = ListGet<ValueList<T, Values...>, I-1>::value;
};


// capacity method
/* empty */
template<class T, T... Values>
struct ListEmpty<ValueList<T, Values...>> { static constexpr bool value = sizeof...(Values) == 0; };


/* size */
template<class T, T... Values>
struct ListSize<ValueList<T, Values...>> { static constexpr size_t value = sizeof...(Values); };


// modifiers
/* pop front */
template<class T>
struct ListPopFront<ValueList<T>> {}; // invalid case

template<class T, T Front, T... Values>
struct ListPopFront<ValueList<T, Front, Values...>> {
	using type = ValueList<T, Values...>;
};


/* push front */
template<class T, T Front, T... Values>
struct VListPushFront<ValueList<T, Values...>, T, Front> {
	using type = ValueList<T, Front, Values...>;
};


/* pop back */
// pop back helper
template<class ListTarget, class T, T Front>
struct ListPopBackHelper<ListTarget, ValueList<T, Front>> {
	using type = ListTarget;
};

template<class ListTarget, class T, T Front, T... Values>
struct ListPopBackHelper<ListTarget, ValueList<T, Front, Values...>> {
	using type = typename ListPopBackHelper<
		typename VListPushBack<ListTarget, T, Front>::type,
		ValueList<T, Values...>>::type;
};

template<class T>
struct ListPopBack<ValueList<T>> {}; // invalid case

template<class T, T... Values>
struct ListPopBack<ValueList<T, Values...>> {
	using type = typename ListPopBackHelper<ValueList<T>, ValueList<T, Values...>>::type;
};


/* push back */
template<class T, T Back, T... Values>
struct VListPushBack<ValueList<T, Values...>, T, Back> {
	using type = ValueList<T, Values..., Back>;
};

} // namespace detail
} // namespace toys

#endif//


