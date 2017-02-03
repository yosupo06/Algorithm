class LowestCommonAncestor {
	static const MD = 21; //max depth = 2**MD
	int[][] g;
	int[MD][] parent;
	int[] depth;
	void dfs(int v, int b, int d) {
		parent[v][0] = b;
		foreach (k; 1..MD) {
			auto u = parent[v][k-1];
			parent[v][k] = (u < 0) ? -1 : parent[u][k-1];
		}
		depth[v] = d;
		foreach (j; g[v]) {
			if (j != b) dfs(j, v, d+1);
		}
	}

	this (int[][] graph, int root) {
		g = graph;
		depth = new int[g.length];
		parent = new int[MD][](g.length);
		dfs(root, -1, 0);
	}

	int lca(int u, int v) {
		if (depth[u] > depth[v]) swap(u, v);
		auto d = depth[v] - depth[u];
		foreach (k; 0..MD) {
			if (d & 1) {
				v = parent[v][k];
			}
			d >>= 1;
		}
		if (u == v) return u;
		foreach_reverse (k; 0..MD) {
			if (parent[u][k] != parent[v][k]) {
				u = parent[u][k];
				v = parent[v][k];
			}
		}
		return parent[u][0];
	}
}