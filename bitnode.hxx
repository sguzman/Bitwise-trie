#pragma once

namespace despairagus {
	namespace bitnode {
		template <typename A>
		class bitnode {
			explicit bitnode(void) : zero{nullptr}, one{nullptr} {}
		public:
		private:
			bitnode* zero;
			bitnode* one;
		};
	}
}