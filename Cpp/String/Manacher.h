int manacher(string s, int R[]) {
    int n = (int)s.size();
    for (int i = 0, j = 0; i < n; i++) {
        int &k = R[i]; k = min(j+R[j]-i, R[2*j-i]);
        while (0 <= i-k and i+k < n and s[i-k] == s[i+k]) k++;
        if (j + R[j] < i + R[i]) j = i;
    }
}