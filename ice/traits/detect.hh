//
// Created by c on 03/07/2019 15:38
//

#ifndef ICE_TRAITS_DETECT_HH
#define ICE_TRAITS_DETECT_HH

/* include section */

#include <type_traits>

/* class & function section */

namespace ice {

namespace traits {

namespace detail {

// holder helper
struct detect_holder {};

template<class T>
using detect_holder_t = detect_holder;

template<class Holder, template<class...> class Op, class... Args>
struct detect {
	using value_t = std::false_type;
};

template<template<class...> class Op, class... Args>
struct detect<detect_holder_t<Op<Args...>>, Op, Args...> {
	using value_t = std::true_type;
};

} // namespace detail

template<template<class...> class Op, class... Args>
using is_detected = typename detail::detect<detail::detect_holder, Op, Args...>::value_t;

} // namespace traits

} // namespace ice

#endif//


