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

namespace F { // max_flow
	const int N = 2e5 + 10;
	const int M = 1e6 + 10;
    const int inf = 0x3f3f3f3f;
    int h[N], now[N], d[N], cnt = 1, S, T;
    struct edge { int v, w, nxt; } e[M << 1];
    inline void tlink(int x, int y, int w) { e[++cnt] = (edge) { y, w, h[x] }; h[x] = cnt; }
    inline void link(int x, int y, int w, int tw = 0) { tlink(x, y, w); tlink(y, x, tw); }
    inline void setst(int s, int t) { S = s; T = t; }
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
}

int n, p[N], q[N], bp[N], bq[N], ans;

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) p[i] = in + 1; rep(i, 1, n) q[i] = in + 1;
	rep(i, 1, n) {
		for(int x = i; !bp[x]; x = p[x]) bp[x] = i;
		for(int x = i; !bq[x]; x = q[x]) bq[x] = i;
	} rep(i, 1, n) bq[i] += n; ans = n; F :: setst(0, n + n + 1);
	rep(i, 1, n) {
		if(p[i] != i && q[i] != i) {
			if(p[i] != q[i]) F :: link(bq[i], bp[i], 1, 0);
			else F :: link(bq[i], bp[i], 1, 1);
		} else if(p[i] != i || q[i] != i) {
			if(p[i] == i) F :: link(bq[i], n + n + 1, 1, 0);
			else F :: link(0, bp[i], 1, 0);
		} else ans--;
	} cout << ans - F :: runit() << endl;
	return 0;
}
