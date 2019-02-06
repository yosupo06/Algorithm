// !! Broken !!

#include <bits/stdc++.h>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
constexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n - 1); }
template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;

//TODO: gabow
template<class E>
struct MaxMatching {
    int n;
    const VV<E>& g;
    V<int> mt;

    using P = pair<int, int>;
    V<int> ty, gr_buf;
    V<P> nx;

    int group(int x) {
        if (gr_buf[x] == -1 || ty[gr_buf[x]] == 1) return gr_buf[x];
        return gr_buf[x] = group(gr_buf[x]);
    }

    void match(int p, int b) {
        int d = mt[p];
        mt[p] = b;
        if (d == -1 || mt[d] != p) return;
        if (nx[p].second == -1) {
            mt[d] = nx[p].first;
            match(nx[p].first, d);
        } else {
            match(nx[p].first, nx[p].second);
            match(nx[p].second, nx[p].first);
        }
    }

    bool arg(int st) {
        ty[st] = gr_buf[st] = -1;
        queue<int> q;
        V<int> vis;
        q.push(st); vis.push_back(st);
        while (q.size()) {
            int a = q.front(); q.pop();
            for (auto e: g[a]) {
                int b = e.to;
                if (ty[b] == 1) continue; // odd point
                if (ty[b] == 0) {
                    if (mt[b] == -1) {
                        //increase matching
                        mt[b] = a; match(a, b);
                        for (int d: vis) ty[d] = 0;
                        return true;
                    }
                    // connect
                    vis.push_back(b); vis.push_back(mt[b]);
                    ty[b] = 1;
                    ty[mt[b]] = -1;
                    nx[mt[b]] = P(a, -1);
                    gr_buf[mt[b]] = b;
                    q.push(mt[b]);
                    continue;
                }
                int x = group(a), y = group(b);
                if (x == y) continue;
                if (x != -1) nx[x] = P(a, b);
                if (y != -1) nx[y] = P(a, b);
                int z = -1;
                while (true) {
                    if (y != -1) swap(x, y);
                    x = group(nx[mt[x]].first);
                    if (x == -1 || nx[x] == P(a, b)) {
                        z = x;
                        break;
                    }
                    nx[x] = P(a, b);
                }
                for (int v : {gr_buf[a], gr_buf[b]}) {
                    while (v != -1 && v != z) {
                        q.push(v);
                        ty[v] = -1;
                        nx[v] = P(a, b);
                        gr_buf[v] = z;
                        v = gr_buf[nx[mt[v]].first];
                    }
                }
            }
        }
        return false;
    }
    MaxMatching(const VV<E>& _g) : n(int(_g.size())), g(_g), mt(n, -1), ty(n, 0), gr_buf(n), nx(n) {
        int ans = 0;
        for (int st = 0; st < n; st++) {
            if (mt[st] == -1 && arg(st)) {
//                fill(ty.begin(), ty.end(), 0);
                ans++;
            }
        }
    }
};
using P = pair<int, int>; //r, c
struct E { int to; };

void solve(V<string> mp) {
    int h = int(mp.size()), w = int(mp[0].size());
    int n = 0;
    VV<E> g;
    auto inc_n = [&]() {
        g.push_back({});
        return n++;
    };
    auto add_e = [&](int a, int b) {
        if (a == -1 || b == -1) return;
        assert(a < n && b < n);
        g[a].push_back({b});
        g[b].push_back({a});
    };
    map<P, int> to_id;
    map<int, P> to_p;
    auto get_id = [&](int r, int c) {
        if (to_id.count(P(r, c))) return to_id[P(r, c)];
        return -1;
    };
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            if (mp[r][c] != '.') continue;
            int id = inc_n();
            to_id[P(r, c)] = id;
            to_p[id] = P(r, c);
        }
    }
    VV<int> id1s(h, V<int>(w)), id2s(h, V<int>(w));

    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            if (mp[r][c] == '.') continue;
            int id1 = inc_n(), id2 = inc_n();
            add_e(id1, id2);
            id1s[r][c] = id1;
            id2s[r][c] = id2;
            if (mp[r][c] == '+') {
                add_e(id1, get_id(r, c - 1));
                add_e(id1, get_id(r - 1, c));
                add_e(id1, get_id(r, c + 1));
                add_e(id1, get_id(r + 1, c));

                add_e(id2, get_id(r, c - 1));
                add_e(id2, get_id(r - 1, c));
                add_e(id2, get_id(r, c + 1));
                add_e(id2, get_id(r + 1, c));
            } else {
                add_e(id1, get_id(r, c - 1));
                add_e(id1, get_id(r, c + 1));

                add_e(id2, get_id(r - 1, c));
                add_e(id2, get_id(r + 1, c));
            }
        }
    }

    MaxMatching<E> mts(g);

    auto mt = mts.mt;

    V<string> ans = mp;
    auto bc = [&](int r, int c) {
        return 0 <= r && r < h && 0 <= c && c < w;
    };
    auto mark = [&](int r, int c, P p1, P p2) {
        set<char> s;
        for (char u = 'a'; u <= 'z'; u++) s.insert(u);
        for (int dr = -2; dr <= 2; dr++) {
            for (int dc = -2; dc <= 2; dc++) {
                if (bc(r + dr, c + dc)) s.erase(ans[r + dr][c + dc]);
            }
        }
        auto u = *s.begin();
        ans[r][c] = u;
        ans[p1.first][p1.second] = u;
        ans[p2.first][p2.second] = u;
    };
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            if (mp[r][c] == '.') continue;
            int id1 = id1s[r][c], id2 = id2s[r][c];
            if (mt[id1] == id2 || mt[id1] == -1 || mt[id2] == -1) continue;
            mark(r, c, to_p[mt[id1]], to_p[mt[id2]]);
        }
    }
    cout << "END" << endl;
    //for (auto s: ans) cout << s << endl;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false); //warning!
    cout << setprecision(20) << fixed;

    for (int ph = 0; ph < TEN(6); ph++) {
        int h, w;
        h = rand() % 10 + 1;
        w = rand() % 10 + 1;
        //cin >> h >> w;
        V<string> mp(h);
        //for (int r = 0; r < h; r++) cin >> mp[r];
        for (int r = 0; r < h; r++) {
            for (int c = 0; c < w; c++) {
                int ty = rand() % 3;
                if (ty == 0) mp[r] += '+';
                else if (ty == 1) mp[r] += '.';
                else mp[r] += '*';
            }
        }
        cout << h << " " << w << endl;
        for (string s: mp) cout << s << endl;
        solve(mp);
    }

    int h, w;
    cin >> h >> w;
    V<string> mp(h);
    for (int r = 0; r < h; r++) cin >> mp[r];
    solve(mp);
    return 0;
}