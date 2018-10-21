// s[0..res[i]] == s[i..i+res[i]]
template <class S> V<int> z_algo(const S& s) {
    int n = int(s.size());
    V<int> R(n + 1);
    R[0] = 0;
    for (int i = 1, j = 0; i <= n; i++) {
        int& k = R[i];
        k = (j + R[j] <= i) ? 0 : min(j + R[j] - i, R[i - j]);
        while (i + k < n && s[k] == s[i + k]) k++;
        if (j + R[j] < i + R[i]) j = i;
    }
    R[0] = n;
    return R;
}
