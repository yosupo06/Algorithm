class SCC {
	int v;
	int[][] g, rg;
	this(int V) {
		v = V;
		rg.length = g.length = v;
	}

	void addEdge(int x, int y) {
		g[x] ~= y;
		g[y] ~= x;
	}
	bool[] us;
	int[] cmp, vs;
	void dfs(int v) {
		us[v] = true;
		foreach (d; g[v]) {
			if (us[d]) continue;
			dfs(d);
		}
		vs ~= v;
	}
	void rdfs(int v, int k) {
		us[v] = true;
		cmp[v] = k;
		foreach (d; rg[v]) {
			if (us[d]) continue;
			rdfs(d, k);
		}
	}
	void scc() {
		us.length = cmp.length = v;
		us[] = false;
		foreach (i; 0..v) {
			if (us[i]) continue;
			dfs(i);
		}
		us[] = false;
		int k = 0;
		foreach_reverse (d; vs) {
			if (us[d]) continue;
			sccrd(d, k++);
		}
	}
}