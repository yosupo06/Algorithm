int V;
vector<int> g[MV], rg[MV];
bool us[MV];
vector<int> vs;
int cmp[MV];
void sccd(int v) {
    us[v] = true;
    for (int d: g[v]) {
        if (us[d]) continue;
        sccd(d);
    }
    vs.push_back(v);
}

void sccrd(int v, int k) {
    us[v] = true;
    cmp[v] = k;
    for (int d : rg[v]) {
        if (us[d]) continue;
        sccrd(d, k);
    }
}

void scc() {
    fill_n(us, MN*MM, false);
    for (int i = 0; i < V; i++) {
        if (us[i]) continue;
        sccd(i);
    }
    fill_n(us, MN*MM, false);
    int k = 0;
    for (int i = vs.size()-1; i >= 0; i--) {
        if (us[vs[i]]) continue;
        sccrd(vs[i], k++);
    }
}

class SCC {
    vector<int> g[MV];
    bool us[MV];
    vector<int> vs;
    SCC(int v) {
        
    }
};