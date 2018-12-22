#include "gtest/gtest.h"
#include "base.h"
#include "bitop.h"
#include "util/ostream.h"
#include "random.h"
#include "datastructure/bitvector.h"


TEST(BitVectorTest, RightShift) {
    Random gen;
    BitVec bs(64);
    bs.d[0] = 0x1234123412341234ULL;
    bs >>= 4;
    ASSERT_EQ(bs.d[0], 0x0123412341234123ULL);

    for (int le = 0; le < 200; le++) {
        for (int ph = 0; ph < 30; ph++) {
            int shift = gen.uniform(0, le + 3);
            bs = BitVec(le);
            for (int i = 0; i < le; i++) bs.set(i, gen.uniform_bool());
            auto bs2 = bs >> shift;
            for (int i = 0; i < le; i++) {
                ASSERT_EQ(bs2[i], ((i + shift < le) ? bs[i + shift] : false));
            }
        }
    }
}

TEST(BitVectorTest, LeftShift) {
    Random gen;
    BitVec bs(64);
    bs.d[0] = 0x1234123412341234ULL;
    bs <<= 4;
    ASSERT_EQ(bs.d[0], 0x2341234123412340ULL);

    for (int le = 0; le < 200; le++) {
        for (int ph = 0; ph < 30; ph++) {
            int shift = gen.uniform(0, le + 3);
            bs = BitVec(le);
            for (int i = 0; i < le; i++) bs.set(i, gen.uniform_bool());
            auto bs2 = bs << shift;
            for (int i = 0; i < le; i++) {
                ASSERT_EQ(bs2[i], ((i - shift >= 0) ? bs[i - shift] : false));
            }
        }
    }
}
