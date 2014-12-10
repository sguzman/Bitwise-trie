#pragma once

#include <bitset>
#include <cstring>
#include <iostream>

namespace despairagus {
	namespace bitwise {
		using std::cout;
		using std::ostream;

		template <typename A>
		class binary final {
			template<typename B>
			using conref = const B &;

			constexpr static const size_t sz{sizeof(A)};
			constexpr static const size_t szB{sz << 3};

			using bitA = std::bitset<szB>;
			using byte = unsigned char;
			using bit = bool;

		public:
			explicit binary(void) = delete;

			explicit binary(conref<A> a) noexcept {
				byte *ptr = new byte[sz];
				memcpy((void *) ptr, (const void *const) &a, sz);

				for (size_t i = 0; i < sz; ++i) {
					static byte ch;
					ch = ptr[i];
					for (size_t j = 0; j < 8; ++j) {
						static bool bitVal;
						bitVal = binary<A>::getBitFromByte(ch, j);
						this->bits[binary<A>::getBitIdx(i, j)] = bitVal;
					}
				}

				delete[] ptr;
			}

			explicit binary(A &&a) noexcept : binary(a) {
			}

			template <typename... B>
			explicit binary(B... b) = delete;

			inline ~binary(void) noexcept {
				bits.~bitA();
			}

			inline void print(void) const noexcept {
				binary<A>::print(std::cout, *this);
			}

			inline bool getBit(conref<size_t> idx) const noexcept {
				return bits[idx];
			}

			inline bool getBit(size_t&& idx) const noexcept {
				return this->getBit(idx);
			}

			inline bool getBit(conref<int> idx) const noexcept {
				return this->getBit((size_t) idx);
			}

			inline bool getBit(int&& idx) const noexcept {
				return this->getBit((size_t) idx);
			}

			inline bool getBit(conref<byte> byteIdx, conref<byte> bitIdx) const noexcept {
				return binary<A>::getBit(*this, byteIdx, bitIdx);
			}

			inline bool getBit(byte&& byteIdx, byte&& bitIdx) const noexcept {
				return binary<A>::getBit(*this, byteIdx, bitIdx);
			}

			inline bool getBit(conref<int> byteIdx, conref<int> bitIdx) const noexcept {
				return binary<A>::getBit((byte) byteIdx + 0, (byte) bitIdx + 0);
			}

			inline bool getBit(int&& byteIdx, int&& bitIdx) const noexcept {
				return binary<A>::getBit((byte) byteIdx + 0, (byte) bitIdx + 0);
			}

			template <typename... B>
			inline bool getBit(B... b) const noexcept = delete;

			template <typename B>
			friend inline ostream &operator<<(ostream &os, conref<binary<B>> a) noexcept {
				a.print(os, a);

				return os;
			}

			template <typename B>
			friend inline ostream &operator<<(ostream &os, binary<B> &&a) noexcept {
				return operator<<(os, a);
			}

			explicit operator bool(void) const noexcept {
				return this->bits.all();
			}

		private:
			static inline void print(std::ostream &os, conref<binary<A>> a) noexcept {
				constexpr static size_t szOneLess{sz - 1};

				for (size_t i = 0; i < sz; ++i) {
					for (size_t j = 0; j < 8; ++j) {
						static bit bitIdx;
						bitIdx = (bit) a.bits[getBitIdx(i, j)];
						os << bitIdx;
					}

					if (szOneLess != i) {
						os << ' ';
					}
				}
			}

			static inline bit getBitFromByte(conref<byte> data, conref<byte> bitIdx) noexcept {
				return data & (1 << bitIdx);
			}

			static inline size_t getBitIdx(conref<size_t> byteIdx, conref<size_t> bitIdx) noexcept {
				return (byteIdx << 3) + bitIdx;
			}

			static inline bit getBit(conref<binary<A>> bits, conref<size_t> byteIdx, conref<size_t> bitIdx) noexcept {
				return bits[getBitIdx(byteIdx, bitIdx)];
			}

			bitA bits;
		};
	}
}