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

const int N = 3e5 + 10;

int n, m, p, u[N], v[N], w[N], id[N], dep[N], fa[N];
veg ban[N];
ll ans;

struct dsu {
	int fa[N];
	void reset() { rep(i, 1, n) fa[i] = i; }
	int gf(int x) { return fa[x] == x ? x : fa[x] = gf(fa[x]); }
	bool merge(int x, int y) { x = gf(x), y = gf(y); if(x == y) return 0; fa[x] = y; return 1; }
} d1, d2;

bool check(int u, int v, int lim) {
	while(u != v && lim--) {
		if(dep[u] < dep[v]) swap(u, v);
		u = fa[u];
	} return u != v;
}

vec get(int u, int v) {
	vec pot;
	while(u != v) {
		if(dep[u] < dep[v]) swap(u, v);
		pot.eb(u); u = fa[u];
	} pot.eb(u); return pot;
}

vec G[N];
bool vis[N];

void solve(int u, int v, int w, veg &ban) {
	if(check(u, v, ban.size())) {
		int tu = u; u = d2.gf(u), v = d2.gf(v);
		while(u != v) {
			if(dep[u] < dep[v]) swap(u, v);
			ans += w * d1.merge(u, fa[u]); d2.merge(u, fa[u]); u = d2.gf(u);
		} ans += w * d1.merge(u, tu); return;
	}
	vec pot = get(u, v);
	for(auto v : pot) G[v].clear();
	for(auto v : ban) G[v.fi].eb(v.se), G[v.se].eb(v.fi);
	int p = pot.front(); for(auto x : pot) if(G[x].size() < G[p].size()) p = x;
	for(auto x : G[p]) vis[x] = 1; vec a, b;
	for(auto x : pot) if(vis[x]) a.eb(x), vis[x] = 0; else b.eb(x);
	for(auto x : b) ans += w * d1.merge(x, p);
	for(auto x : a) {
		for(auto y : G[x]) vis[y] = true;
		for(auto y : a) if(!vis[y]) ans += w * d1.merge(x, y);
		for(auto y : G[x]) vis[y] = false;
	}
	for(auto x : a) {
		for(auto y : G[x]) vis[y] = true;
		for(auto y : b) if(!vis[y]) { ans += w * d1.merge(p, x); break; }
		for(auto y : G[x]) vis[y] = false;
	}
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in, p = in;
	dep[1] = 1; rep(i, 2, n) fa[i] = in, dep[i] = dep[fa[i]] + 1;
	rep(i, 1, m) u[i] = in, v[i] = in, w[i] = in, id[i] = i;
	rep(i, 1, p) { int t = in, a = in, b = in; ban[t].eb(a, b); }
	sort(id + 1, id + m + 1, [&](int x, int y) { return w[x] < w[y]; });
	d1.reset(), d2.reset(); rep(i, 1, m) solve(u[id[i]], v[id[i]], w[id[i]], ban[id[i]]);
	cout << ans << endl; return 0;
}
