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

	explicit binary(conref<A> a) {
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

	explicit binary(A&& a) : binary(a) {}

	template <typename... B>
	explicit binary(B... b) = delete;

	~binary(void) {
		bits.~bitA();
	}

private:
	static inline void print(std::ostream& os, binary<A> a) {
		for (size_t i = 0; i < sz; ++i) {
			for (size_t j = 0; predAndPrint(os, j); ++j) {
				static bit bitIdx;
				bitIdx = (bit) a.bits[getBitIdx(i, j)];
				os << bitIdx;
			}
		}
	}

	static inline bit getBitFromByte(byte data, byte bitIdx) {
		return data & (1 << bitIdx);
	}

	static inline size_t getBitIdx(size_t byteIdx, size_t bitIdx) {
		return (byteIdx << 3) + bitIdx;
	}

	static inline bit predAndPrint(std::ostream& os, conref<size_t> idx) {
		const bool pred{idx < 8};

		if (!pred) {
			os << ' ';
		}

		return pred;
	} ;

	bitA bits;
};