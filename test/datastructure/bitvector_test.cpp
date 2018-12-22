#include "gtest/gtest.h"
#include "base.h"
#include "bitop.h"
#include "util/ostream.h"
#include "util/random.h"
#include "datastructure/bitvector.h"


TEST(BitVectorTest, RightShift) {
    BitVec bs(64);
    bs.d[0] = 0x1234123412341234ULL;
    bs >>= 4;
    ASSERT_EQ(bs.d[0], 0x0123412341234123ULL);
}

TEST(BitVectorTest, LeftShift) {
    BitVec bs(64);
    bs.d[0] = 0x1234123412341234ULL;
    bs <<= 4;
    ASSERT_EQ(bs.d[0], 0x2341234123412340ULL);
}
