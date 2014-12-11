#pragma once

namespace despairagus {
	namespace bitnode {
		template <typename A>
		class bitnode {
			template<typename B>
			using conref = const B &;

			using byte = unsigned char;
			using bit = bool;

		public:
			explicit bitnode(void) : zero{nullptr}, one{nullptr} {}

		private:
			bitnode* zero;
			bitnode* one;
		};
	}
}