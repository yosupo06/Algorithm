// Gabow Edmond's blossom algorithm
// Reference: https://qiita.com/Kutimoti_T/items/5b579773e0a24d650bdf
template <class E> struct MaxMatching {
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
        nx[st] = P(-1, -1);
        queue<int> q;
        V<int> vis;
        q.push(st);
        vis.push_back(st);
        while (q.size()) {
            int a = q.front();
            q.pop();
            for (auto e : g[a]) {
                int b = e.to;
                if (ty[b] == 1) continue;  // odd point
                if (ty[b] == 0) {
                    if (mt[b] == -1) {
                        // increase matching
                        mt[b] = a;
                        match(a, b);
                        for (int d : vis) ty[d] = 0;
                        return true;
                    }
                    // connect
                    vis.push_back(b);
                    vis.push_back(mt[b]);
                    ty[b] = 1;
                    ty[mt[b]] = -1;
                    nx[b] = P(-1, -1);
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
                while (x != -1 || y != -1) {
                    if (y != -1) swap(x, y);
                    x = group(nx[mt[x]].first);
                    if (x == -1) continue;
                    if (nx[x] == P(a, b)) {
                        z = x;
                        break;
                    }
                    nx[x] = P(a, b);
                }
                for (int v : {group(a), group(b)}) {
                    while (v != z) {
                        q.push(v);
                        ty[v] = -1;
                        gr_buf[v] = z;
                        v = group(nx[mt[v]].first);
                    }
                }
            }
        }
        return false;
    }
    MaxMatching(const VV<E>& _g)
        : n(int(_g.size())), g(_g), mt(n, -1), ty(n, 0), gr_buf(n), nx(n) {
        for (int st = 0; st < n; st++)
            if (mt[st] == -1) arg(st);
    }
};
