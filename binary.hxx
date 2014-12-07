#include <bitset>

template <typename A>
using conref = const A&;

template <typename A>
class binary final {
public:
	explicit binary(void) = null;

	explicit binary(conref<A> a);

	explicit binary(A&& a);

	template <typename... B>
	explicit binary(B... b) = delete;

	~binary(void);
private:
};