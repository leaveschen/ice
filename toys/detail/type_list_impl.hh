//
// Created by c on 25/01/2019 01:22 PM
//

#ifndef TOYS_DETAIL_TYPE_LIST_IMPL_HH
#define TOYS_DETAIL_TYPE_LIST_IMPL_HH

/* include section */

#include "toys/detail/forward_declaration.hh"

/* class & function section */

namespace toys {
namespace detail {

// basic type list definition
template<class... Types> struct TypeList {};


// element access
/* front */
template<> struct ListFront<TypeList<>> {}; // invalid case

template<class Front, class... Rest>
struct ListFront<TypeList<Front, Rest...>> { using type = Front; };


/* back */
template<> struct ListBack<TypeList<>> {}; // invalid case

template<class T>
struct ListBack<TypeList<T>> { using type = T; };

template<class... Types>
struct ListBack<TypeList<Types...>> {
	using type = typename ListBack<typename ListPopFront<TypeList<Types...>>::type>::type;
};


/* index */
template<unsigned I>
struct ListGet<TypeList<>, I> {}; // partial specialization for invalid case

template<class Front, class... Rest>
struct ListGet<TypeList<Front, Rest...>, 0> {
	using type = Front;
};

template<unsigned I, class Front, class... Rest>
struct ListGet<TypeList<Front, Rest...>, I> {
	using type = typename ListGet<TypeList<Rest...>, I-1>::type;
};


// capacity method
/* empty */
template<class... Types>
struct ListEmpty<TypeList<Types...>> { static constexpr bool value = sizeof...(Types) == 0; };


/* size */
template<class... Types>
struct ListSize<TypeList<Types...>> { static constexpr size_t value = sizeof...(Types); };


// modifiers
/* pop front */
template<> struct ListPopFront<TypeList<>> {}; // invalid case

template<class Front, class... Rest>
struct ListPopFront<TypeList<Front, Rest...>> { using type = TypeList<Rest...>; };


/* push front */
template<class Front, class... Types>
struct ListPushFront<TypeList<Types...>, Front> {
	using type = TypeList<Front, Types...>;
};


/* pop back */
// pop back helper
template<class ListTarget, class Front>
struct ListPopBackHelper<ListTarget, TypeList<Front>> {
	using type = ListTarget;
};

template<class ListTarget, class Front, class... Rest>
struct ListPopBackHelper<ListTarget, TypeList<Front, Rest...>> {
	using type = typename ListPopBackHelper<
		typename ListPushBack<ListTarget, Front>::type,
		TypeList<Rest...>>::type;
};

template<> struct ListPopBack<TypeList<>> {}; // invalid case

template<class... Types>
struct ListPopBack<TypeList<Types...>> {
	using type = typename ListPopBackHelper<TypeList<>, TypeList<Types...>>::type;
};


/* push back */
template<class Back, class... Types>
struct ListPushBack<TypeList<Types...>, Back> {
	using type = TypeList<Types..., Back>;
};

} // namespace detail
} // namespace toys

#endif// TOYS_DETAIL_TYPE_LIST_IMPL_HH


