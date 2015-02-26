/**
 * Quick Find Weighted
 * merge:O(logN)
 * isSame:O(1)
 * numGroup:O(1)
 */

class UnionFind {
	int[] i2g;
	int[][] g2i;
	int gn;
	this(int n) {
		i2g = new int[](n);
		g2i = new int[][](n);
		gn = n;
		foreach (i; 0..n) {
			i2g[i] = i;
			g2i[i] = [i];
		}
	}

	void merge(int a, int b) {
		import std.algorithm : swap;
		if (isSame(a, b)) return;
		gn--;
		int ga = i2g[a], gb = i2g[b];
		//gaにgbを統合する
		if (g2i[ga].length < g2i[gb].length) swap(ga, gb);
		foreach (i; g2i[gb]) i2g[i] = ga;
		g2i[ga] ~= g2i[gb];
		g2i[gb].length = 0;
	}

	bool isSame(int a, int b) {
		return i2g[a] == i2g[b];
	}

	int numGroup() {
		return gn;
	}
}

unittest {
	auto uf = new UnionFind(5);
	uf.merge(3, 3);
	uf.merge(2, 4);
	uf.merge(1, 3);
	uf.merge(0, 2);
	//[0-2-4, 1-3]
	assert(uf.isSame(0, 3) == false);
	assert(uf.isSame(4, 0) == true);
	assert(uf.numGroup == 2);
}