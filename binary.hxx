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

public:
	explicit binary(void) = delete;

	explicit binary(conref<A> a) nowthrow {
		byte* ptr = new byte[sz];
		memcpy((void *) ptr, (const void* const) &a, sz);

		for (size_t i = 0; i < sz; ++i) {
			static byte ch;
			ch = ptr[i];
			for (size_t j = 0; j < 8; ++j) {
				static bool bit;
				bit = binary::getBitFromByte(ch, j);
				this->bitA[(i << 3) + j] = bit;
			}
		}
	}

	explicit binary(A&& a);

	template <typename... B>
	explicit binary(B... b) = delete;

	~binary(void);
private:
	static inline bool getBitFromByte(byte data, byte bit) nothrow {
		return data & (1 << bit);
	}

	bitA bits;
};