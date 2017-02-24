template<class Str>
struct SA {
    Str s;
    V<int> sa, rsa, lcp;
};

template<class Str>
V<int> doublingSA(Str s) {
    int n = (int)s.size();
    V<int> sa(n+1);
    V<int> rsa(n+1);
    iota(begin(sa), end(sa), 0);
    for (int i = 0; i <= n; i++) {
        rsa[i] = i < n ? s[i] : -1;
    }
    vector<int> tmp(n+1);
    for (int k = 1; k <= n; k *= 2) {
        auto cmp = [&](int x, int y){
            if (rsa[x] != rsa[y]) return rsa[x] < rsa[y];
            int rx = x+k <= n ? rsa[x+k] : -1;
            int ry = y+k <= n ? rsa[y+k] : -1;
            return rx < ry;
        };
        sort(begin(sa), end(sa), cmp);
        tmp[sa[0]] = 0;
        for (int i = 1; i <= n; i++) {
            tmp[sa[i]] = tmp[sa[i-1]] + (cmp(sa[i-1], sa[i]) ? 1 : 0);
        }
        copy(begin(tmp), end(tmp), begin(rsa));
    }
    return sa;
}

template<class Str>
struct SA {
    Str s;
    vector<int> sa, rsa, lcp;
    SA(Str s) : s(s) {
        int n = (int)s.size();
        sa.resize(n+1); rsa.resize(n+1); lcp.clear();
        iota(sa.begin(), sa.end(), 0);
        for (int i = 0; i <= n; i++) {
            rsa[i] = i < n ? s[i] : -1;
        }
        vector<int> tmp(n+1);
        for (int k = 1; k <= n; k *= 2) {
            auto cmp = [&](int x, int y){
                if (rsa[x] != rsa[y]) return rsa[x] < rsa[y];
                int rx = x+k <= n ? rsa[x+k] : -1;
                int ry = y+k <= n ? rsa[y+k] : -1;
                return rx < ry;
            };
            sort(sa.begin(), sa.end(), cmp);
            tmp[sa[0]] = 0;
            for (int i = 1; i <= n; i++) {
                tmp[sa[i]] = tmp[sa[i-1]] + (cmp(sa[i-1], sa[i]) ? 1 : 0);
            }
            copy_n(tmp.begin(), n+1, rsa.begin());
        }
    }
};
