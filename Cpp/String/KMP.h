//!!!not verify!!!
vector<int> kmp(string s, int R[]) {
    vector<int> R(s.size()+1);
    R[0] = -1;
    int j = -1;
    for (int i = 0; i < s.size() ; i++) {
        while (j >= 0 && s[i] != s[j]) j = R[j];
        j++;
        R[i+1] = j;
    }
    return R;
}
