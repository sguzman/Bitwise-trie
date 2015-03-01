#pragma once

#include <iostream>

#include "binary.hxx"
#include "bitnode.hxx"

namespace despairagus {
	namespace bitwisetrieNS {
		using std::cout;
		using std::ostream;

		using namespace bitnodeNS;
		using namespace binaryNS;

		template <typename A, typename B>
		class bitwisetrie final {
			template<typename C>
			using conref = const C&;

			using bitA = std::bitset<sizeof(A) << 3>;
			using byte = unsigned char;
			using bit = bool;

			constexpr static const size_t limit{sizeof(A) << 3};

			static inline bitnode<B>* navigate(bitnode<B>* currNode, conref<A> data) {
				return bitwisetrie<A,B>::navigate(currNode, data, 0);
			}

			static inline bitnode<B>* navigate(bitnode<B>* currNode, conref<A> data, conref<size_t> idx) {
				binary<A> bitHolder{data};

				return bitwisetrie<A,B>::navigate(currNode, bitHolder, idx);
			}

			static bitnode<B>* navigate(bitnode<B>* currNode, conref<binary<A>> bits, conref<size_t> idx) {
				if (idx < limit) {
					if (bits.getBit(idx)) {
						if (currNode->getOne() == nullptr) {
							currNode->setOne(new bitnode<B>);
						}

						return bitwisetrie<A,B>::navigate(currNode->getOne(), bits, idx + 1);
					} else {
						if (currNode->getZero() == nullptr) {
							currNode->setZero(new bitnode<B>);
						}

						return bitwisetrie<A,B>::navigate(currNode->getZero(), bits, idx + 1);
					}
				}

				return currNode;
			}

		public:
			explicit bitwisetrie(void) : root{new bitnode<B>} {}

			template <typename... C>
			explicit bitwisetrie(C...) = delete;

			inline explicit operator bool (void) {
				return this->root->isNotBarren();
			}

			template <typename C>
			explicit operator C (void) = delete;

			inline bool insertOnEmpty(conref<A> a, conref<B> b) noexcept {
				bitnode<B>* leafNode = bitwisetrie<A,B>::navigate(root, a);

				if (leafNode->isEmpty()) {
					leafNode->setData(b);

					return true;
				}

				return false;
			}

			inline bool insertOnNotEmpty(conref<A> a, conref<B> b) noexcept {
				bitnode<B>* leafNode = bitwisetrie<A,B>::navigate(root, a);

				if (leafNode->isNotEmpty()) {
					leafNode->setData(b);

					return true;
				}

				return false;
			}

			inline void insert(conref<A> a, conref<B> b) noexcept {
				bitnode<B>* leafNode = bitwisetrie<A,B>::navigate(root, a);

				leafNode->setData(a);
			}

			inline bool remove(conref<A> a) noexcept {
				bitnode<B>* leafNode = bitwisetrie<A,B>::navigate(root, a);

				if (leafNode->isNotEmpty()) {
					leafNode->dump();

					return true;
				}

				return false;
			}

			inline bool contains(conref<A> a) noexcept {
				bitnode<B>* leafNode = bitwisetrie<A,B>::navigate(root, a);

				return leafNode->isNotEmpty();
			}

			inline bool notContains(conref<A> a) noexcept {
				return !this->contains(a);
			}

		private:
			bitnode<B>* root;
		};
	}
}
