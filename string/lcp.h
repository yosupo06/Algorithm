template<class Str>
void makeLCP(SA<Str> &sa) {
    int n = (int)sa.s.size();
    sa.lcp.resize(n);
    int h = 0;
    for (int i = 0; i < n; i++) {
        int j = sa.sa[sa.rsa[i]-1];
        if (h > 0) h--;
        for (; j+h < n && i+h < n; h++) {
            if (sa.s[j+h] != sa.s[i+h]) break;
        }
        sa.lcp[sa.rsa[i]-1] = h;
    }
}
