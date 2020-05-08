// 普通にsortした方が早くない？困ったね
template <class Q> void sort_mo(V<Q>& ques) {
    auto dist = [&](Q x, Q y) { return abs(x.l - y.l) + abs(x.r - y.r); };
    int n = int(ques.size());
    if (n <= 1) return;

    // ordered by manhattan mst (tsp approx)
    {
        VV<int> tr(n);
        V<pair<int, int>> ps(n);
        for (int i = 0; i < n; i++) {
            ps[i] = {ques[i].l, ques[i].r};
        }
        auto edges = manhattan_mst(ps);
        for (auto e : edges) {
            tr[e.first].push_back(e.second);
            tr[e.second].push_back(e.first);
        }
        V<Q> nques;
        auto dfs = [&](auto self, int p, int b) -> void {
            nques.push_back(ques[p]);
            for (auto d : tr[p]) {
                if (d == b) continue;
                self(self, d, p);
            }
        };
        dfs(dfs, 0, -1);
        ques = nques;
    }
    // 2-opt
    for (int ph = 0; ph < 10; ph++) {
        for (int i = 1; i < n; i++) {
            for (int j = i + 1; j < min(i + 10, n - 1); j++) {
                ll pre =
                    dist(ques[i - 1], ques[i]) + dist(ques[j], ques[j + 1]);
                ll now =
                    dist(ques[i - 1], ques[j]) + dist(ques[i], ques[j + 1]);
                if (now < pre) {
                    reverse(ques.begin() + i, ques.begin() + j + 1);
                }
            }
        }
    }
    // reverse first
    {
        int mi = TEN(9), idx = -1;
        for (int i = 0; i < n - 1; i++) {
            int nw = abs(ques[i].l - ques[i].r) + dist(ques[0], ques[i + 1]);
            if (nw < mi) {
                mi = nw;
                idx = i;
            }
        }
        reverse(ques.begin(), ques.begin() + idx + 1);
    }
    // reverse last
    {
        int mi = TEN(9), idx = -1;
        for (int i = 1; i < n; i++) {
            int nw = dist(ques[i - 1], ques[n - 1]);
            if (nw < mi) {
                mi = nw;
                idx = i;
            }
        }
        reverse(ques.begin() + idx, ques.end());
    }
}
