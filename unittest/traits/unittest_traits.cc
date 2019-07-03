//
// Created by c on 03/07/2019 17:57
//

/* include section */

#include <iostream>
#include <utility>
#include <ice/traits/type_traits.hh>

/* class & function section */


struct A { void foo(); };
struct B {};

template<class T>
using has_foo_t = decltype(std::declval<T&>().foo());

void test_has_member_function() {
	std::cout << "[test has member function]\n";
	std::cout << "A has foo: " << ice::is_detected<has_foo_t, A>::value << "\n";
	std::cout << "B has foo: " <<ice::is_detected<has_foo_t, B>::value << "\n";
}

int main() {
	test_has_member_function();
}


