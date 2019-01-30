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




// capacity method
/* empty */
template<class T, T... Values>
struct ListEmpty<ValueList<T, Values...>> { static constexpr bool value = sizeof...(Values) == 0; };


/* size */
template<class T, T... Values>
struct ListSize<ValueList<T, Values...>> { static constexpr size_t value = sizeof...(Values); };

} // namespace detail
} // namespace toys

#endif//


