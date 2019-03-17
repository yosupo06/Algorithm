struct RunExec {
    VV<pair<int, int>> runs;

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

    template <class Str>
    RunExec(Str _a) : a(_a) {
        n = int(a.size());
        runs.resize(n / 2 + 1);
        reverse(a.begin(), a.end());
        run(0, n, 0);
        for (auto& run: runs) {
            for (auto& p: run) {
                tie(p.first, p.second) =
                        make_pair(n - p.second, n - p.first);
            }
        }
        reverse(a.begin(), a.end());
        run(0, n, 1);

        for (auto& run: runs) {
            sort(run.begin(), run.end());
            V<pair<int, int>> res;
            for (auto p: run) {
                if (!res.empty() && p.second <= res.back().second) continue;
                res.push_back(p);
            }
            run = res;
        }
    }
};
