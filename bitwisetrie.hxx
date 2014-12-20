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

			static inline bitnode<A>* navigate(bitnode<A>* currNode, conref<A> data) {
				return bitwisetrie<A>::navigate(currNode, data, 0);
			}

			static inline bitnode<A>* navigate(bitnode<A>* currNode, conref<A> data, conref<size_t> idx) {
				binary<A> bitHolder{data};

				return bitwisetrie<A>::navigate(currNode, bitHolder, idx);
			}

			static bitnode<A>* navigate(bitnode<A>* currNode, conref<binary<A>> bits, conref<size_t> idx) {
				if (idx < limit) {
					if (bits.getBit(idx)) {
						if (currNode->getOne() == nullptr) {
							currNode->setOne(new bitnode<A>);
						}

						return bitwisetrie<A>::navigate(currNode->getOne(), bits, idx + 1);
					} else {
						if (currNode->getZero() == nullptr) {
							currNode->setZero(new bitnode<A>);
						}

						return bitwisetrie<A>::navigate(currNode->getZero(), bits, idx + 1);
					}
				}

				return currNode;
			}

		public:
			explicit bitwisetrie(void) : root{new bitnode<A>} {}

			inline bool insertOnEmpty(conref<A> a) noexcept {
				bitnode<A>* leafNode = bitwisetrie<A>::navigate(root, a);

				if (leafNode->isEmpty()) {
					leafNode->setData(a);

					return true;
				}

				return false;
			}

			inline bool insertOnNotEmpty(conref<A> a) noexcept {
				bitnode<A>* leafNode = bitwisetrie<A>::navigate(root, a);

				if (leafNode->isNotEmpty()) {
					leafNode->setData(a);

					return true;
				}

				return false;
			}

		private:
			bitnode<A>* root;
		};
	}
}