#include <bits/stdc++.h>

#define eb emplace_back
#define ep emplace
#define fi first
#define se second
#define in read<int>()
#define lin read<ll>()
#define rep(i, x, y) for(int i = (x); i <= (y); i++)
#define per(i, x, y) for(int i = (x); i >= (y); i--)

using namespace std;

using ll = long long;
using db = double;
using pii = pair < int, int >;
using vec = vector < int >;
using veg = vector < pii >;

template < typename T > T read() {
	T x = 0; bool f = 0; char ch = getchar();
	while(!isdigit(ch)) f |= ch == '-', ch = getchar();
	while(isdigit(ch)) x = x * 10 + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}

template < typename T > void chkmax(T &x, const T &y) { x = x > y ? x : y; }
template < typename T > void chkmin(T &x, const T &y) { x = x < y ? x : y; }

const int N = 210;
const int M = N * N * 5;

int n, m;
int a[N][N];

namespace F { // max_flow
    const int inf = 0x3f3f3f3f;
    int h[N], now[N], d[N], cnt = 1, S, T;
    struct edge { int v, w, nxt; } e[M << 1];
    inline void tlink(int x, int y, int w) { e[++cnt] = (edge) { y, w, h[x] }; h[x] = cnt; }
    inline void link(int x, int y, int w) { tlink(x, y, w); tlink(y, x, 0); }
    inline void setst(int s, int t) { S = s; T = t; }
	void reset() { rep(i, 0, n + n + 1) h[i] = 0; cnt = 1; }
    queue < int > q;
    bool bfs() {
		while(q.size()) q.pop(); q.push(S); memset(d, 0, sizeof d); d[S] = 1; now[S] = h[S];
		while(!q.empty()) {
			int x = q.front(); q.pop();
			for(int i = h[x], y; i; i = e[i].nxt)
				if(e[i].w && !d[y = e[i].v]) {
					d[y] = d[x] + 1; q.push(y); now[y] = h[y];
					if(y == T) return 1;
				}
		} return 0;
    }
    int dinic(int x, int flow) {
		if(x == T) return flow;
		int res = flow;
		for(int i = now[x], y; i && res; i = e[i].nxt) {
			now[x] = i;
			if(e[i].w && d[y = e[i].v] == d[x] + 1) {
				int k = dinic(y, min(res, e[i].w));
				if(!k) d[y] = 0; e[i].w -= k; e[i ^ 1].w += k; res -= k;
			}
		}
		return flow - res;
    }
    ll runit() {
		ll maxflow = 0,flow;
		while(bfs()) while(flow = dinic(S, inf)) maxflow += flow;
		return maxflow;
    }
	int get(int x) {
		for(int i = h[x]; i; i = e[i].nxt)
			if(!e[i].w)	return e[i].v - n;
		return -1;
	}
}

int bel[N * N];

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in;
	rep(i, 1, n) rep(j, 1, m) a[i][j] = in;
	rep(i, 1, n) rep(j, 1, m) bel[(i - 1) * m + j] = i;
	rep(j, 1, m - 1) {
		F :: reset(); F :: setst(0, n + n + 1);
		rep(i, 1, n) {
			F :: link(0, i, 1);
			rep(k, j, m) F :: link(i, bel[a[i][k]] + n, 1);
		}
		rep(i, 1, n) F :: link(i + n, n + n + 1, 1);
		assert(F :: runit() == n);
		rep(i, 1, n) {
			int t = F :: get(i);
			rep(k, j, m) if(bel[a[i][k]] == t) { swap(a[i][j], a[i][k]); break; }
		}
	}
	rep(i, 1, n) { rep(j, 1, m) printf("%d ", a[i][j]); puts(""); }
	rep(j, 1, m) {
		vec pot; rep(i, 1, n) pot.eb(a[i][j]);
		sort(pot.begin(), pot.end());
		per(i, n, 1) a[i][j] = pot.back(), pot.pop_back();
	}
	rep(i, 1, n) { rep(j, 1, m) printf("%d ", a[i][j]); puts(""); }
	return 0;
}
