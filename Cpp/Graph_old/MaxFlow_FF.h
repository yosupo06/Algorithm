/**
 * F-F 流し戻しとかしたい時用
 */
template<int V>
struct MaxFlow {
    struct Edge {
        int to, rev, cap;
    };
    vector<Edge> g[V];
    /// 初期化
    void init() {
        for (int i = 0; i < V; i++) {
            g[i].clear();
        }
    }
    /// 有向辺の追加
    void add(int from, int to, int cap) {
        g[from].push_back(Edge{to, (int)g[to].size(), cap});
        g[to].push_back(Edge{from, (int)g[from].size()-1, 0});
    }
    /// 無向辺の追加
    void add_multi(int from, int to, int cap) {
        g[from].push_back(Edge{to, (int)g[to].size(), cap});
        g[to].push_back(Edge{from, (int)g[from].size()-1, cap});
    }

    void erase(int from, int to) {
        for (int i = 0; i < (int)g[from].size(); i++) {
            auto e = g[from][i];
            if (e.to == to && e.cap + g[to][e.rev].cap) {
                int c = e.cap - g[to][e.rev].cap;
                g[to][e.rev].cap = 0;
                g[from][i].cap = 0;
                return c;
            }
        }
        assert(false);
    }

    bool used[V];
    bool dfs(int s, int t) {
        if (s == t) return true;
        used[s] = true;
        for (auto &e : g[s]) {
            if (used[e.to]) continue;
            if (!e.cap) continue;
            if (dfs(e.to, t)) {
                e.cap -= 1;
                g[e.to][e.rev].cap += 1;
                return true;
            }
        }
        return false;
    }
    int exec(int s, int t, int F) {
        int f = 0;
        while (f < F) {
            fill_n(used, V, false);
            if (!dfs(s, t)) break;
            f++;
        }
        return f;
    }
};
