// Gabow Edmond's blossom algorithm
// Reference: https://qiita.com/Kutimoti_T/items/5b579773e0a24d650bdf
template <class E> struct MaxMatching {
    int n;
    const VV<E>& g;
    V<int> mt;

    using P = pair<int, int>;
    V<int> is_ev, gr_buf;
    V<P> nx;
    int st;
    int group(int x) {
        if (gr_buf[x] == -1 || is_ev[gr_buf[x]] != st) return gr_buf[x];
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

    bool arg() {
        is_ev[st] = st;
        gr_buf[st] = -1;
        nx[st] = P(-1, -1);
        queue<int> q;
        q.push(st);
        while (q.size()) {
            int a = q.front();
            q.pop();
            for (auto e : g[a]) {
                int b = e.to;
                if (b == st) continue;
                if (mt[b] == -1) {
                    mt[b] = a;
                    match(a, b);
                    return true;
                }
                if (is_ev[b] == st) {
                    int x = group(a), y = group(b);
                    if (x == y) continue;
                    int z = -1;
                    while (x != -1 || y != -1) {
                        if (y != -1) swap(x, y);
                        if (nx[x] == P(a, b)) {
                            z = x;
                            break;
                        }
                        nx[x] = P(a, b);
                        x = group(nx[mt[x]].first);
                    }
                    for (int v : {group(a), group(b)}) {
                        while (v != z) {
                            q.push(v);
                            is_ev[v] = st;
                            gr_buf[v] = z;
                            v = group(nx[mt[v]].first);
                        }
                    }
                } else if (is_ev[mt[b]] != st) {
                    is_ev[mt[b]] = st;
                    nx[b] = P(-1, -1);
                    nx[mt[b]] = P(a, -1);
                    gr_buf[mt[b]] = b;
                    q.push(mt[b]);
                }
            }
        }
        return false;
    }
    MaxMatching(const VV<E>& _g)
        : n(int(_g.size())), g(_g), mt(n, -1), is_ev(n, -1), gr_buf(n), nx(n) {
        for (int i = 0; i < n; i++) {
            for (auto e: g[i]) {
                int j = e.to;
                if (mt[i] == -1 && mt[j] == -1) {
                    mt[i] = mt[j];
                    mt[j] = mt[i];
                }
            }
        }
        for (st = 0; st < n; st++)
            if (mt[st] == -1) arg();
    }
};
