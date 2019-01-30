//
// Created by c on 30/01/2019 01:23 PM
//

#ifndef TOYS_DETAIL_FORWARD_DECLARATION_HH
#define TOYS_DETAIL_FORWARD_DECLARATION_HH

/* include section */

/* class & function section */

namespace toys {
namespace detail {

// type list
template<class... Types> struct TypeList;

// value list
template<class T, T... Values> struct ValueList;

// type & value list manipulation
template<class List, unsigned I> struct ListGet;
template<class List> struct ListFront;
template<class List> struct ListBack;

template<class List> struct ListEmpty;
template<class List> struct ListSize;

template<class List> struct ListPopFront;
template<class List, class T> struct ListPushFront;
template<class List> struct ListPopBack;
template<class List, class T> struct ListPushBack;

} // namespace detail
} // namespace toys

#endif//


