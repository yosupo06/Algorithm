#pragma once

#include "base.hpp"
#include "graph/primitive.hpp"
#include "datastructure/hashset.hpp"
#include "datastructure/hashmap.hpp"
#include "datastructure/simplequeue.hpp"

struct TreeDecomp {
    VV<SimpleEdge> tr;
    VV<int> bags;
};


template <class E>
TreeDecomp decomp_width2(VV<E> _g) {
    int n = int(_g.size());
    assert(n);

    V<HashSet<int>> g(n);
    for (int i = 0; i < n; i++) {
        for (auto e : _g[i]) {
            int j = e.to;
            g[i].insert(j);
        }
    }

    V<int> deg(n);
    V<bool> alive(n, true);
    SimpleQueue<int> que;
    for (int i = 0; i < n; i++) {
        deg[i] = int(g[i].size());
        que.push(i);
    }

    struct Event {
        int deg;
        int a, b, c;
    };
    V<Event> events;

    V<int> nears;
    auto remove = [&](int p) {
        assert(alive[p]);
        alive[p] = false;
        for (int i: nears) {
            assert(alive[i]);
            g[i].erase(p);
            deg[i]--;
            que.push(i);
        }
    };
    while (que.size()) {
        int p = que.front();
        que.pop();
        int d = deg[p];
        if (!alive[p] || d >= 3) continue;
        nears = g[p].to_vec();
        assert(int(nears.size()) == d);
        if (d == 0) {
            events.push_back({0, p, -1, -1});
        }
        if (d == 1) {
            events.push_back({1, p, nears[0], -1});
        }
        if (d == 2) {
            int u = nears[0];
            int v = nears[1];
            events.push_back({2, p, u, v});
            g[u].insert(v);
            g[v].insert(u);
            deg[u] = int(g[u].size());
            deg[v] = int(g[v].size());
        }
        remove(p);
    }

    for (int i = 0; i < n; i++) {
        if (alive[i]) {
            return TreeDecomp{};
        }
    }

    TreeDecomp td;
    V<int> par;
    V<int> node_pos(n, -1);
    HashMap<pair<int, int>, int> edge_pos;
    reverse(events.begin(), events.end());
    for (auto event : events) {
        int id = int(td.bags.size());
        if (event.deg == 0) {
            td.bags.push_back({event.a});
            par.push_back(id - 1);
        }
        if (event.deg == 1) {
            td.bags.push_back({event.a, event.b});
            par.push_back(node_pos[event.b]);
        }
        if (event.deg == 2) {
            td.bags.push_back({event.a, event.b, event.c});
            par.push_back(edge_pos.get(minmax(event.b, event.c)));
        }
        for (int x : td.bags.back()) {
            node_pos[x] = id;
        }
        for (int x : td.bags.back()) {
            for (int y : td.bags.back()) {
                if (x < y) edge_pos.set({x, y}, id);
            }
        }
    }
    int K = int(td.bags.size());
    td.tr = VV<SimpleEdge>(K);
    for (int i = 1; i < K; i++) {
        td.tr[par[i]].push_back({i});
        td.tr[i].push_back({par[i]});
    }
    return td;
}
