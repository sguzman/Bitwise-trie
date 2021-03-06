#pragma once

#include <bitset>
#include <cstring>
#include <string>
#include <iostream>

namespace {
	namespace binaryNS {
		using std::cout;
		using std::ostream;

		template <typename A>
		class binary final {
			template<typename B>
			using conref = const B &;

			using bitA = std::bitset<sizeof(A) << 3>;
			using byte = unsigned char;
			using bit = bool;

			constexpr static const size_t sz{sizeof(A)};
			constexpr static const size_t szB{sz << 3};
			constexpr static const size_t szOneLess{sz - 1};

			static inline std::ostream& print(std::ostream &os, conref<binary<A>> a) noexcept {
				return os << a.bits;
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

		public:
			explicit binary(void) = delete;

			inline explicit binary(conref<A> a) noexcept {
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

			inline explicit binary(A &&a) noexcept : binary(a) {}

			template <typename... B>
			explicit binary(B... b) = delete;

			inline ~binary(void) noexcept {
				bits.~bitA();
			}

			inline explicit operator bool (void) const noexcept {
				return this->bits.all();
			}

			template <typename B>
			inline explicit operator B (void) const noexcept = delete;

			inline bool operator [](size_t idx) const noexcept {
				return this->getBit(idx);
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

			inline bool getBit(conref<size_t> a, conref<size_t> b) const noexcept {
				return this->getBit(binary<A>::getBitIdx((byte) a, (byte) b));
			}

			inline bool getBit(size_t &&a, size_t &&b) const noexcept {
				return this->getBit(a, b);
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
				return binary<A>::getBit((size_t) byteIdx, (size_t) bitIdx);
			}

			inline bool getBit(int&& byteIdx, int&& bitIdx) const noexcept {
				return binary<A>::getBit(byteIdx, bitIdx);
			}

			template <typename... B>
			inline bool getBit(B... b) const noexcept = delete;

			inline unsigned long long getULLong(void) const noexcept {
				return this->bits.to_ullong();
			}

			inline std::string getString(void) const noexcept {
				return this->bits.to_string();
			}

			friend inline ostream &operator<<(ostream &os, conref<binary<A>> a) noexcept {
				return a.print(os, a);
			}

			friend inline ostream &operator<<(ostream &os, binary<A> &&a) noexcept {
				return operator<<(os, a);
			}

			constexpr static inline size_t getSize(void) noexcept {
				return sz;
			}

		private:
			bitA bits;
		};
	}
}
