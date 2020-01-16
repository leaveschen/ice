//
// Created by c on 26/06/2019 13:50
//

#ifndef ICE_ALGORITHM_STRING_PREDICATE_HH
#define ICE_ALGORITHM_STRING_PREDICATE_HH

/* include section */

#include <iterator>

/* class & function section */

namespace ice {

namespace algorithm {

template<class InputRange, class TestRange, class Predicate>
inline bool startswith(InputRange const& input, TestRange const& test, Predicate p) {
	auto input_end = std::end(input);
	auto test_end = std::end(test);

	auto input_it = std::begin(input);
	auto test_it = std::begin(test);
	for (; input_it != input_end and test_it != test_end; ++input_it, ++test_it) {
		if (!p(*input_it, *test_it)) { return false; }
	}
	return test_it == test_end;
}

template<class InputRange, class TestRange>
bool startswith(InputRange const& input, TestRange const& test) {
	using input_value_type = typename InputRange::value_type;
	using test_value_type = typename TestRange::value_type;
	return startswith(input,
			test,
			[](input_value_type i, test_value_type t) {
			return i == t;
			});
}

namespace detail {

// only implement with bidirectional iterator
template<class InputIterator, class TestIterator, class Predicate>
inline bool endswith(InputIterator input_begin,
		InputIterator input_end,
		TestIterator test_begin,
		TestIterator test_end,
		Predicate p,
		std::bidirectional_iterator_tag) {
	for (; input_end != input_begin and test_end != test_begin; ) {
		if (!p(*(--input_end), *(--test_end))) { return false; }
	}
	return test_end == test_begin;
}

} // namespace detail

template<class InputRange, class TestRange, class Predicate>
inline bool endswith(InputRange const& input, TestRange const& test, Predicate p) {
	auto input_begin = std::begin(input);
	auto test_begin = std::begin(test);

	auto input_it = std::end(input);
	auto test_it = std::end(test);

	using iterator_category =
		typename std::iterator_traits<decltype(input_begin)>::iterator_category;
	return detail::endswith(input_begin, input_it, test_begin, test_it, p, iterator_category());
}

template<class InputRange, class TestRange>
bool endswith(InputRange const& input, TestRange const& test) {
	using input_value_type = typename InputRange::value_type;
	using test_value_type = typename TestRange::value_type;
	return endswith(input,
			test,
			[](input_value_type i, test_value_type t) {
			return i == t;
			});
}

} // namespace algorithm

} // namespace ice

#endif//


