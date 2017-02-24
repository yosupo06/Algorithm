#include "gtest/gtest.h"
#include "base.h"
#include "random.h"
#include "string/sais.h"

V<int> naive_sa(string s) {
    int n = int(s.size());
    V<int> idx(n+1);
    iota(begin(idx), end(idx), 0);
    sort(begin(idx), end(idx), [&](int l, int r){
        return s.substr(l) < s.substr(r);
    });
    return idx;
}

V<int> lcp(string s, V<int> sa) {
    int n = int(s.size());
    V<int> lcp(n);
    for (int i = 0; i < n; i++) {
        string x = s.substr(sa[i]);
        string y = s.substr(sa[i+1]);
        int c = 0;
        while (x[c] == y[c]) c++;
        lcp[i] = c;
    }
    return lcp;
}
TEST(SATest, SATest) {
    string s = "abracadabra";
    EXPECT_EQ(naive_sa(s), sa_is(s));
}

TEST(SATest, ManyRandom) {
    for (int i = 0; i < 1000; i++) {
        string s = rand_lower_string(rand_int(1, 100));
        EXPECT_EQ(naive_sa(s), sa_is(s));
        auto sa = sa_is(s);
        EXPECT_EQ(lcp(s, sa), suffixArray(s).lcp);
    }
}
