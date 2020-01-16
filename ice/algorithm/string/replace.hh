//
// Created by c on 26/06/2019 13:48
//

#ifndef ICE_ALGORITHM_STRING_REPLACE_HH
#define ICE_ALGORITHM_STRING_REPLACE_HH

/* include section */

#include <ice/traits/type_traits.hh>

/* class & function section */

namespace ice {

namespace algorithm {

template<class InputIter, class ReplaceIter>
decltype(auto) replace(InputIter&& input_begin,
		InputIter&& input_end,
		ReplaceIter&& replace_begin) {}

} // namespace algorithm

} // namespace ice

#endif//


