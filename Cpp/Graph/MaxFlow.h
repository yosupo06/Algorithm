/**
 * Dinic法による最大流
 *
 * ほとんど蟻本そのまま
 * template引数のint Vは頂点数
 * Edgeにはrevが必要
 * ---
 * void add_edge(Graph<Edge> &g, int from, int to, int cap) {
 *     g[from].push_back(Edge{to, cap, (int)g[to].size()});
 *     g[to].push_back(Edge{from, 0, (int)g[from].size()-1});
 * }
 * ---
 */
template<class C, C INF> // Cap
struct MaxFlow {
    int V;
    vector<int> level, iter;
    //gを破壊するので注意
    template<class E>
    C exec(Graph<E> &g, int s, int t) {
        V = (int)g.size();
        level.resize(V);
        iter.resize(V);
        C flow = 0;
        while (true) {
            bfs(g, s);
            if (level[t] < 0) return flow;
            fill_n(iter.begin(), V, 0);
            while (true) {
                C f = dfs(g, s, t, INF);
                if (!f) break;
                flow += f;
            }
        }
    }

    template<class E>
    void bfs(const Graph<E> &g, int s) {
        fill_n(level.begin(), V, -1);
        queue<int> que;
        level[s] = 0;
        que.push(s);
        while (!que.empty()) {
            int v = que.front(); que.pop();
            for (E e: g[v]) {
                if (e.cap <= 0) continue;
                if (level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    que.push(e.to);
                }
            }
        }
    }

    template<class E>
    C dfs(Graph<E> &g, int v, int t, C f) {
        if (v == t) return f;
        for (int &i = iter[v]; i < (int)g[v].size(); i++) {
            E &e = g[v][i];
            if (e.cap <= 0) continue;
            if (level[v] < level[e.to]) {
                C d = dfs(g, e.to, t, min(f, e.cap));
                if (d <= 0) continue;
                e.cap -= d;
                g[e.to][e.rev].cap += d;
                return d;
            }
        }
        return 0;
    }
};
