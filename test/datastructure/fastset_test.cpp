#include "gtest/gtest.h"
#include "base.h"
#include "bitop.h"
#include "util/ostream.h"
#include "random.h"
#include "datastructure/fastset.h"


TEST(FastSetTest, SimpleTest) {
    Random gen;
    FastSet bs(300);
    set<ssize_t> st;
    st.insert(-1); st.insert(300);
    for (int ph = 0; ph < 10000; ph++) {
        int ty = gen.uniform(0, 3);
        ssize_t x;
        switch (ty) {
            case 0:
                //add
                x = gen.uniform(0, 299);
                bs.set(x); st.insert(x);
                break;
            case 1:
                //reset
                x = gen.uniform(0, 299);
                bs.reset(x); st.erase(x);
                break;
            case 2:
                //next
                x = gen.uniform(0, 299);
                ASSERT_EQ(bs.next(x), *st.lower_bound(x));
                break;
            case 3:
                x = gen.uniform(0, 299);
                ASSERT_EQ(bs.prev(x), *prev(st.lower_bound(x)));
                break;
        }
    }
}
