#include "gtest/gtest.h"
#include "base.h"
#include "datastructure/fenwick.h"

TEST(FenwickYosupo, Usage) {
    Fenwick<int> fw(4);
    fw.add(1, 1);
    fw.add(3, 1);
    assert(fw.sum_lower_bound(2) == 4);
}
