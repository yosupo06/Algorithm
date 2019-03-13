#include "gtest/gtest.h"
#include "base.h"
#include "bitop.h"
#include "util/ostream.h"
#include "random.h"
#include "string/zalgo.h"


TEST(ZTest, StressTest) {
    Random gen;

    auto naive = [&](V<int> v) {
        int n = int(v.size());
        V<int> res(n + 1);
        for (int i = 0; i <= n; i++) {
            while (i + res[i] < n && v[res[i]] == v[i + res[i]]) res[i]++;
        }
        return res;
    };

    for (int le = 0; le < 200; le++) {
        V<int> v(le);
        for (int i = 0; i < le; i++) v[i] = gen.uniform_bool();
        auto sol = naive(v);
        auto ans = z_algo(v);
        ASSERT_EQ(sol, ans);
    }
}
