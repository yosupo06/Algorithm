class MaxFlow(T) {
    struct EdgeC {
        int to;
        T cap;
        int rev;
    };
    EdgeC[][] g;
    int[] level, iter;

    this(int v) {
        g.length = level.length = iter.length = v;
    }

    void addEdge(int from, int to, T cap) {
        g[from] ~= EdgeC(to, cap, cast(int)(g[to].length));
        g[to] ~= EdgeC(from, 0, cast(int)(g[from].length - 1));
    }
    void addMultiEdge(int from, int to, T cap) {
        g[from] ~= EdgeC(to, cap, cast(int)(g[to].length));
        g[to] ~= EdgeC(from, cap, cast(int)(g[from].length - 1));
    }

    void bfs(int s) {
        level[] = -1;
        auto que = DList!int();
        level[s] = 0;
        que.insertBack(s);
        while (!que.empty) {
            int v = que.front(); que.removeFront();
            foreach (ref e; g[v]) {
                if (e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    que.insertBack(e.to);
                }
            }
        }
    }

    T dfs(int v, int t, T f) {
        if (v == t) return f;
        foreach (i, ref e; g[v][iter[v]..$]) {
            if (e.cap > 0 && level[v] < level[e.to]) {
                T d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    g[e.to][e.rev].cap += d;
                    return d;
                }
            }
            iter[v]++;
        }
        return 0;
    }

    int maxFlow(int s, int t) {
        int flow = 0;
        while (true) {
            bfs(s);
            if (level[t] < 0) return flow;
            iter[] = 0;
            T f;
            while ((f = dfs(s, t, T.max)) > 0) {
                flow += f;
            }
        }
    }
};