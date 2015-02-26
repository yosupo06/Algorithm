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
		if (isSame(a, b)) return;
		gn--;
		int ga = i2g[a], gb = i2g[b];
		if (g2i[ga].length > g2i[gb].length) swap(ga, gb);
		foreach (i; g2i[ga]) i2g[i] = gb;
		g2i[gb] ~= g2i[ga];
		g2i[ga].length = 0;
	}

	bool isSame(int a, int b) {
		return i2g[a] == i2g[b];
	}

	int numGroup() {
		return gn;
	}
}