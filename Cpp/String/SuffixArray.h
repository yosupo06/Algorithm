template<int N>
struct SA {
	static int n, k;
	static int rank[N+1], tmp[N+1];

	static bool com(int i, int j) {
		if (rank[i] != rank[j]) return rank[i] < rank[j];
		int ri = i+k <= n ? rank[i+k] : -1;
		int rj = j+k <= n ? rank[j+k] : -1;
		return ri < rj;
	}

	void con(string S, int *sa) {
		int n = (int)S.size();
		for (int i = 0; i <= n; i++) {
			sa[i] = i;
			rank[i] = i < n ? S[i] : -1;
		}
		for (k = 1; k <= n; k *= 2) {
			sort(sa, sa+n+1, com);
			tmp[sa[0]] = 0;
			for (int i = 1; i <= n; i++) {
				tmp[sa[i]] = tmp[sa[i-1]] + (com(sa[i-1], sa[i]) ? 1 : 0);
			}
			for (int i = 0; i <= n; i++) {
				rank[i] = tmp[i];
			}
		}
	}
};
