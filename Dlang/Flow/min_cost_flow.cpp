const int INT_INF = 1 << 29;
const ll INF = 1LL<<55;

struct edge {
	int to;
	int cap;
	ll cost;
	int rev;
};

const int MAX_V = 20010;
int V;
vector<edge> G[MAX_V];
ll h[MAX_V], dist[MAX_V];
int prevv[MAX_V], preve[MAX_V];

void add_edge(int from, int to, int cap, ll cost) {
	G[from].push_back((edge){to, cap, cost, (int)G[to].size()});
	G[to].push_back((edge){from, 0, -cost, (int)G[from].size()-1});
}

ll min_cost_flow(int s, int t, int f, bool bell = false) {
	using P = pair<int, int>;
	ll res = 0;
	fill_n(h, V, 0);
	while (f > 0) {
		fill_n(dist, V, INF);
		dist[s] = 0;
		if (bell) {
			bell = false;
			bool update;
			do {
				update = false;
				for (int v = 0; v < V; v++) {
					if (dist[v] == INF) continue;
					for (int i = 0; i < G[v].size(); i++) {
						edge &e = G[v][i];
						if (e.cap > 0 && dist[e.to] > dist[v] + e.cost) {
							dist[e.to] = dist[v] + e.cost;
							prevv[e.to] = v;
							preve[e.to] = i;
							update = true;
						}
					}
				}
			} while (update);
		} else {
			priority_queue<P, vector<P>, greater<P>> que;
			que.push(P(0, s));
			while (!que.empty()) {
				P p = que.top(); que.pop();
				int v = p.second;
				if (dist[v] < p.first) continue;
				for (int i = 0; i < G[v].size(); i++) {
					edge &e = G[v][i];
					if (e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
						dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
						prevv[e.to] = v;
						preve[e.to] = i;
						que.push(P(dist[e.to], e.to));
					}
				}
			}
		}
		if (dist[t] == INF) {
			return -1;
		}
		for (int v = 0; v < V; v++) {
			h[v] += dist[v];
		}

		int d = f;
		for (int v = t; v != s; v = prevv[v]) {
			d = min(d, G[prevv[v]][preve[v]].cap);
		}
		f -= d;
		res += d * h[t];
		for (int v = t; v != s; v = prevv[v]) {
			edge &e = G[prevv[v]][preve[v]];
			e.cap -= d;
			G[v][e.rev].cap += d;
		}
	}
	return res;
}
