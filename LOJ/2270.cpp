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

int n, m, K, tot;
vector < tuple < int, int, int > > G[N], R[N];

namespace trie {
	vec G[N]; int fa[N], dfn[N], tim, st[21][N], dep[N], lg[N], pw[30];
	int tmn(int x, int y) { return dep[x] < dep[y] ? x : y; }
	void dfs(int x, int p) {
		fa[x] = p; dep[x] = dep[p] + 1; st[0][dfn[x] = ++tim] = x;
		for(auto y : G[x]) if(y ^ p) dfs(y, x), st[0][++tim] = x;
	}
	int lca(int x, int y) {
		if(dfn[x] > dfn[y]) swap(x, y); x = dfn[x], y = dfn[y]; int k = lg[y - x + 1];
		return tmn(st[k][x], st[k][y - pw[k] + 1]);
	}
	void init() {
		rep(i, 1, K) G[i].clear();
		rep(i, 1, K - 1) {
			int u = in, v = in; in;
			G[u].eb(v);
		} tim = 0; dfs(1, 0);
		rep(i, 2, tim) lg[i] = lg[i >> 1] + 1;
		pw[0] = 1; rep(i, 1, lg[tim]) pw[i] = pw[i - 1] << 1;
		rep(k, 1, 20) rep(i, 1, tim - pw[k] + 1) st[k][i] = tmn(st[k - 1][i], st[k - 1][i + pw[k - 1]]);
	}
}

using trie :: lca;
using trie :: dfn;

struct edge { int v, w, nxt; } e[N * 10];
int h[N], cnt, a[N], b[N], c[N], d[N];
int toid[N], outid[N];

void link(int x, int y, int w) { e[++cnt] = (edge) { y, w, h[x] }; h[x] = cnt; }

void solve() {
	n = in, m = in, K = in; rep(i, 1, tot) h[i] = 0; cnt = 0; tot = m + 1; 
	rep(i, 1, n) G[i].clear(), R[i].clear();
	rep(i, 1, m) a[i] = in, b[i] = in, c[i] = in, d[i] = in, G[a].eb(b, c, d), R[b].eb(a, c, d);
	trie :: init(); for(auto v : G[1]) link(m + 1, i, 0);
	rep(x, 1, n) {
		vector < int > pot;
		for(auto v : R[x]) {
			
		}
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
