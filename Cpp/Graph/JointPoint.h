/**
 * 関節点の検出
 */

template <int V>
struct JointPoint {
    vector<int> g[V];
    void add(int a, int b) {
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int br_imos[V]; //0ならば(i, root[i])は橋
    int jp_imos[V];
    bool used[V];
    int root[V], dps[V];
    void dfs(int i, int b, int dp) {
        root[i] = b;
        dps[i] = dp;
        used[i] = true;
        for (int d: g[i]) {
            if (used[d]) {
                if (dps[i] < dps[d]) {
                    imos[i]--;
                    imos[d]++;
                }
            } else {
                dfs(d, i, dp+1);
            }
        }
    }

    int dfs2(int i) {
        used[i] = true;
        for (int d: g[i]) {
            if (used[d]) continue;
            dfs2(d);
            br_imos[i] += br_imos[d];
            jp_imos[i] += jp_imps[d];
            br_imos[i] += dfs2(d);
        }
        return imos[i];
    }

    void exec(int v = V) {
        fill_n(imos, v, 0);
        fill_n(root, v, -1);
        fill_n(dps, v, 0);
        fill_n(used, v, false);
        for (int i = 0; i < v; i++) {
            if (used[i]) continue;
            dfs(i, -1, 0);
        }
        fill_n(used, v, false);
        for (int i = 0; i < v; i++) {
            if (root[i] != -1) continue;
            dfs2(i);
        }
    }
};
