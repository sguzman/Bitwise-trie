#pragma once

namespace despairagus {
	namespace bitnode {
		template <typename A>
		class bitnode {
		public:
			explicit bitnode(void) : zero{nullptr}, one{nullptr} {}

		private:
			bitnode* zero;
			bitnode* one;
		};
	}
}