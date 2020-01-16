//
// Created by c on 26/06/2019 13:28
//

#ifndef ICE_ALGORITHM_STRING_JOIN_HH
#define ICE_ALGORITHM_STRING_JOIN_HH

/* include section */

/* class & function section */

namespace ice {

namespace algorithm {

namespace detail {

// range insert helper, TODO: move into independent implementation file
template<class Range>
inline void range_insert_back(Range& range, Range const& insertion) {
	range.insert(std::end(range), std::begin(insertion), std::end(insertion));
}

template<class Range, std::size_t sz>
inline void range_insert_back(Range& range, typename Range::value_type const (&insertion)[sz]) {
	range.insert(std::end(range), std::begin(insertion), std::end(insertion));
}

template<class Range>
inline void range_insert_back(Range& range, typename Range::value_type const& insertion) {
	range.insert(std::end(range), insertion);
}

} // namespace detail

template<class Sequence, class DelimiterRange>
decltype(auto) join(Sequence const& sequence,
		DelimiterRange const& delimiter) {
	// TODO: implement with traits
	using result_type = typename Sequence::value_type;

	result_type result;
	auto sequence_it = std::begin(sequence);
	auto sequence_end = std::end(sequence);

	// insert first element
	if (sequence_it != sequence_end) {
		detail::range_insert_back(result, *sequence_it);
		++sequence_it;
	}

	for (; sequence_it != sequence_end; ++sequence_it) {
		detail::range_insert_back(result, delimiter);
		detail::range_insert_back(result, *sequence_it);
	}
	return result;
}

} // namespace algorithm

} // namespace ice

#endif//


