template <class S> V<int> manacher(const S& s) {
    int n = int(s.size());
    V<int> r(n);
    if (n == 0) return r;
    r[0] = 1;
    for (int i = 1, j = 0; i < n; i++) {
        int& k = r[i];
        k = (j + r[j] <= i) ? 0 : min(j + r[j] - i, r[2 * j - i]);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) k++;
        if (j + r[j] < i + r[i]) j = i;
    }
    return r;
}


template <class S> V<int> manacher_even(const S& s) {
    int n = int(s.size());
    V<int> r(n + 1);
    for (int i = 1, j = 0; i < n; i++) {
        int& k = r[i];
        k = (j + r[j] <= i) ? 0 : min(j + r[j] - i, r[2 * j - i]);
        while (0 <= i - 1 - k && i + k < n && s[i - 1 - k] == s[i + k]) k++;
        if (j + r[j] < i + r[i]) j = i;
    }
    return r;
}
