#pragma once

#include <iostream>

#include "binary.hxx"
#include "bitnode.hxx"

namespace despairagus {
	namespace bitwisetrie {
		using std::cout;
		using std::ostream;

		template <typename A>
		class bitwisetrie final {
			template<typename B>
			using conref = const B &;

			using bitA = std::bitset<sizeof(A) << 3>;
			using byte = unsigned char;
			using bit = bool;

			constexpr static const size_t limit{sizeof(A) << 3};

		public:
			explicit bitwisetrie(void) = delete;

		private:
			bitnode<A>* root;
		};
	}
}