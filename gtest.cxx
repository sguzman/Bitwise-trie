#include <gtest/gtest.h>

#include <bitset>

#include "binary.hxx"

template <typename A>
using conref = const A&;

namespace
{
    using namespace binaryNS;

    //Pretty ugly otherwise
    template <typename A>
    using constBinary = conref<binary<A>>;

    template <typename A>
    using bitCon = std::bitset<sizeof(A) << 3>;

    template <typename A>
    using constBitset = conref<bitCon<A>>;

    template <typename A, size_t size = sizeof(A) << 3>
    testing::AssertionResult BitSetMatch(constBinary<A> expected, constBitset<A> actual) {
        for (size_t i{}; i < size; ++i) {
            if (expected[i] != actual[i]) {
                return testing::AssertionFailure()
                        << "actual[" << i << "] (" << actual[i]
                        << ") != expected[" << i << "] (" << expected[i] << ")";
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
        binary<int> actual{1};
        bitCon<int> expected{"1"};

        EXPECT_TRUE(BitSetMatch(actual, expected));
    };

    TEST(BinaryTest, BinInt2)
    {
        binary<int> actual{2};
        bitCon<int> expected{"10"};

        EXPECT_TRUE(BitSetMatch(actual, expected));
    };

    TEST(BinaryTest, BinInt3)
    {
        binary<int> actual{3};
        bitCon<int> expected{"11"};

        EXPECT_TRUE(BitSetMatch(actual, expected));
    };

    TEST(BinaryTest, BinInt4)
    {
        binary<int> actual{15};
        bitCon<int> expected{"1111"};

        EXPECT_TRUE(BitSetMatch(actual, expected));
    };

    TEST(BinaryTest, BinInt5)
    {
        binary<int> actual{66};
        bitCon<int> expected{"1000010"};

        EXPECT_TRUE(BitSetMatch(actual, expected));
    };

    TEST(BinaryTest, BinInt6)
    {
        binary<int> actual{65356};
        bitCon<int> expected{"1111111101001100"};

        EXPECT_TRUE(BitSetMatch(actual, expected));
    };

    TEST(BinaryTest, BinInt7)
    {
        binary<int> actual{45364535};
        bitCon<int> expected{"10101101000011010100110111"};

        EXPECT_TRUE(BitSetMatch(actual, expected));
    };
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
