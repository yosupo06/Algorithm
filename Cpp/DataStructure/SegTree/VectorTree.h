//size:2**N N=17:131072 N=12:4096
template <class T, int N>
struct VectorTree {
    static constexpr int size = 1<<N;
    vector<T> seg[size*2];
    void init(T *x, int n) {
        int l = 0, r = 1, s = size;
        for (int i = 0; i <= N; i++) {
            for (int j = l; j < r; j++) {
                seg[j].clear();
                seg[j].resize(s);
            }
            l = l*2+1; r = r*2+1; s /= 2;
        }
        for (int i = 0; i < size; i++) {
            if (i < n) {
                seg[i+size-1][0] = x[i];
            } else {
                seg[i+size-1][0] = -1;
            }
        }
        for (int i = size-2; i >= 0; i--) {
            int k1 = i*2+1, k2 = i*2+2;
            merge(seg[k1].begin(), seg[k1].end(), seg[k2].begin(), seg[k2].end(), seg[i].begin());
        }
    }

    inline T comp(T r1, T r2, T x) {
        if (r1 == -1) return r2;
        if (r2 == -1) return r1;
        T n1 = abs(r1-x), n2 = abs(r2-x);
        if (n1 == n2) {
            return min(r1, r2);
        } else if (n1 < n2) {
            return r1;
        } else {
            return r2;
        }
    }

    inline T get(uint a, uint b, T x, uint k = 0, uint l = 0, uint r = size) {
        if (a <= l && r <= b) {
            auto it1 = lower_bound(seg[k].begin(), seg[k].end(), x);
            auto it2 = lower_bound(seg[k].rbegin(), seg[k].rend(), x, greater<int>());
            T r1 = (it1 != seg[k].end()) ? *it1 : -1;
            T r2 = (it2 != seg[k].rend()) ? *it2 : -1;
            return comp(r1, r2, x);
        }
        if (r <= a || b <= l) return -1;
        T vl = get(a, b, x, k*2+1, l, (l+r)/2);
        T vr = get(a, b, x, k*2+2, (l+r)/2, r);
        return comp(vl, vr, x);
    }
};
