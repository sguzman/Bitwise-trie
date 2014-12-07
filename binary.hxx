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

	explicit binary(conref<A> a);

	explicit binary(A&& a);

	template <typename... B>
	explicit binary(B... b) = delete;

	~binary(void);
private:

	bitA bits;
};