#include "gtest/gtest.h"
#include "base.h"
#include "bitop.h"
#include "util/ostream.h"
#include "random.h"
#include "string/manacher.h"


TEST(ManacharTest, StressTest) {
    Random gen;

    auto naive = [&](V<int> v) {
        int n = int(v.size());
        V<int> res(n);
        for (int i = 0; i < n; i++) {
            while (i - res[i] >= 0 && i + res[i] < n && v[i - res[i]] == v[i + res[i]]) res[i]++;
        }
        return res;
    };

    for (int le = 0; le < 50; le++) {
        for (int ph = 0; ph < 200; ph++) {
            V<int> v(le);
            for (int i = 0; i < le; i++) v[i] = gen.uniform_bool();
            auto sol = naive(v);
            auto ans = manacher(v);
            ASSERT_EQ(sol, ans);
        }
    }
}

TEST(ManacharEvenTest, StressTest) {
    Random gen;

    auto naive = [&](V<int> v) {
        int n = int(v.size());
        V<int> res(n + 1);
        for (int i = 0; i <= n; i++) {
            while (i - 1 - res[i] >= 0 && i + res[i] < n && v[i - 1 - res[i]] == v[i + res[i]]) res[i]++;
        }
        return res;
    };

    for (int le = 0; le < 50; le++) {
        for (int ph = 0; ph < 200; ph++) {
            V<int> v(le);
            for (int i = 0; i < le; i++) v[i] = gen.uniform_bool();
            auto sol = naive(v);
            auto ans = manacher_even(v);
            ASSERT_EQ(sol, ans);
        }
    }
}
