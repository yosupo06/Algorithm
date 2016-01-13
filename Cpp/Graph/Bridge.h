/**
 * 橋の検出
 */

template <int V>
struct Bridge {
    vector<int> g[V];
    void add(int a, int b) {
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int imos[V]; //0ならば(i, root[i])は橋
    int root[V], dps[V];
    int gc, ig[V];

    stack<int> visit;
    int dfs(int i, int b, int dp) {
        root[i] = b;
        dps[i] = dp;
        visit.push(i);
        bool fp = false;
        for (int d: g[i]) {
            if (dps[d] != -1) {
                if (!fp && d == b) {
                    fp = true;
                    continue;
                }
                if (dps[i] > dps[d]) {
                    imos[i]++;
                    imos[d]--;
                }
            } else {
                imos[i] += dfs(d, i, dp+1);
            }
        }
        if (imos[i] == 0) {
            int j;
            do {
                j = visit.top(); visit.pop();
                ig[j] = gc;
            } while (j != i);
            gc++;
        }
        return imos[i];
    }
    
    void exec(int v = V) {
        fill_n(imos, v, 0);
        fill_n(root, v, -1);
        fill_n(dps, v, -1);
        fill_n(ig, v, -1);
        gc = 0;
        for (int i = 0; i < v; i++) {
            if (dps[i] != -1) continue;
            dfs(i, -1, 0);
        }
    }
};
