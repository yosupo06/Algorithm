template<class Edge>
struct HLDecomp {
    VV<Edge> g;
    using P = pair<int, int>;
    V<P> id; //vertex -> [line id, line pos]
    VV<int> lines; //line id -> line list(top to bottom)
    V<P> par; //line id -> [parent line id, parent line pos]
    V<int> lineDPS; //line id -> line depth
    
    //buffer
    V<int> sz; //node size
    int idc;
    V<int> line_buf;
 
    HLDecomp(VV<Edge> g, int r) {
        int n = int(g.size());
        this->g = g;
        sz = V<int>(n);
        id = V<P>(n);
        dfs_sz(r, -1);
        idc = 0;
        par.push_back(P(-1, -1));
        lineDPS.push_back(0);
        dfs(r, -1, 0);
    }
    void dfs_sz(int p, int b) {
        sz[p] = 1;
        for (auto e: g[p]) {
            int d = e.to;
            if (d == b) continue;
            dfs_sz(d, p);
            sz[p] += sz[d];
        }
    }
    void dfs(int p, int b, int height) {
        line_buf.push_back(p);
        id[p] = P(idc, height);
        int nx = -1, buf = -1;
        for (auto e: g[p]) {
            if (e.to == b) continue;
            if (buf < sz[e.to]) {
                buf = sz[e.to];
                nx = e.to;
            }
        }
        if (nx == -1) {
            //make line
            lines.push_back(line_buf);
            line_buf.clear();
            idc++;
            return;
        }
        dfs(nx, p, height+1);
        for (auto e: g[p]) {
            if (e.to == b || e.to == nx) continue;
            par.push_back(id[p]);
            lineDPS.push_back(lineDPS[id[p].first] + 1);
            dfs(e.to, p, 0);
        }
    }
};
