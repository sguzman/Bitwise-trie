#pragma once

#include <iostream>

#include "binary.hxx"
#include "bitnode.hxx"

namespace despairagus {
	namespace bitwisetrie {
		using std::cout;
		using std::ostream;
		using namespace bitnodeNS;
		using namespace binaryNS;

		template <typename A>
		class bitwisetrie final {
			template<typename C>
			using conref = const C&;

			using bitA = std::bitset<sizeof(A) << 3>;
			using byte = unsigned char;
			using bit = bool;

			constexpr static const size_t limit{sizeof(A) << 3};

			static inline bitnode<B>* navigate(bitnode<B>* currNode, conref<A> data) {
			}

			static inline bitnode<B>* navigate(bitnode<B>* currNode, conref<A> data, conref<size_t> idx) {
				binary<A> bitHolder{data};

				return bitwisetrie<A>::navigate(currNode, bitHolder, idx);
			}

			static bitnode<B>* navigate(bitnode<B>* currNode, conref<binary<A>> bits, conref<size_t> idx) {
				if (idx < limit) {
					if (bits.getBit(idx)) {
						if (currNode->getOne() == nullptr) {
							currNode->setOne(new bitnode<B>);
						}

						return bitwisetrie<A>::navigate(currNode->getOne(), bits, idx + 1);
					} else {
						if (currNode->getZero() == nullptr) {
							currNode->setZero(new bitnode<B>);
						}

						return bitwisetrie<A>::navigate(currNode->getZero(), bits, idx + 1);
					}
				}

				return currNode;
			}

		public:
			explicit bitwisetrie(void) : root{new bitnode<B>} {}

			inline bool insertOnEmpty(conref<B> a) noexcept {

				if (leafNode->isEmpty()) {
					leafNode->setData(a);

					return true;
				}

				return false;
			}

			inline bool insertOnNotEmpty(conref<B> a) noexcept {
				bitnode<B>* leafNode = bitwisetrie<A,B>::navigate(root, a);

				if (leafNode->isNotEmpty()) {
					leafNode->setData(a);

					return true;
				}

				return false;
			}

			inline void insert(conref<B> a) noexcept {
				bitnode<B>* leafNode = bitwisetrie<A,B>::navigate(root, a);

				return leafNode->isNotEmpty();
			}

			inline bool notContains(conref<B> a) noexcept {
				bitnode<B>* leafNode = bitwisetrie<A,B>::navigate(root, a);

				return leafNode->isEmpty();
			}

		private:
			bitnode<B>* root;
		};
	}
}
