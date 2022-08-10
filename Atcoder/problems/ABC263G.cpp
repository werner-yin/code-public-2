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
const int M = N * N * 2;

namespace F { // max_flow
    const int inf = 0x3f3f3f3f;
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

const int L = 2e7 + 10;

int n, a[L], b[L];
int pri[L], pnum;
bool vis[L];

void init(int l) {
	rep(i, 2, l) {
		if(!vis[i]) pri[++pnum] = i;
		rep(j, 1, pnum) {
			int t = pri[j] * i; if(t > l) break;
			vis[t] = true; if(i % pri[j] == 0) break;
		}
	} vis[1] = 1;
}

int main() {
#ifdef YJR_2333_TEST
    freopen("1.in","r",stdin);
#endif
	n = in; rep(i, 1, n) a[i] = in, b[i] = in;
	init(20000000);
	F :: setst(0, n + 1); int cnt1 = 0, id1 = 0;
	rep(i, 1, n)
		if(a[i] & 1) {
			if(a[i] != 1) F :: link(0, i, b[i]);
			else cnt1 = b[i], id1 = i;
		} else F :: link(i, n + 1, b[i]);
	rep(i, 1, n) if(a[i] & 1) rep(j, 1, n) if(~a[j] & 1 && !vis[a[i] + a[j]]) F :: link(i, j, F :: inf);
	ll ans1 = F :: runit();
	if(id1) F :: link(0, id1, cnt1);
	ll ans2 = F :: runit();
	cerr << ans1 << " " << ans2 << endl;
	ll ans = ans1 + ans2 + (cnt1 - ans2) / 2;
	cout << ans << endl;
	return 0;
}
