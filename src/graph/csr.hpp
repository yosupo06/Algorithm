#pragma once

struct CSR {
    V<int> to, start;
    CSR() {}
    CSR(int n, const V<pair<int, int>>& edges) {
        start = V<int>(n + 1);
        for (auto e : edges) {
            start[e.first]++;
        }
        for (int i = 1; i <= n; i++) {
            start[i] += start[i - 1];
        }
        to = V<int>(start.back());
        for (auto e : edges) {
            to[start[e.first] - 1] = e.second;
            start[e.first]--;
        }
    }
};
