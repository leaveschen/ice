//
// Created by c on 25/01/2019 01:22 PM
//

#ifndef TOYS_TYPE_LIST_HH
#define TOYS_TYPE_LIST_HH

/* include section */

/* class & function section */

namespace toys {

// forward declarations
template<class... Types> struct TypeList;

template<class List, unsigned I> struct ListAt;
template<class List> struct ListFront;
template<class List> struct ListBack;

template<class List> struct ListEmpty;
template<class List> struct ListSize;

template<class List> struct ListPopFront;
template<class List, class T> struct ListPushFront;
template<class List> struct ListPopBack;
template<class List, class T> struct ListPushBack;


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
	using type = typename ListBack<typename ListPopFront<Types...>::type>::type;
};


/* index */
template<unsigned I>
struct ListAt<TypeList<>, I> {}; // partial specialization for invalid case

template<class List>
struct ListAt<List, 0> {
	using type = typename ListFront<List>::type;
};

template<class List, unsigned I>
struct ListAt {
	using type = typename ListAt<typename ListPopFront<List>::type, I-1>::type;
};


// capacity method
/* empty */
template<> struct ListEmpty<TypeList<>> { static constexpr bool value = true; };

template<class... Types>
struct ListEmpty<TypeList<Types...>> { static constexpr bool value = false; };


/* size */
template<> struct ListSize<TypeList<>> { static constexpr size_t value = 0; };

template<class... Types>
struct ListSize<TypeList<Types...>> {
	static constexpr size_t value = ListSize<
		typename ListPopFront<TypeList<Types...>>::type
		>::value + 1;
};


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
namespace detail {
	template<class ListTarget, class ListSource> struct ListPopBackHelper;

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
} // namespace detail

template<> struct ListPopBack<TypeList<>> {}; // invalid case

template<class... Types>
struct ListPopBack<TypeList<Types...>> {
	using type = typename detail::ListPopBackHelper<TypeList<>, TypeList<Types...>>::type;
};

/* push back */
template<class Back, class... Types>
struct ListPushBack<TypeList<Types...>, Back> {
	using type = TypeList<Types..., Back>;
};

} // namespace toys

#endif//


