template<class Str>
vector<int> kmp(Str s) {
    int n = (int)s.size();
    vector<int> R(n+1); R[0] = -1;
    for (int i = 0, j = -1; i < n; i++) {
        while (j >= 0 && s[i] != s[j]) j = R[j];
        j++;
        R[i+1] = j;
    }
    return R;
}
