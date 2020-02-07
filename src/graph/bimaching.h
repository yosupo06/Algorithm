#pragma once

#include "datastructure/simplequeue.h"
#include "graph/csr.h"

struct BipartiteMaching {
  public:
    int n, m;
    V<int> lmt, rmt;

    BipartiteMaching(int _n, int _m, V<pair<int, int>> edges)
        : n(_n), m(_m), lmt(n, -1), rmt(m, -1), dist(m) {
        for (auto e : edges) {
            int l, r;
            tie(l, r) = e;
            if (lmt[l] == -1 && rmt[r] == -1) {
                lmt[l] = r;
                rmt[r] = l;
            }
        }
        lg = CSR(n, edges);
        for (auto& e : edges) swap(e.first, e.second);
        rg = CSR(m, edges);

        while (true) {
            bfs();
            // if (trg_dist >= 20) break;
            if (trg_dist == TEN(9)) break;
            bool f = dfs();
            assert(f);
        }
    }

  private:
    CSR lg, rg;

    int trg_dist;
    V<int> dist;
    SimpleQueue<int> que;
    void bfs() {
        trg_dist = TEN(9);
        que.clear();
        for (int i = 0; i < m; i++) {
            if (rmt[i] == -1) {
                dist[i] = 0;
                que.push(i);
            } else {
                dist[i] = TEN(9);
            }
        }
        while (!que.empty()) {
            int q = que.front();
            que.pop();
            int distq = dist[q];
            for (int pid = rg.start[q]; pid < rg.start[q + 1]; pid++) {
                int p = rg.to[pid];
                int next = lmt[p];
                if (next == -1) {
                    trg_dist = distq + 1;
                    return;
                }
                if (dist[next] == TEN(9)) {
                    dist[next] = distq + 1;
                    que.push(next);
                }
            }
        }
    }
    bool dfs() {
        bool update = false;
        for (int i = 0; i < n; i++) {
            if (lmt[i] == -1 && dfs(i, trg_dist)) {
                update = true;
            }
        }
        return update;
    }
    bool dfs(int p, int distp) {
        int st = lg.start[p], ls = lg.start[p + 1];
        for (int qid = st; qid < ls; qid++) {
            int q = lg.to[qid];
            if (distp - 1 == dist[q]) {
                int next = rmt[q];
                if (next != -1) {
                    dist[q] = TEN(9);
                    if (!dfs(next, distp - 1)) continue;
                }
                lmt[p] = q;
                rmt[q] = p;
                return true;
            }
        }
        return false;
    }
};
