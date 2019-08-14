//
// Created by c on 26/06/2019 14:36
//

/* include section */

#include <iostream>
#include <string>
#include <vector>

#include <ice/algorithm/string.hh>

/* class & function section */

template<class T>
void print_vector(std::vector<T> const& vec) {
	auto it = vec.begin();
	auto end = vec.end();
	if (it != end) {
		std::cout << *it;
	} else {
		std::cout << "\n";
		return;
	}
	for (++it; it != end; ++it) std::cout << "/" << *it;
	std::cout << "\n";
}

void test_format() {
	ice::format("xixi", 1, 2);
}

void test_predicate() {
	std::cout << "\n[test split]\n";
	std::string input{"xijiancuoha"};
	std::string test1{"xijian"};
	std::string test2{"cuoha"};
	std::cout << ice::startswith(input, test1) << "\n";
	std::cout << ice::startswith(input, test2) << "\n";
	std::cout << ice::endswith(input, test1) << "\n";
	std::cout << ice::endswith(input, test2) << "\n";
}

void test_join() {
	std::cout << "\n[test join]\n";
	std::vector<std::string> sequence1{"ab", "cd", "ef", "gh"};
	std::vector<std::string> sequence2{"ab"};
	std::vector<std::string> sequence3{};
	std::string delimiter{"-"};
	std::cout << ice::join(sequence1, delimiter) << "\n";
	std::cout << ice::join(sequence2, delimiter) << "\n";
	std::cout << ice::join(sequence3, delimiter) << "\n";
	std::cout << ice::join(sequence1, "#") << "\n";
	std::cout << ice::join(sequence1, '*') << "\n";
}

void test_split() {
	std::cout << "\n[test split]\n";
	std::string str{"xi ha hu"};

	std::vector<std::string> vec;
	ice::split(vec, str, ' ');
	print_vector(vec);
	ice::split(vec, str, 'h');
	print_vector(vec);
	ice::split(vec, str, 'y');
	print_vector(vec);
}


int main() {
	test_format();
	test_predicate();
	test_join();
	test_split();
}


