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

template<class Str>
vector<int> manacherEven(Str s) {
    int n = (int)s.size();
    vector<int> R(n-1);
    if (n == 1) return R;
    R[0] = (s[0] == s[1] ? 1 : 0);
    for (int i = 1, j = 0; i < n-1; i++) {
        int &k = R[i]; k = (j + R[j] <= i) ? 0 : min(j+R[j]-i, R[2*j-i]);
        while (0 <= i-k and i+1+k < n and s[i-k] == s[i+1+k]) k++;
        if (j + R[j] < i + R[i]) j = i;
    }
    return R;
}
