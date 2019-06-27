//
// Created by c on 26/06/2019 13:28
//

#ifndef ICE_ALGORITHM_STRING_JOIN_HH
#define ICE_ALGORITHM_STRING_JOIN_HH

/* include section */

/* class & function section */

namespace ice {

namespace algorithm {

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
		result.insert(std::end(result), std::begin(*sequence_it), std::end(*sequence_it));
		++sequence_it;
	}

	for (; sequence_it != sequence_end; ++sequence_it) {
		result.insert(std::end(result), std::begin(delimiter), std::end(delimiter));
		result.insert(std::end(result), std::begin(*sequence_it), std::end(*sequence_it));
	}
	return result;
}

} // namespace algorithm

} // namespace ice

#endif//


