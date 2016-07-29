template<class Str>
vector<int> manacher(Str s) {
    int n = (int)s.size();
    vector<int> R(n); R[0] = 1;
    for (int i = 1, j = 0; i < n; i++) {
        int &k = R[i]; k = (j + R[j] <= i) ? 0 : min(j+R[j]-i, R[2*j-i]);
        while (0 <= i-k and i+k < n and s[i-k] == s[i+k]) k++;
        if (j + R[j] < i + R[i]) j = i;
    }
    return R;
}
