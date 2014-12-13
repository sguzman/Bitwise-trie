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
			inline explicit bitnode(void) : zero{nullptr}, one{nullptr}, data{nullptr} {}

			template <typename... A>
			explicit bitnode(A... a) = delete;

		private:
			bitnode* zero;
			bitnode* one;

			A* data;
		};
	}
}