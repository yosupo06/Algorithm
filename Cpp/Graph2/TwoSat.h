/**
 * TwoSat
 * !!!not verify!!!
 */
struct TwoSat {
    int V;
    vector<bool> res;
    bool exec() {
        scc.exec(2*V);
        for (int i = 0; i < V; i++) {
            if (scc.res[i] == scc.res[i+V]) return false;
            res[i] = scc.res[i] > scc.res[i+V];
        }
        return true;
    }

    struct Edge { int to; };
    Graph<Edge> g, rg;
    TwoSat(int V) : V(V) {
        g = Graph<Edge>(2*V);
        res.resize(V);
    }
    void addEdge(int a, int b) {
        g[a].push_back(b);
        rg[b].push_back(a);
    }
    void add(int a, bool apos, int b, bool bpos) {
        addEdge(a+(apos?V:0), b+(bpos?0:V));
        addEdge(b+(bpos?V:0), a+(apos?0:V));
    }
}

