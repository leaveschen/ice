//
// Created by c on 26/06/2019 14:36
//

/* include section */

#include <iostream>
#include <string>

#include <ice/algorithm/string.hh>

/* class & function section */

int main() {
	std::string input{"xijiancuoha"};
	std::string test{"xijian"};
	assert(!ice::algorithm::startswith(input, test));
}


