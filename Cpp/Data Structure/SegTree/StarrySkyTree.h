template <int N>
struct StarrySkyTree {
    using P = pair<ll, ll>;
    static const int S = 1<<N;
    static const ll INF = 1LL<<55; //Warning: overflow!!(range negative add)
    P seg[2*S];

    void init() {
        fill_n(seg, 2*S, P(-INF, 0));
    }

    void set(int i, ll x) {
        i += S;
        seg[i].first = x;
        while (i) {
            i /= 2;
            seg[i].first = seg[i].second +
            max(seg[i*2].first, seg[i*2+1].first);
        } 
    }

    void add(int a, int b, ll x, int k = 1, int l = 0, int r = S) {
        if (r <= a || b <= l) return;
        if (a <= l && r <= b) {
            seg[k].first += x;
            seg[k].second += x;
        }
        int md = (l+r)/2;
        add(a, b, x, k*2, l, md);
        add(a, b, x, k*2+1, md, r);
        seg[k].first = seg[k].second +
        max(seg[k*2].first, seg[k*2+1].second);
    }

    ll get(int a, int b, int k = 1, int l = 0, int r = S) {
        if (r <= a || b <= l) return -INF;
        if (a <= l && r <= b) return seg[k].first;
        int md = (l+r)/2;
        ll dl = get(a, b, k*2, l, md);
        ll dr = get(a, b, k*2+1, md, r);
        return seg[k].second + max(dl, dr);
    }
};