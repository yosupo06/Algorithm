typedef long long ll;

ll gcd(ll a, ll b) {
    if (b==0) return a;
    return gcd(b, a%b);
}

ll comb(int n, int k) {
    if (n < k) return 0;
    ll result = 1;
    for (int i = 1; i <= k; i++) {
        result *= n - i + 1;
        result /= i;
    }
    return result;
}

ll pow_mod(ll x, ll n, ll mod) {
	ll r = 1;
	while (n) {
		if (n & 1) r = (r * x) % mod;
		x = (x * x) % mod;
		n >>= 1;
	}
	return r;
}

ll invp(ll r, ll mod) {
	return pow_mod(r, mod-2, mod);
}

ll comb_pmod(int n, int k, ll mod) {
	if (n < k || k < 0) return 0;
	ll r = 1;
	for (int i = 1; i <= k; i++) {
		r *= i;
		r %= mod;
	}
	r = invp(r, mod);
	for (int i = n-k+1; i <= n; i++) {
		r = (r * i) % mod;
	}
	return r;
}
const int BIT_SIZE = MAX_N+1;
ll bit[BIT_SIZE] = {};
int bit_sum(ll *d, int add) {
    add++;
    ll s = 0;
    while (add > 0) {
        s += d[add-1];
        add -= add & -add;
    }
    return s;
}

void bit_add(ll *d, int add, ll x) {
    add++;
    while (add <= BIT_SIZE) {
        d[add-1] += x;
        add += add & -add;
    }
}

typedef pair<int, ll> bucket_query;
const int BACKET_SIZE = 320;
void bucket_make_query(vector<bucket_query> *v, ll l, ll r) {
    v->clear();
    if (l > r) return;
    int kl = (l+BACKET_SIZE-1)/BACKET_SIZE, kr = r/BACKET_SIZE-1;
    if (kl >= kr) {
        for (int i = l; i < r; i++) {
            v->push_back(bucket_query(0, i));
        }
        return;
    }
    for (int i = l; i < kl*BACKET_SIZE; i++) {
        v->push_back(bucket_query(0, i));
    }
    for (int i = kl; i < kr; i++) {
        v->push_back(bucket_query(1, i));
    }
    for (int i = kr*BACKET_SIZE; i < r; i++) {
        v->push_back(bucket_query(0, i));
    }
    return;    
}

constexpr int get_msb(int n) {
    return (n == (n & (-n))) ? n : get_msb(n - (n & (-n)));
}

constexpr int get_seg_size(int n) {
    return (n == (n & (-n))) ? n : get_msb(n - (n & (-n))) * 2;
}

const int MAX_M = 100010;
const int SEG_SIZE = get_seg_size(MAX_M);
P seg[SEG_SIZE];

void seg_init() {
    for (int i = 0; i < SEG_SIZE; i++) {
        seg[i] = P(1.0, 0.0);
    }
}

void seg_set(P *seg, int i, P x) {
    i += SEG_SIZE/2 - 1;
    seg[i] = x;
    while (i) {
        i = (i - 1) / 2;
        P s1 = seg[i*2+1], s2 = seg[i*2+2];
        seg[i] = P(s1.first*s2.first, s1.second*s2.first + s2.second);
    }
}
int seg_get(int *seg, int a, int b, int k = 0, int l = 0, int r = SEG_SIZE/2) {
    if (a <= l && r <= b) return seg[k];
    if (r <= a || b <= l) return -1;
    int vl = seg_get(seg, a, b, k*2+1, l, (l+r)/2);
    int vr = seg_get(seg, a, b, k*2+2, (l+r)/2, r);
    return max(vl, vr);
}
const int MAX_V = 210;
const int INT_INF = 1<<30;
typedef pair<int, int> P;
typedef tuple<int, int, int> T;
struct edge {
    int to, cap, cost, rev;
};
int V;
vector<edge> G[MAX_V];
int h[MAX_V], dist[MAX_V];
int prevv[MAX_V], preve[MAX_V];

void add_edge(int from, int to, int cap, int cost) {
    G[from].push_back((edge){to, cap, cost, (int)G[to].size()});
    G[to].push_back((edge){from, 0, -cost, (int)G[from].size()-1});
}

int min_cost_flow(int s, int t, int f) {
    int res = 0;
    fill_n(h, V, 0);
    while (f > 0) {
        priority_queue<P, vector<P>, greater<P>> que;
        fill_n(dist, V, INT_INF);
        dist[s] = 0;
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
        if (dist[t] == INT_INF) {
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

struct edge {int to, cap, rev;};

vector<edge> G[MAX_V], G2[MAX_V];
int level[MAX_V];
int iter[MAX_V];

void add_edge_multi(int from, int to, int cap) {
    G2[from].push_back((edge){to, cap, (int)G2[to].size()});
    G2[to].push_back((edge){from, cap, (int)G2[from].size()-1});
}

void bfs(int s) {
    fill_n(level, MAX_V, -1);
    queue<int> que;
    level[s] = 0;
    que.push(s);
    while (!que.empty()) {
        int v = que.front(); que.pop();
        for (int i = 0; i < G[v].size(); i++) {
            edge &e = G[v][i];
            if (e.cap > 0 && level[e.to] < 0) {
                level[e.to] = level[v] + 1;
                que.push(e.to);
            }
        }
    }
}

int dfs (int v, int t, int f) {
    if (v == t) return f;
    for (int &i = iter[v]; i < G[v].size(); i++) {
        edge &e = G[v][i];
        if (e.cap > 0 && level[v] < level[e.to]) {
            int d = dfs(e.to, t, min(f, e.cap));
            if (d > 0) {
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int max_flow(int s, int t) {
    int flow = 0;
    while (true) {
        bfs(s);
        if (level[t] < 0) return flow;
        fill_n(iter, MAX_V, 0);
        int f;
        while ((f = dfs(s, t, INT_INF)) > 0) {
            flow += f;
        }
    }
}

/* comb_fill_pmod
d[0][0] = 1;
fill(d+1, d+n, 0)
for (int i = 1; i < n; i++) {
    d[i][0] = 1;
    for (int j = 1; j < k; j++) {
        d[i][j] = (d[i-1][j] + d[i-1][j-1]) % mod;
    }
}
*/