struct Edge {
	int to;
};

struct EdgeDist {
	int to;
	int dist;
}

struct EdgeMCF {
	int to, rev;
	int dist;
	int cap;
}

void add_edge(VV<EdgeMCF> g, int from, int to, int dist, int cap) {
	g[from].push_back(EdgeMCF{to, int(g[to].size()), dist, cap});
	g[to].push_back(EdgeMCF{from, int(g[from].size())-1, -dist, 0});
}
