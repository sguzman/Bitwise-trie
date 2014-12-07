#pragma once

#include <bitset>
#include <cstring>

template <typename A>
class binary final {
	template <typename B>
	using conref = const B&;

	constexpr static size_t sz{sizeof(A)};
	constexpr static size_t szB{sz << 3};

	using bitA = std::bitset<szB>;
	using byte = unsigned char;
	using bit = bool;

public:
	explicit binary(void) = delete;

	explicit binary(conref<A> a) noexcept {
		byte* ptr = new byte[sz];
		memcpy((void *) ptr, (const void* const) &a, sz);

		for (size_t i = 0; i < sz; ++i) {
			static byte ch;
			ch = ptr[i];
			for (size_t j = 0; j < 8; ++j) {
				static bool bitVal;
				bitVal = binary::getBitFromByte(ch, j);
				this->bits[getBitIdx(j, i)] = bitVal;
			}
		}

		delete [] ptr;
	}

	explicit binary(A&& a) noexcept : binary(a) {}

	template <typename... B>
	explicit binary(B... b) = delete;

	inline ~binary(void) noexcept{
		bits.~bitA();
	}

private:
	static inline void print(std::ostream& os, conref<binary<A>> a) noexcept {
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

	static inline bit getBitFromByte(byte data, byte bitIdx) noexcept {
		return data & (1 << bitIdx);
	}

	static inline size_t getBitIdx(size_t byteIdx, size_t bitIdx) noexcept {
		return (byteIdx << 3) + bitIdx;
	}

	bitA bits;
};