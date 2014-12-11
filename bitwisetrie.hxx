#pragma once

#include <iostream>

#include "binary.hxx"

namespace despairagus {
	namespace bitwisetrie {
		using std::cout;
		using std::ostream;

		template <typename A>
		class bitwisetrie {
			template<typename B>
			using conref = const B &;

			using bitA = std::bitset<szB>;
			using byte = unsigned char;
			using bit = bool;

			explicit bitwisetrie(void) = delete;
		};
	}
}