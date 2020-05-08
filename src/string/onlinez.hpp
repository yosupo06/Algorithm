#pragma once

struct OnlineZ {
    string s;
    V<int> mp = {-1}, nx;
    int j = -1;
    V<int> inc(char c) {
        // calc nx
        s.push_back(c);
        if (mp.back() == -1)
            nx.push_back(-1);
        else
            nx.push_back(s[mp.back()] != c ? mp.back() : nx[mp.back()]);
        // calc mp
        int i = int(s.size()) - 1;
        while (j >= 0 && s[i] != s[j]) j = mp[j];
        j++;
        mp.push_back(j);

        V<int> res;
        int u = nx.back();
        while (u != -1) {
            if (s[u] != c) {
                res.push_back(int(s.size()) - 1 - u);
                u = mp[u];
            } else {
                u = nx[u];
            }
        }
        return res;
    }
};
