//1<<17:131072 1<<12:4096
const int SEG_SIZE = 1<<12;
int seg[SEG_SIZE];

void seg_init() {
    for (int i = 0; i < SEG_SIZE; i++) {
        seg[i] = 0;
    }
}

template <class T>
void seg_set(T *seg, int i, T x) {
    i += SEG_SIZE/2 - 1;
    seg[i] = x;
    while (i) {
        i = (i - 1) / 2;
        T s1 = seg[i*2+1], s2 = seg[i*2+2];
        seg[i] = max(s1, s2);
    }
}

template <class T>
T seg_get(T *seg, int a, int b, int k = 0, int l = 0, int r = SEG_SIZE/2) {
    if (a <= l && r <= b) return seg[k];
    if (r <= a || b <= l) return -1;
    T vl = seg_get(seg, a, b, k*2+1, l, (l+r)/2);
    T vr = seg_get(seg, a, b, k*2+2, (l+r)/2, r);
    return max(vl, vr);
}

template <int N>
struct SegTree {
    static const int size = 1<<N;
    typedef pair<ll, ll> P;
    P seg[size*2];
    
    void init() {
        for (int i = 0; i < size; i++) {
            seg[i] = P(0, 0);
        }
    }

    void set(int i, ll x) {
        i += size-1;
        seg[i] = P(x, x);
        while (i) {
            i = (i-1) / 2;
            seg[i].first = seg[i*2+1].first + seg[i*2+2].first;
            seg[i].second = max(seg[i*2+1].second, seg[i*2+2].second);
        }
    }

    void mod(ll x, int a, int b, int k = 0, int l = 0, int r = size) {
        if (seg[k].second < x) return;
        if (r <= a || b <= l) return;
        if (a <= l && r <= b && r-l == 1) {
            seg[k].first %= x;
            seg[k].second %= x;
            return;
        }

        mod(x, a, b, k*2+1, l, (l+r)/2);
        mod(x, a, b, k*2+2, (l+r)/2, r);

        seg[k].first = seg[k*2+1].first + seg[k*2+2].first;
        seg[k].second = max(seg[k*2+1].second, seg[k*2+2].second);
    }

    ll get(uint a, uint b, uint k = 0, uint l = 0, uint r = size) {
        if (r <= a || b <= l) return 0;
        if (a <= l && r <= b) {
            return seg[k].first;
        }
        ll r1 = get(a, b, k*2+1, l, (l+r)/2);
        ll r2 = get(a, b, k*2+2, (l+r)/2, r);
        return r1+r2;
    }
};