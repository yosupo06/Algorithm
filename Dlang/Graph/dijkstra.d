/**
 * Example:
 * -----
 * struct Edge(C) {
 *   int to;
 *   C cost;
 * }
 * -----
 */

C[] dijkstra(C = typeof(E.cost), E)(in E[][] graph, int s) {
    import std.typecons : Tuple;
    import std.container : Array, BinaryHeap;
    alias Q = Tuple!(int, "to", C, "cost");

    auto n = graph.length;
    C[] dist = new C[graph.length]; dist[] = C.max;
    bool[] used = new bool[n];
    auto que = BinaryHeap!(Array!Q, "a.cost > b.cost")();
    dist[s] = 0;
    que.insert(Q(s, 0));
    while (!que.empty) {
        auto p = que.front.to; que.popFront;
        if (used[p]) continue;
        used[p] = true;
        foreach (E e; graph[p]) {
            if (dist[e.to] > dist[p] + e.cost) {
                dist[e.to] = dist[p] + e.cost;
                que.insert(Q(e.to, dist[e.to]));
            }
        }
    }
    return dist;
}

unittest {
    import std.random;
    import std.typecons;
    auto gen = Random(unpredictableSeed);
    // check with 1000 random case
    foreach (_; 0..1000) {
        int N = uniform(1, 20, gen);
        int[][] d = new int[][](N, N);
        foreach (i; 0..N) {
            foreach (j; 0..N) {
                if (i == j) continue;
                if (uniform(0, 4, gen) == 0) {
                    d[i][j] = uniform(1, 1000, gen);
                } else {
                    d[i][j] = int.max;
                }
            }
        }

        alias Edge = Tuple!(int, "to", int, "cost");
        Edge[][] g = new Edge[][](N);
        foreach (i; 0..N) {
            foreach (j; 0..N) {
                if (i == j) continue;
                if (d[i][j] < int.max) {
                    g[i] ~= Edge(j, d[i][j]);
                }
            }
        }
        int[][] dijk_res = new int[][](N);
        foreach (i; 0..N) {
            dijk_res[i] = dijkstra(g, i);
        }
        foreach (k; 0..N) {
            foreach (i; 0..N) {
                foreach (j; 0..N) {
                    if (d[i][k] < int.max && d[k][j] < int.max) {
                        import std.algorithm : min;
                        d[i][j] = min(d[i][j], d[i][k]+d[k][j]);
                    }
                }
            }
        }
        foreach (i; 0..N) {
            foreach (j; 0..N) {
                assert(dijk_res[i][j] == d[i][j]);
            }
        }
    }
    // check with 1000 random case(double)
    foreach (_; 0..1000) {
        int N = uniform(1, 20, gen);
        double[][] d = new double[][](N, N);

        foreach (i; 0..N) {
            foreach (j; 0..N) {
                if (i == j) {
                    d[i][j] = 0;
                    continue;
                }
                if (uniform(0, 4, gen) == 0) {
                    d[i][j] = uniform(1f, 1000f, gen);
                } else {
                    d[i][j] = float.max;
                }
            }
        }
        alias Edge = Tuple!(int, "to", double, "cost");
        Edge[][] g = new Edge[][](N);
        foreach (i; 0..N) {
            foreach (j; 0..N) {
                if (i == j) continue;
                if (d[i][j] < double.max) {
                    g[i] ~= Edge(j, d[i][j]);
                }
            }
        }
        double[][] dijk_res = new double[][](N);
        foreach (i; 0..N) {
            dijk_res[i] = dijkstra(g, i);
        }
        foreach (k; 0..N) {
            foreach (i; 0..N) {
                foreach (j; 0..N) {
                    if (d[i][k] < double.max && d[k][j] < double.max) {
                        import std.algorithm : min;
                        d[i][j] = min(d[i][j], d[i][k]+d[k][j]);
                    }
                }
            }
        }
        foreach (i; 0..N) {
            foreach (j; 0..N) {
                assert(dijk_res[i][j] - d[i][j] < 1e-10);
            }
        }
    }
}