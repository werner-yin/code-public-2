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

const int N = 1e6 + 10;

int n, m, ind[N], a[N];

namespace F { // max_flow
	const int N = 2e5 + 10;
	const int M = 2e6 + 10;
    const int inf = 0x3f3f3f3f;
    int h[N], now[N], d[N], cnt = 1, S, T;
    struct edge { int v, w, nxt; } e[M << 1];
	void reset() { rep(i, 0, (n << 2) + 1) h[i] = 0; cnt = 1; }
    inline void tlink(int x, int y, int w) { e[++cnt] = (edge) { y, w, h[x] }; h[x] = cnt; }
    inline void link(int x, int y, int w) { tlink(x, y, w); tlink(y, x, 0); }
    inline void setst(int s, int t) { S = s; T = t; }
    queue < int > q;
    bool bfs() {
		while(q.size()) q.pop(); q.push(S); rep(i, 0, (n << 2) + 1) d[i] = 0; d[S] = 1; now[S] = h[S];
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
}

int id(int x, int t) { return n * t + x; } // 0 : 入态，1 : 出态。

void solve() {
	n = in; rep(i, 1, n) ind[a[i] = in] = i;
	F :: setst(0, n * 4 + 1);
	rep(i, 1, n) {
		int x = a[i];
		for(int j = x + x; j <= 50000; j += x) if(ind[j]) {
				int u = i, v = ind[j];
				rep(a, 0, 1) rep(b, 0, 1) if(a != 1 || b != 0) F :: link(id(u, a), id(v, b + 2), 1);
		}
	}
	rep(i, 1, n)
		F :: link(F :: S, id(i, 0), 1), F :: link(F :: S, id(i, 1), 1),
		F :: link(id(i, 2), F :: T, 1), F :: link(id(i, 3), F :: T, 1),
		F :: link(id(i, 0), id(i, 3), 1);
	int ans = F :: runit() - n; printf("%d\n", ans);
}

void clr() { F :: reset(); rep(i, 1, n) ind[a[i]] = 0; }

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve(), clr();
	return 0;
}
