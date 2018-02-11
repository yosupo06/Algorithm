/**
 * Edge Sample
 * ---
 * void add_edge(Graph<Edge> &g, int from, int to, int cap) {
 *     g[from].push_back(Edge{to, cap, (int)g[to].size()});
 *     g[to].push_back(Edge{from, 0, (int)g[from].size()-1});
 * }
 * ---
 */

template<class C>
struct MaxFlow {
    C flow;
    V<bool> dual;
};

template<class C, C EPS, class E>
struct MF_EXEC {
    static const C INF = numeric_limits<C>::max();
    VV<E> &g;
    int s, t;
    int N;
    V<int> level, iter;

    MaxFlow<C> info;
    MF_EXEC(VV<E> &g, int s, int t): g(g), s(s), t(t) {
        N = int(g.size());
        level = V<int>(N);
        iter = V<int>(N);

        C flow = 0;
        while (true) {
            bfs();
            if (level[t] < 0) break;
            fill(begin(iter), end(iter), 0);
            while (true) {
                C f = dfs(s, INF);
                if (!f) break;
                flow += f;
            }
        }
        V<bool> dual(N);
        for (int i = 0; i < N; i++) {
            dual[i] = level[i] == -1;
        }
        info = MaxFlow<C>{flow, dual};
    }

    void bfs() {
        queue<int> que;
        fill(begin(level), end(level), -1);
        level[s] = 0;
        que.push(s);
        while (!que.empty()) {
            int v = que.front(); que.pop();
            for (E e: g[v]) {
                if (e.cap <= EPS) continue;
                if (level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    que.push(e.to);
                }
            }
        }
    }

    C dfs(int v, C f) {
        if (v == t) return f;
        C res = 0;
        for (int &i = iter[v]; i < int(g[v].size()); i++) {
            E &e = g[v][i];
            if (e.cap <= EPS) continue;
            if (level[v] >= level[e.to]) continue;
            C d = dfs(e.to, min(f, e.cap));
            e.cap -= d;
            g[e.to][e.rev].cap += d;
            res += d;
            f -= d;
            if (f == 0) break;
        }
        return res;
    }
};

template<class C, C EPS, class E>
MaxFlow<C> max_flow(VV<E> &g, int s, int t) {
    return MF_EXEC<C, EPS, E>(g, s, t).info;
}
