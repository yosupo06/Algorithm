/**
 * 後退解析
 */

template<int V>
struct Retrograde {
    vector<int> g[V], rg[V];
    /// 辺のクリア
    void init() {
        for (int i = 0; i < V; i++) {
            g[i].clear();
            rg[i].clear();
        }
    }

    void add(int from, int to) {
        g[from].push_back(to);
        rg[to].push_back(from);
    }

    int d[V]; /// -1:このマスからスタートすると先手が負ける 0:None 1:このマスからスタートすると先手が勝つ
    int count[V];
    void exec() {
        for (int i = 0; i < V; i++) {
            count[i] = (int)g[i].size();
        }

        for (int i = 0; i < V; i++) {
            if (d[i] == 1) {
                for (int x: rg[i]) {
                    count[x]--;
                }
            }
        }
        for (int i = 0; i < V; i++) {
            if (d[i] == -1) {
                for (int x: rg[i]) {
                    if (d[x]) continue;
                    d[x] = 1;
                    for (int y: rg[x]) {
                        count[y]--;
                    }
                }
            }
        }
        queue<int> q;
        for (int i = 0; i < V; i++) {
            if (count[i]) continue;
            q.push(i);
        }
        while (q.size()) {
            int p = q.front(); q.pop();
            if (d[p]) continue;
            d[p] = -1;
            for (int x: rg[p]) {
                if (d[x]) continue;
                d[x] = 1;
                for (int y: rg[x]) {
                    count[y]--;
                    if (!count[y]) {
                        q.push(y);
                    }
                }
            }
        }
        return;
    }
};
