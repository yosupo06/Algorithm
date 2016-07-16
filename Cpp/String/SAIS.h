template<class Str>
struct SA {
    Str s;
    vector<int> sa, rsa, lcp;

    vector<bool> ls;
    SA(Str s, int B = 200) : s(s) {
        int n = (int)s.size();
        sa.resize(n+1); rsa.resize(n+1); lcp.clear();
        ls.resize(n+1); //L:false S:true

        vector<int> l_ba(B), s_ba(B), l_basm(B+1), s_basm(B+1);
        fill_n(l_ba.begin(), B, 0); fill_n(s_ba.begin(), B, 0);
        ls[n] = true;
        for (int i = n-1; i >= 0; i--) {
            if (i == n-1 || s[i] > s[i+1]) {
                ls[i] = false;
            } else if (s[i] < s[i+1]) {
                ls[i] = true;
            } else {
                ls[i] = ls[i+1];
            }
            if (!ls[i]) {
                l_ba[s[i]]++;
            } else {
                s_ba[s[i]]++;
            }
        }

        l_basm[0] = 1; s_basm[0] = 1+l_ba[0];
        for (int i = 1; i <= B; i++) {
            l_basm[i] = s_basm[i-1]+s_ba[i-1];
            s_basm[i] = l_basm[i]+l_ba[i];
        }

        vector<int> v;
        int lms[n+1];
        fill_n(lms, n+1, -1);
        int c = 0;
        for (int i = 1; i < n; i++) {
            if (!ls[i-1] && ls[i]) {
                lms[i] = c++;
                v.push_back(i);
            }
        }

        if (v.size()) {
            vector<int> v2 = v;
            int buf[B+1];
            copy_n(s_basm.begin(), B+1, buf);
            fill_n(sa.begin(), n+1, -1);
            sa[0] = n;
            for (int i = 0; i < (int)v.size(); i++) {
                int c = s[v[i]];
                sa[buf[c]++] = v[i];
            }
            induce(l_basm);
            int c = 0;
            for (int i = 1; i <= n; i++) {
                if (lms[sa[i]] == -1) continue;
                v[c++] = sa[i];
            }

            vector<int> s2(v.size());
            c = 0;
            s2[lms[v[0]]] = 0;
            for (int i = 1; i < (int)v.size(); i++) {
                int l = v[i-1], r = v[i];
                while (true) {
                    if (s[l] != s[r]) {
                        c++;
                        break;
                    }
                    l++; r++;
                    if (lms[l] != -1 || lms[r] != -1) {
                        if (lms[l] == -1 || lms[r] == -1) {
                            c++;
                        }
                        break;
                    }
                }
                s2[lms[v[i]]] = c;
            }
            SA<vector<int>> sa_child(s2, c+1);
            for (int i = 1; i <= (int)v.size(); i++) {
                v[i-1] = v2[sa_child.sa[i]];
            }
        }

        int buf[B+1];
        copy_n(s_basm.begin(), B+1, buf);

        fill_n(sa.begin(), n+1, -1);
        sa[0] = n;
        for (int i = 0; i < (int)v.size(); i++) {
            int c = s[v[i]];
            sa[buf[c]++] = v[i];
        }

        induce(l_basm);

        for (int i = 0; i <= n; i++) {
            rsa[sa[i]] = i;
        }
    }

    void induce(vector<int> &lba_sm) {
        int n = (int)s.size();
        vector<int> buf;
        buf = lba_sm;
        for (int i = 0; i <= n; i++) {
            if (sa[i] >= 1 && !ls[sa[i]-1]) {
                int bc = s[sa[i]-1];
                sa[buf[bc]++] = sa[i]-1;
            }
        }
        buf = lba_sm;
        for (int i = n; i > 0; i--) {
            if (sa[i] >= 1 && ls[sa[i]-1]) {
                int bc = s[sa[i]-1];
                sa[--buf[bc+1]] = sa[i]-1;
            }
        }
    }
};
