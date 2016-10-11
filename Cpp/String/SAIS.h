template<class Str>
struct SA {
    Str s;
    vector<int> sa, rsa, lcp;

    vector<bool> ls;
    SA(Str s, int B = 128) : s(s) {
        int n = (int)s.size();
        sa.resize(n+1); rsa.resize(n+1); lcp.clear();
        ls.resize(n+1); //L:false S:true

        vector<int> l_ba(B, 0), s_ba(B, 0), l_basm(B+1), s_basm(B+1);
        ls[n] = true;
        for (int i = n-1; i >= 0; i--) {
            ls[i] = ls[i+1];
            if (i == n-1 || s[i] > s[i+1]) {
                ls[i] = false;
            } else if (s[i] < s[i+1]) {
                ls[i] = true;
            }
            if (!ls[i]) {
                l_ba[s[i]]++;
            } else {
                s_ba[s[i]]++;
            }
        }

        // l[0], s[0], l[1], s[1], ...
        l_basm[0] = 1; s_basm[0] = 1+l_ba[0];
        for (int i = 1; i <= B; i++) {
            l_basm[i] = s_basm[i-1]+s_ba[i-1];
            s_basm[i] = l_basm[i]+l_ba[i];
        }

        vector<int> v, lms(n+1, -1); // lms list
        for (int i = 1; i < n; i++) {
            if (!ls[i-1] && ls[i]) {
                lms[i] = int(v.size());
                v.push_back(i);
            }
        }

        if (v.size()) {
            vector<int> v2 = v, buf = s_basm;
            fill(begin(sa), end(sa), -1);
            sa[0] = n;
            for (int i = 0; i < int(v.size()); i++) {
                int c = s[v[i]];
                sa[buf[c]++] = v[i];
            }
            induce(l_basm);
            for (int i = 1, c = 0; i <= n; i++) {
                if (lms[sa[i]] == -1) continue;
                v[c++] = sa[i];
            }

            vector<int> s2(v.size());
            int c = 0;
            s2[lms[v[0]]] = 0;
            for (int i = 1; i < int(v.size()); i++) {
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
            vector<int> ch_sa = SA<vector<int>>(s2, c+1).sa;
            for (int i = 0; i < int(v.size()); i++) {
                v[i] = v2[ch_sa[i+1]];
            }
        }

        vector<int> buf = s_basm;
        fill_n(sa.begin(), n+1, -1);
        sa[0] = n;
        for (int i = 0; i < int(v.size()); i++) {
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
                int first = s[sa[i]-1]; // first char
                sa[buf[first]++] = sa[i]-1;
            }
        }
        buf = lba_sm;
        for (int i = n; i > 0; i--) {
            if (sa[i] >= 1 && ls[sa[i]-1]) {
                int first = s[sa[i]-1]; // first char
                sa[--buf[first+1]] = sa[i]-1;
            }
        }
    }
};
