const int MAX_V = 210;

double G[MAX_V+1][MAX_V+1], h[MAX_V*2+2], dist[MAX_V*2+2];
int prevv[MAX_V*2+2];
bool used[MAX_V*2+2];
bool flow[MAX_V+1][MAX_V+1] = {};

double bit_matching_cost(int l, int r) {
    double res = 0, min_f = 0;
    auto inf = INFINITY;
    auto eps = 1e-10;
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < r; j++) {
            min_f = min(min_f, G[i][j]);
        }
    }
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < r; j++) {
            G[i][j] -= min_f;
        }
    }
    for (int i = 0; i < l; i++) {
        G[i][r] = 0;
        flow[i][r] = true;
    }
    for (int i = 0; i < r; i++) {
        G[l][i] = 0;
        flow[l][i] = true;
    }
    G[l][r] = inf;
    flow[l][r] = false;
    fill_n(h, l+r+2, 0);
    while (true) {
        fill_n(dist, l+r+2, inf);
        dist[l+r+1] = 0;
        fill_n(used, l+r+2, false);
        while (true) {
            int v = -1;
            for (int i = 0; i < l+r+2; i++) {
                if (!used[i] && (v == -1 || dist[v] - dist[i] > eps)){
                    v = i;
                }
            }
            if (v == -1) break;
            used[v] = true;
            if (v < l+1) {
                for (int i = l+1; i < l+r+2; i++) {
                    auto f = dist[v] + G[v][i-(l+1)] + h[v] - h[i];
                    if (!flow[v][i-(l+1)] && dist[i] - f > eps) {
                        dist[i] = f;
                        prevv[i] = v;
                    }
                }
            } else {
                for (int i = 0; i < l+1; i++) {
                    auto f = dist[v] - G[i][v-(l+1)] + h[v] - h[i];
                    if (flow[i][v-(l+1)] && dist[i] - f > eps) {
                        dist[i] = f;
                        prevv[i] = v;
                    }
                }
            }
        }
        if (dist[l] >= inf) {
            break;
        }
        for (int v = 0; v < l+r+2; v++) {
            h[v] += dist[v];
        }
        res += h[l];
        res += min_f;
        for (int v = l; v != l+r+1 ; v = prevv[v]) {
            if (v < l+1) {
                flow[v][prevv[v]-(l+1)] = false;
            } else {
                flow[prevv[v]][v-(l+1)] = true;
            }
        }
    }
    return res;
}
