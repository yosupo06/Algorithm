// wavelet matrix
struct Wavelet {
    // space: 32N bits
    struct BitVector {
        V<int> _rank = {0};
        BitVector(V<char> v = V<char>()) {
            _rank.reserve(v.size() + 1);
            for (int d : v) _rank.push_back(_rank.back() + d);
        }
        int rank(bool f, int k) { return f ? _rank[k] : (k - _rank[k]); }
        int rank(bool f, int l, int r) { return rank(f, r) - rank(f, l); }
    };
    // space: 1.5N bits
    /*struct BitVector {
        V<ull> v;
        V<int> _rank;
        BitVector(V<char> _v = V<char>()) {
            int n = int(_v.size());
            v = V<ull>((n + 63) / 64);
            _rank = V<int>(v.size() + 1);
            for (int i = 0; i < n; i++) {
                if (_v[i]) {
                    v[i / 64] |= 1ULL << (i % 64);
                    _rank[i / 64 + 1]++;
                }
            }
            for (int i = 0; i < int(v.size()); i++) {
                _rank[i+1] += _rank[i];
            }
        }
        int rank(int k) {
            int a = _rank[k / 64];
            if (k % 64) a += __builtin_popcountll(v[k / 64] << (64 - k % 64));
            return a;
        }
        int rank(bool f, int k) { return f ? rank(k) : k - rank(k); }
        int rank(bool f, int l, int r) { return rank(f, r) - rank(f, l); }
    };*/

    int n, lg = 1;
    V<int> mid;
    V<BitVector> data;
    Wavelet(V<int> v = V<int>()) : n(int(v.size())) {
        int ma = 0;
        for (int x : v) ma = max(ma, x);
        while ((1 << lg) <= ma) lg++;
        mid = V<int>(lg);
        data = V<BitVector>(lg);
        for (int lv = lg - 1; lv >= 0; lv--) {
            V<char> buf;
            VV<int> nx(2);
            for (int d : v) {
                bool f = (d & (1 << lv)) > 0;
                buf.push_back(f);
                nx[f].push_back(d);
            }
            mid[lv] = int(nx[0].size());
            data[lv] = BitVector(buf);
            v.clear();
            v.insert(v.end(), nx[0].begin(), nx[0].end());
            v.insert(v.end(), nx[1].begin(), nx[1].end());
        }
    }
    pair<int, int> succ(bool f, int a, int b, int lv) {
        int na = data[lv].rank(f, a) + (f ? mid[lv] : 0);
        int nb = data[lv].rank(f, b) + (f ? mid[lv] : 0);
        return make_pair(na, nb);
    }
    // count i, s.t. (a <= i < b) && (v[i] < u)
    int rank(int a, int b, int u) {
        if ((1 << lg) <= u) return b - a;
        int ans = 0;
        for (int lv = lg - 1; lv >= 0; lv--) {
            bool f = (u & (1 << lv)) > 0;
            if (f) ans += data[lv].rank(false, a, b);
            tie(a, b) = succ(f, a, b, lv);
        }
        return ans;
    }
    // k-th(0-indexed!) number in v[a..b]
    int select(int a, int b, int k) {
        int u = 0;
        for (int lv = lg - 1; lv >= 0; lv--) {
            int le = data[lv].rank(false, a, b);
            bool f = (le <= k);
            if (f) {
                u += (1 << lv);
                k -= le;
            }
            tie(a, b) = succ(f, a, b, lv);
        }
        return u;
    }
};

struct CompressWavelet {
    Wavelet wt;
    V<int> v, vidx;
    int zip(int x) {
        return int(lower_bound(vidx.begin(), vidx.end(), x) - vidx.begin());
    }
    CompressWavelet(V<int> _v = V<int>()) : v(_v), vidx(v) {
        sort(vidx.begin(), vidx.end());
        vidx.erase(unique(vidx.begin(), vidx.end()), vidx.end());
        for (auto& d : v) d = zip(d);
        wt = Wavelet(v);
    }
    int rank(int a, int b, int u) { return wt.rank(a, b, zip(u)); }
    int select(int a, int b, int k) { return vidx[wt.select(a, b, k)]; }
};
