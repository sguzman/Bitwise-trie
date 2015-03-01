#include <gtest/gtest.h>

#include <bitset>

#include "binary.hxx"

template <typename A>
using conref = const A&;

namespace
{
    //Pretty ugly otherwise
    template <size_t t>
    using constBitSize = conref<std::bitset<t>>;

    // Typedef's for some primitive types
    using IntBitset = std::bitset<sizeof(int) << 3>;
    using uIntBitset = std::bitset<sizeof(unsigned int) << 3>;


    template<size_t size>
    testing::AssertionResult BitSetMatch(constBitSize<size> expected, constBitSize<size> actual) {
        for (size_t i{}; i < size; ++i) {
            if (expected[i] != actual[i]) {
                return testing::AssertionFailure() << "actual[" << i
                        << "] (" << actual[i] << ") != expected[" << i
                        << "] (" << expected[i] << ")";
            }
        }

        return testing::AssertionSuccess();
    }

    class BinaryTest : public testing::Test
    {
    public:

    protected:
        BinaryTest(void) {}
        virtual ~BinaryTest(void) {}
        virtual void SetUp(void) {}
        virtual void TearDown(void) {}
    };

    TEST(BinaryTest, BinInt1)
    {
        IntBitset iBitA{"01010101"};
        IntBitset iBitB{"01010101"};

        EXPECT_TRUE(BitSetMatch(iBitA, iBitB));
    };
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
