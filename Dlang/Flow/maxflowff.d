//O(FE) T=int only
class MaxFlow {
    struct EdgeC {
        int to;
        int cap;
        int rev;
    };
    EdgeC[][] g;
    bool[] used;
    this(int v) {
        g.length = used.length = v;
    }

    void addEdge(int from, int to, int cap) {
        g[from] ~= EdgeC(to, cap, cast(int)(g[to].length));
        g[to] ~= EdgeC(from, 0, cast(int)(g[from].length - 1));
    }

    void addMultiEdge(int from, int to, int cap) {
        g[from] ~= EdgeC(to, cap, cast(int)(g[to].length));
        g[to] ~= EdgeC(from, cap, cast(int)(g[from].length - 1));
    }
    int t;
    bool dfs(int s) {
        if (s == t) return true;
        if (used[s]) return false;
        used[s] = true;
        foreach (ref d; g[s]) {
            if (d.cap && dfs(d.to)) {
                d.cap -= 1;
                g[d.to][d.rev].cap += 1;
                return true;
            }
        }
        return false;
    }
    int maxFlow(int s, int _t) {
        assert(s != _t);
        t = _t;
        int flow = 0;
        while (true) {
            used[] = false;
            if (!dfs(s)) {
                break;
            }
            flow++;
        }
        return flow;
    }
};