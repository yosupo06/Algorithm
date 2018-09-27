#include "gtest/gtest.h"
#include "base.h"
#include "random.h"
#include "string/suffixarray.h"

V<int> naive_sa(string s) {
    V<int> idx(s.size()+1);
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

TEST(SAYosupoTest, SAISRANDOM) {
    for (int i = 0; i < 100; i++) {
        string s = rand_lower_string(rand_int(1, 100));
        auto sa = sa_is(s);
        assert(naive_sa(s) == sa);
        assert(lcp(s, sa) == SA<string>(s, sa).lcp);
    }
}

TEST(SAYosupoTest, DoublingSARandom) {
    for (int i = 0; i < 100; i++) {
        string s = rand_lower_string(rand_int(1, 100));
        auto sa = doublingSA(s);
        assert(naive_sa(s) == sa);
        assert(lcp(s, sa) == SA<string>(s, sa).lcp);
    }
}
