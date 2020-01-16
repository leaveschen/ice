//
// Created by c on 26/06/2019 13:24
//

#ifndef ICE_ALGORITHM_STRING_SPLIT_HH
#define ICE_ALGORITHM_STRING_SPLIT_HH

/* include section */

#include <iterator>
#include <ice/algorithm/string/finder.hh>

/* class & function section */

namespace ice {

namespace algorithm {

namespace detail {

template<class Iterator>
struct string_iter_traits {
	using char_t = typename std::iterator_traits<Iterator>::value_type;
	using value_type = typename std::basic_string<char_t>;
	using reference = value_type&;
};

// NOTE: Do not use this class directly
template<class Iterator, class Finder>
struct split_iterator {
	// members
	Iterator m_begin;
	Iterator m_end;
	Finder m_finder;

	// types
	using value_type = typename std::iterator_traits<Iterator>::value_type;
	using difference_type = typename std::iterator_traits<Iterator>::difference_type;
	using reference = typename string_iter_traits<Iterator>::reference;
	using pointer = typename std::iterator_traits<Iterator>::pointer;
	using iterator_category = std::input_iterator_tag;
	using dereference_type = typename string_iter_traits<Iterator>::value_type;

	// constructors
	split_iterator(Iterator begin) :
		m_begin(begin), m_end(), m_finder() {}
	split_iterator(Iterator begin, Iterator end, Finder finder) :
		m_begin(begin), m_end(end), m_finder(finder) {}

	// XXX: here may cause unexpected result
	dereference_type operator*() {
		auto next = m_finder(m_begin, m_end);
		dereference_type ret(m_begin, next);
		// set next to avoid dupulicated compute in operator++
		m_begin = next;
		return ret;
	}
	split_iterator& operator++() {
		if (m_begin != m_end) { ++m_begin; }
		return *this;
	}

	bool operator==(split_iterator& other) const { return m_begin == other.m_begin; }
	bool operator!=(split_iterator& other) const { return m_begin != other.m_begin; }
};

} // namespace detail

template<class Sequence, class Range, class Finder>
void inline split_finder(Sequence& result, Range const& input, Finder const& finder) {
	auto b = std::begin(input);
	auto e = std::end(input);
	using It = decltype(b);
	detail::split_iterator<It, Finder> iter_begin{b, e, finder};
	detail::split_iterator<It, Finder> iter_end{e};
	Sequence temp{iter_begin, iter_end};
	result.swap(temp);
}

template<class Sequence, class Range>
void split(Sequence& result, Range const& input,
		typename Range::value_type token) {
	using token_type = typename Range::value_type;
	using Finder = token_finder_functor<token_type>;
	Finder finder{token};
	split_finder(result, input, finder);
}

} // namespace algorithm

} // namespace ice

#endif//


