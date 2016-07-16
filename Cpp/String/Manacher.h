//!!!not verify!!!
vector<int> manacher(string s) {
    int n = (int)s.size();
    vector<int> R(n+1); R[0] = 0;
    for (int i = 0, j = 0; i < n; i++) {
        int &k = R[i]; k = (j + R[j] <= i) ? 0 : min(j+R[j]-i, R[2*j-i]);
        while (0 <= i-k and i+k < n and s[i-k] == s[i+k]) k++;
        if (j + R[j] < i + R[i]) j = i;
    }
    return R;
}
