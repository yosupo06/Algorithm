//#undef LOCAL
#include <bits/stdc++.h>
#include <ostream>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
template<class T> using V = vector<T>;
template<class T> using VV = V<V<T>>;
constexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n-1); }
#define rep(i,N) for(int i=0;i<(int)(N);i++)
#define rep1(i,N) for(int i=1;i<=(int)(N);i++)
#define fs first
#define sc second
#define pb push_back
#define PB push_back
#define MP make_pair
#define FOR(i, a, b) for(int i=int(a);i<int(b);i++)
#define REP(i,b) FOR(i,0,b)
#define all(x) x.begin(),x.end()
#define ALL(x) x.begin(),x.end()
template<class T, class U> void chmin(T& t, const U& u) { if (t > u) t = u; }
template<class T, class U> void chmax(T& t, const U& u) { if (t < u) t = u; }

#ifdef LOCAL
#define show(x) cerr << __LINE__ << " : " << #x << " = " << (x) << endl
#else
#define show(x) true
#endif


struct UnionFind {
    V<int> p, r;
    int gn;
    UnionFind(int n = 0) : p(n, -1), r(n, 1), gn(n) {}
    void merge(int a, int b) {
        int x = group(a), y = group(b);
        if (x == y) return;  // same
        gn--;
        if (r[x] < r[y]) {
            p[x] = y;
        } else {
            p[y] = x;
            if (r[x] == r[y]) r[x]++;
        }
    }
    int group(int a) {
        if (p[a] == -1) return a;
        return p[a] = group(p[a]);
    }
    bool same(int a, int b) { return group(a) == group(b); }
};

// s[0..res[i]] == s[i..i+res[i]]
template <class S> V<int> z_algo(const S& s) {
    int n = int(s.size());
    V<int> R(n + 1);
    R[0] = 0;
    for (int i = 1, j = 0; i <= n; i++) {
        int& k = R[i];
        k = (j + R[j] <= i) ? 0 : min(j + R[j] - i, R[i - j]);
        while (i + k < n && s[k] == s[i + k]) k++;
        if (j + R[j] < i + R[i]) j = i;
    }
    R[0] = n;
    return R;
}


int n;
V<int> a;

V<int> rev(V<int> l) {
    reverse(l.begin(), l.end());
    return l;
}

V<int> sub_a(int l, int r) {
    return {a.begin() + l, a.begin() + r};
}
V<int> concat(V<int> l, const V<int>& r) {
    l.insert(l.end(), r.begin(), r.end());
    return l;
}

struct Run {
    int l, r;

    friend ostream &operator<<(ostream &os, const Run &q) {
        os << "l: " << q.l << " r: " << q.r;
        return os;
    }
};

V<Run> norm(V<Run> run) {
    sort(run.begin(), run.end(), [&](const Run& l, const Run& r) {
        if (l.l != r.l) return l.l < r.l;
        return l.r > r.r;
    });
    V<Run> res;
    for (auto r: run) {
        if (!res.empty() && res.back().r >= r.r) continue;
        res.push_back(r);
    }
    return res;
}

VV<Run> runs;
void run(int l, int r, int f) {
    if (l + 1 == r) return;
    int md = (l + r + f) / 2;
    run(l, md, f);
    run(md, r, f);
    auto z1 = z_algo(rev(sub_a(l, md)));
    auto z2 = z_algo(concat(sub_a(md, r), sub_a(l, r)));
    for (int i = md - 1; i >= l; i--) {
        int l1 = min(i - l, z1[md - i]);
        int l2 = min(r - md, z2[(r - l) - (md - i)]);
        int le = i - l1, ri = md + l2, peri = md - i;
        if (ri - le >= 2 * peri) runs[md - i].push_back({i - l1, md + l2});
    }
}



struct Q {
    int s, t, le;
};

const int LG = 19;
UnionFind uf[LG];

ll merge(int s, int t, int l) {
    if (uf[l].same(s, t)) return 0;
    uf[l].merge(s, t);
    if (l == 0) return 1;
    int le = 1 << (l - 1);
    return merge(s, t, l - 1) + merge(s + le, t + le, l - 1);
}


void solve() {
    cin >> n;
    a = V<int>(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    runs = VV<Run>(n / 2 + 1);

    reverse(a.begin(), a.end());
    run(0, n, 0);
    for (int i = 1; i <= n / 2; i++) {
        for (auto &q: runs[i]) {
            q.l = n - q.l;
            q.r = n - q.r;
            swap(q.l, q.r);
        }
    }
    reverse(a.begin(), a.end());
    run(0, n, 1);
    for (int i = 1; i <= n / 2; i++) {
        runs[i] = norm(runs[i]);
    }

    auto que = VV<Q>(n / 2 + 1);
    for (int period = 1; period <= n / 2; period++) {
        for (auto q: runs[period]) {
            int di = q.r - q.l;
            for (int pe = period; pe <= di / 2; pe += period) {
                que[pe].push_back({q.l, q.l + pe, di - pe});
            }
        }
    }
    V<ll> cost(n / 2 + 1);
    for (int i = 1; i <= n / 2; i++) cin >> cost[i];
    V<int> idx(n / 2);
    iota(idx.begin(), idx.end(), 1);
    sort(idx.begin(), idx.end(), [&](int x, int y) {
        return cost[x] < cost[y];
    });

    for (int i = 0; i < LG; i++) {
        uf[i] = UnionFind(n);
    }
    ll sm = 0;
    for (auto i: idx) {
        ll cnt = 0;
        for (auto q: que[i]) {
            for (int l = LG - 1; l >= 0; l--) {
                if (q.le & (1<<l)) {
                    cnt += merge(q.s, q.t, l);
                    q.s += (1<<l);
                    q.t += (1<<l);
                    q.le -= (1<<l);
                }
            }
        }
        sm += cost[i] * cnt;
    }
    cout << sm << endl;
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(20);
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        solve();
    }
}
