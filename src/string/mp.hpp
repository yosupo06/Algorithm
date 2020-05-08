template <class S> V<int> mp(const S& s) {
    int n = int(s.size());
    V<int> r(n + 1);
    r[0] = -1;
    for (int i = 0, j = -1; i < n; i++) {
        while (j >= 0 && s[i] != s[j]) j = r[j];
        j++;
        r[i + 1] = j;
    }
    return r;
}
