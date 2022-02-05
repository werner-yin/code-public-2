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

const int N = 1e5 + 10;
const int inf = 0x3f3f3f3f;

int n, m, dfn[N], stk[N], top, dep[N], fa[20][N], mnp[N], mna[N], f[N], sf[N], tot, s[N];
vec G[N];
bool vis[N];

void dfs(int x, int p) {
	dfn[x] = ++tot; dep[x] = dep[p] + 1; fa[0][x] = p; mnp[x] = mna[x] = inf;
	rep(i, 1, 19) fa[i][x] = fa[i - 1][fa[i - 1][x]];
	sort(G[x].begin(), G[x].end()); G[x].resize(unique(G[x].begin(), G[x].end()) - G[x].begin());
	for(auto y : G[x])
		if(!dep[y]) dfs(y, x), chkmin(mna[x], mna[y]);
		else if(dep[y] < dep[x]) chkmin(mnp[x], dep[y]);
	chkmin(mna[x], mnp[x]); f[x] = mna[x] >= dep[p]; sf[x] = f[x]; 
}

void rdfs(int x, int p) {
	sf[x] += sf[p]; 
	for(auto y : G[x]) if(dep[y] == dep[x] + 1) rdfs(y, x);
}

int lca(int x, int y) {
	if(dep[x] < dep[y]) swap(x, y);
	per(i, 19, 0) if(dep[fa[i][x]] >= dep[y]) x = fa[i][x];
	if(x == y) return x;
	per(i, 19, 0) if(fa[i][x] != fa[i][y]) x = fa[i][x], y = fa[i][y];
	return fa[0][x];
}

int getnear(int x, int p) {
	per(i, 19, 0) if(dep[fa[i][x]] > dep[p]) x = fa[i][x];
	return x;
}

int ans;

void vdfs(int x) {
	bool fl = 0;
	for(auto y : G[x]) {
		int v = getnear(y, x);
		if(x != 1 || (vis[x] || G[x].size() > 1)) ans += sf[y] - sf[v];
		fl |= mna[v] >= dep[x];
		vdfs(y);
	} if(!vis[x] && (x != 1 || G[x].size() > 1)) ans += fl;
}

void cdfs(int x) {
	for(auto y : G[x]) cdfs(y);
	G[x].clear();
}

void solve() {
	n = in, m = in, tot = 0; rep(i, 1, n) G[i].clear(), sf[i] = f[i] = dep[i] = 0;
	rep(i, 1, m) { int u = in, v = in; G[u].eb(v); G[v].eb(u); }
	dfs(1, 0); rdfs(1, 0); rep(i, 1, n) G[i].clear();
	int q = in;
	rep(_, 1, q) {
		int t = in; rep(i, 1, t) s[i] = in; ans = 0;
		sort(s + 1, s + t + 1, [](auto a, auto b) { return dfn[a] < dfn[b]; });
		stk[top = 1] = 1;
		rep(i, 1, t) {
			if(s[i] == 1) continue;
			int L = lca(s[i], stk[top]); 
			while(top > 1 && dep[L] <= dep[stk[top - 1]]) G[stk[top - 1]].eb(stk[top]), top--;
			if(L != stk[top]) G[L].eb(stk[top]), stk[top] = L;
			stk[++top] = s[i];
		} rep(i, 2, top) G[stk[i - 1]].eb(stk[i]);
		rep(i, 1, t) vis[s[i]] = true;
		vdfs(1); printf("%d\n", ans); cdfs(1);
		rep(i, 1, t) vis[s[i]] = false;
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("01.in", "r", stdin);
#endif
	for(int T = in; T; T--) solve();
	return 0;
}
