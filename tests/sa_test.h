#include "gtest/gtest.h"
#include "base.h"
#include "random.h"
#include "string/suffixarray.h"

TEST(SATest, SAExample) {
    string s = "abraca";
    auto sa = sa_is(s);
    EXPECT_EQ(sa.size(), 7);
    EXPECT_EQ(s.substr(sa[0]), "");
    EXPECT_EQ(s.substr(sa[1]), "a");
    EXPECT_EQ(s.substr(sa[2]), "abraca");
    EXPECT_EQ(s.substr(sa[3]), "aca");
    EXPECT_EQ(s.substr(sa[4]), "braca");
    EXPECT_EQ(s.substr(sa[5]), "ca");
    EXPECT_EQ(s.substr(sa[6]), "raca");
    auto lcp = SA<string>(s, sa).lcp;
    EXPECT_EQ(lcp.size(), 6);
    EXPECT_EQ(lcp[0], 0); // "", "a"
    EXPECT_EQ(lcp[1], 1); // "a", "abraca"
    EXPECT_EQ(lcp[2], 1); // "abraca", "aca"
    EXPECT_EQ(lcp[3], 0); // "aca", "braca"
    EXPECT_EQ(lcp[4], 0); // "braca", "ca"
    EXPECT_EQ(lcp[5], 0); // "ca", "raca"
}

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

TEST(SAISTest, ManyRandom) {
    for (int i = 0; i < 1000; i++) {
        string s = rand_lower_string(rand_int(1, 100));
        auto sa = sa_is(s);
        EXPECT_EQ(naive_sa(s), sa);
        EXPECT_EQ(lcp(s, sa), SA<string>(s, sa).lcp);
    }
}

TEST(DoublingSATest, ManyRandom) {
    for (int i = 0; i < 1000; i++) {
        string s = rand_lower_string(rand_int(1, 100));
        auto sa = doublingSA(s);
        EXPECT_EQ(naive_sa(s), sa);
        EXPECT_EQ(lcp(s, sa), SA<string>(s, sa).lcp);
    }
}
