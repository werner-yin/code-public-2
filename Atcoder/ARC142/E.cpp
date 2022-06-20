#include <bits/stdc++.h>

#define in read()
#define fi first
#define se second
#define eb emplace_back
#define rep(i, x, y) for(int i = (x); i <= (y); i++)
#define per(i, x, y) for(int i = (x); i >= (y); i--)

using namespace std;

typedef long long ll;
typedef double db;
typedef vector < int > vec;
typedef pair < int , int > pii;

template < typename T > void chkmax(T &x, const T &y) { x = x < y ? y : x; }

int read() {
	int x = 0; bool f = 0; char ch = getchar(); while(!isdigit(ch)) f |= ch == '-',ch = getchar();
	while(isdigit(ch)) x = x * 10 + (ch ^ 48),ch = getchar(); return f ? -x : x;
}

const int inf = 0x3f3f3f3f;
const int N = 110;

namespace F { // max_flow
	const int N = 2e4;
	const int M = N * 20;
    int h[N], now[N], d[N], cnt = 1, S, T;
    struct edge { int v, w, nxt; } e[M << 1];
    inline void tlink(int x, int y, int w) { e[++cnt] = (edge) { y, w, h[x] }; h[x] = cnt; }
    inline void link(int x, int y, int w) { tlink(x, y, w); tlink(y, x, 0); }
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

int n, m, a[N], b[N], ans, mn[N];
vec G[N];
bool bx[N];

int main() {
#ifdef YJR_2333_TEST
    freopen("1.in","r",stdin);
#endif
	n = in; rep(i, 1, n) a[i] = in, b[i] = in;
	m = in;
	rep(i, 1, m) { int x = in, y = in; G[x].eb(y), G[y].eb(x); chkmax(mn[x], min(b[x], b[y])), chkmax(mn[y], min(b[x], b[y])); }
	rep(x, 1, n) if(a[x] < mn[x]) ans += mn[x] - a[x], a[x] = mn[x];
	rep(x, 1, n) if(a[x] < b[x]) bx[x] = true;
	F :: setst(0, n * 101 + 1);
	rep(x, 1, n)
		if(bx[x]) {
			F :: link(0, x, b[x] - a[x]);
			for(auto y : G[x])
				if(!bx[y] && b[x] - a[y] > 0)
					F :: link(x, n + 100 * (y - 1) + (b[x] - a[y]), inf);
		} else
			rep(j, 1, 100) {
				F :: link(n + 100 * (x - 1) + j, F :: T, 1);
				if(j > 1)
					F :: link(n + 100 * (x - 1) + j, n + 100 * (x - 1) + j - 1, inf);
			}
	cout << F :: runit() + ans << endl;
	return 0;
}
