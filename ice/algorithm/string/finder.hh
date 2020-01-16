//
// Created by c on 05/08/2019 15:12
//

#ifndef ICE_ALGORITHM_STRING_FINDER_HH
#define ICE_ALGORITHM_STRING_FINDER_HH

/* include section */

#include <algorithm>

/* class & function section */

namespace ice {

namespace algorithm {

template<class T>
class token_finder_functor {
private:
	T m_pattern;

public:
	// ctor
	token_finder_functor() : m_pattern() {}
	token_finder_functor(T pattern) : m_pattern(pattern) {}

	// call
	template<class Iterator>
	decltype(auto) operator()(Iterator begin, Iterator end) { return std::find(begin, end, m_pattern); }
};

} // namespace algorithm

} // namespace ice

#endif//


