#include <bits/stdc++.h>

#define eb emplace_back
#define ep emplace
#define fi first
#define se second
#define in read<int>()
#define rep(i, x, y) for(int i = (x); i <= (y); i++)
#define per(i, x, y) for(int i = (x); i >= (y); i--)

using namespace std;

using ll = long long;
using vec = vector < int >;

template < typename T > T read() {
	T x = 0; bool f = 0; char ch = getchar();
	while(!isdigit(ch)) f |= ch == '-', ch = getchar();
	while(isdigit(ch)) x = x * 10 + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}

template < typename T > void chkmin(T &x, const T &y) { x = x < y ? x : y; }

const int N = 1e6 + 10;

int n, m, K, tot;
vec G[N], R[N];

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
int h[N], cnt, a[N], b[N], c[N], d[N], stk[N], top, dep[N];
int toid[N], outid[N], ps[N], ss[N];
vec tG[N];
bool vis[N];
ll dis[N], ans[N];

void link(int x, int y, int w) { e[++cnt] = (edge) { y, w, h[x] }; h[x] = cnt; }

void dfs(int x) {
	toid[x] = ++tot; outid[x] = ++tot;
	for(auto y : tG[x]) dfs(y);
	top = 0; for(auto y : tG[x]) stk[++top] = y; // stk is not using
	rep(i, 1, top) {
		if(i == 1) ps[i] = toid[stk[i]];
		else ps[i] = ++tot, link(ps[i], ps[i - 1], 0), link(ps[i], toid[stk[i]], 0);
	}
	per(i, top, 1) {
		if(i == top) ss[i] = toid[stk[i]];
		else ss[i] = ++tot, link(ss[i], ss[i + 1], 0), link(ss[i], toid[stk[i]], 0);
	}
	rep(i, 1, top) {
		if(i > 1) link(outid[stk[i]], ps[i - 1], dep[x]);
		if(i < top) link(outid[stk[i]], ss[i + 1], dep[x]);
		link(outid[stk[i]], outid[x], 0); link(toid[x], toid[stk[i]], 0);
	}
}

void clr(int x) {
	for(auto y : tG[x]) dfs(y);
	tG[x].clear(); toid[x] = outid[x] = 0;
}

void dijk(int S) {
	memset(dis, 0x3f, sizeof dis); memset(vis, 0, sizeof vis);
	priority_queue < pair < ll, int >, vector < pair < ll, int > >, greater < pair < ll, int > > > q; q.ep(dis[S] = 0, S);
	while(q.size()) {
		int x = q.top().se; q.pop(); if(vis[x]) continue; vis[x] = true;
		for(int i = h[x], y = e[i].v; i; i = e[i].nxt, y = e[i].v)
			if(dis[y] > dis[x] + e[i].w) dis[y] = dis[x] + e[i].w, q.ep(dis[y], y);
	}
}

void solve() {
	n = in, m = in, K = in; rep(i, 1, tot) h[i] = 0; cnt = 0; tot = m + 1; 
	rep(i, 1, n) G[i].clear(), R[i].clear();
	rep(i, 1, m) a[i] = in, b[i] = in, c[i] = in, d[i] = in, G[a[i]].eb(i), R[b[i]].eb(i);
	trie :: init(); for(auto v : G[1]) link(m + 1, v, c[v]);
	rep(x, 1, n) {
		vector < int > pot;
		for(auto v : R[x]) pot.eb(d[v]);
		for(auto v : G[x]) pot.eb(d[v]);
		sort(pot.begin(), pot.end(), [](auto x, auto y) { return dfn[x] < dfn[y]; });
		pot.resize(unique(pot.begin(), pot.end()) - pot.begin()); stk[top = 1] = 1;
		for(auto y : pot) {
			if(y == 1) continue; int l = lca(y, stk[top]);
			while(dep[l] <= dep[stk[top - 1]]) tG[stk[top - 1]].eb(stk[top]), top--;
			if(l != stk[top]) tG[l].eb(stk[top]), stk[top] = l;
			stk[++top] = y;
		} rep(i, 2, top) tG[stk[i - 1]].eb(stk[i]);
		dfs(1);
		for(auto v : R[x]) link(v, outid[d[v]], c[v]), link(v, outid[d[v]], c[v] + dep[d[v]]);
		for(auto v : G[x]) link(toid[d[v]], v, c[v]), link(outid[d[v]], v, c[v] + dep[d[v]]);
		clr(1);
	} dijk(m + 1); memset(ans, 0x3f, sizeof ans);
	rep(i, 1, m) chkmin(ans[b[i]], (dis[i] + c[i]) / 2);
	rep(i, 2, n) printf("%lld\n", ans[i]);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
