//
// Created by c on 26/06/2019 14:36
//

/* include section */

#include <iostream>
#include <string>
#include <vector>

#include <ice/algorithm/string.hh>

/* class & function section */

void test_predicate() {
	std::string input{"xijiancuoha"};
	std::string test1{"xijian"};
	std::string test2{"cuoha"};
	std::cout << ice::algorithm::startswith(input, test1) << "\n";
	std::cout << ice::algorithm::startswith(input, test2) << "\n";
	std::cout << ice::algorithm::endswith(input, test1) << "\n";
	std::cout << ice::algorithm::endswith(input, test2) << "\n";
}

void test_join() {
	std::vector<std::string> sequence1{"ab", "cd", "ef", "gh"};
	std::vector<std::string> sequence2{"ab"};
	std::vector<std::string> sequence3{};
	std::string delimiter{"-"};
	std::cout << ice::algorithm::join(sequence1, delimiter) << "\n";
	std::cout << ice::algorithm::join(sequence2, delimiter) << "\n";
	std::cout << ice::algorithm::join(sequence3, delimiter) << "\n";
}

int main() {
	test_predicate();
	test_join();
}


