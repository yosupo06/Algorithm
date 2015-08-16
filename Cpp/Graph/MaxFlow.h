/**
 * Dinic法による最大流
 *
 * ほとんど蟻本そのまま
 * template引数のint Vは頂点数
 */
template<int V>
struct MaxFlow {
    using T = int; /// 辺の重みの型
    const T INF = 1<<28;
    struct Edge {
        int to, rev;
        T cap;
    };
    vector<Edge> g[V];
    int level[V];
    int iter[V];
    /// 初期化
    void init() {
        for (int i = 0; i < V; i++) {
            g[i].clear();
        }
    }
    /// 有向辺の追加
    void add(int from, int to, T cap) {
        g[from].push_back(Edge{to, (int)g[to].size(), cap});
        g[to].push_back(Edge{from, (int)g[from].size()-1, 0});
    }
    /// 無向辺の追加
    void add_multi(int from, int to, T cap) {
        g[from].push_back(Edge{to, (int)g[to].size(), cap});
        g[to].push_back(Edge{from, (int)g[from].size()-1, cap});
    }

    void bfs(int s) {
        fill_n(level, V, -1);
        queue<int> que;
        level[s] = 0;
        que.push(s);
        while (!que.empty()) {
            int v = que.front(); que.pop();
            for (Edge e: g[v]) {
                if (e.cap <= 0) continue;
                if (level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    que.push(e.to);
                }
            }
        }
    }

    T dfs(int v, int t, T f) {
        if (v == t) return f;
        for (int &i = iter[v]; i < (int)g[v].size(); i++) {
            Edge &e = g[v][i];
            if (e.cap <= 0) continue;
            if (level[v] < level[e.to]) {
                T d = dfs(e.to, t, min(f, e.cap));
                if (d <= 0) continue;
                e.cap -= d;
                g[e.to][e.rev].cap += d;
                return d;
            }
        }
        return 0;
    }

    // sからtへの最大流を返す
    T exec(int s, int t) {
        T flow = 0;
        while (true) {
            bfs(s);
            if (level[t] < 0) return flow;
            fill_n(iter, V, 0);
            T f;
            while ((f = dfs(s, t, INF)) > 0) {
                flow += f;
            }
        }
    }
};

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
