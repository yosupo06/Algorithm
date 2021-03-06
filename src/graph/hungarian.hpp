/**
割当問題を解き，以下の条件を満たすle, ri, permを得る
- le[i] <= 0, ri[j] >= 0
- cost[i][j] + le[i] + ri[j] >= 0
- cost[i][perm[i]] + le[i] + ri[perm[i]] = 0
*/
template<class D>
struct Hungarian {
    V<D> le, ri;
    V<int> perm;

    Hungarian(const VV<D>& c) {
        int n = int(c.size()), m = int(c[0].size());
        assert(n <= m);
        le = V<D>(n, D(0)); ri = V<D>(m, D(0));
        perm = V<int>(n);
        V<int> to_r(n, -1), to_l(m, -1);

        for (int s = 0; s < n; s++) {
            V<char> l_u(n), r_u(m);
            l_u[s] = true;
            V<int> tr(m, -1), min_l(m, s);
            V<D> min_cost(m);
            for (int j = 0; j < m; j++) min_cost[j] = c[s][j] + le[s] + ri[j];
            while (true) {
                int r = -1;
                D d = numeric_limits<D>::max();
                for (int j = 0; j < m; j++) {
                    if (!r_u[j] && min_cost[j] < d) {
                        r = j;
                        d = min_cost[j];
                    }
                }
                for (int i = 0; i < n; i++) if (l_u[i]) le[i] -= d;
                for (int j = 0; j < m; j++) {
                    if (r_u[j]) ri[j] += d;
                    else min_cost[j] -= d;
                }
                tr[r] = min_l[r];
                int l = to_l[r];
                if (l == -1) {
                    while (r != -1) {
                        int nl = tr[r], nr = to_r[nl];
                        to_l[r] = nl; to_r[nl] = r;
                        r = nr;
                    }
                    break;
                }
                l_u[l] = r_u[r] = true;
                for (int j = 0; j < m; j++) {
                    D cost = c[l][j] + le[l] + ri[j];
                    if (cost < min_cost[j]) {
                        min_l[j] = l;
                        min_cost[j] = cost;
                    }
                }
            }
        }
        perm = to_r;
    }
};
