#include <bits/stdc++.h>

#define eb emplace_back
#define fi first
#define se second
#define in read<int>()
#define rep(i, x, y) for(int i = (x); i <= (y); i++)
#define per(i, x, y) for(int i = (x); i >= (y); i--)

using namespace std;

using ll = long long;
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
const int TN = N * 10;
const int S = 1 << 13;
const int mod = 998244353;

int *g[N][2], tvpot[TN], *cur = tvpot;
int f[N][2], n, m, U;
vec bel[N], hav[N], G[N];
veg ed;

struct DSU {
	int fa[N];
	void reset() { rep(i, 1, n) fa[i] = i; }
	int gf(int x) { return fa[x] == x ? x : fa[x] = gf(fa[x]); }
} D;

int tmp[S + 10];

int wk[N][2][2], fa[N];

void calc(int y, int x) {
	wk[y][0][0] = wk[y][1][1] = 1; wk[y][0][1] = wk[y][1][0] = 0;
	while(y != x) {
		int p = fa[y];
		wk[p][0][0] = wk[p][0][1] = wk[p][1][0] = wk[p][1][1] = 1;
		if(p != x) {
			for(auto t : G[p])
				if(t ^ fa[p] && t != y)
					rep(cury, 0, 1) {
						wk[p][cury][0] = 1ll * wk[p][cury][0] * (f[t][0] + f[t][1]) % mod;
						wk[p][cury][1] = 1ll * wk[p][cury][1] * f[t][0] % mod;
					}	
		}
		rep(cury, 0, 1) {
			wk[p][cury][0] = 1ll * wk[p][cury][0] * (wk[y][cury][0] + wk[y][cury][1]) % mod;
			wk[p][cury][1] = 1ll * wk[p][cury][1] * wk[y][cury][0] % mod;
		}
		y = p;
	}
}

void clear() { rep(i, 0, U) tmp[i] = 0; }

void merge(int *f, int *g, int pw) {
	rep(s, 0, U) if(f[s]) {
		for(int tv = U ^ s, t = tv; ; t = (t - 1) & tv) {
			if(g[t]) tmp[s | t] = (tmp[s | t] + 1ll * f[s] * g[t] % mod * pw % mod) % mod;
			if(t == 0) break;
		}
	}
}

void dfs(int x, int p) {
	f[x][0] = f[x][1] = 1; fa[x] = p;
	for(auto y : G[x]) if(y ^ p) {
			dfs(y, x); for(auto v : hav[y]) hav[x].eb(v);
			if(hav[y].size()) assert(hav[y].size() == 1);
			f[x][0] = 1ll * f[x][0] * (f[y][0] + f[y][1]) % mod;
			f[x][1] = 1ll * f[x][1] * f[y][0] % mod;
		}
	if(hav[x].size() <= 1 && !bel[x].size() && p) return; // 1 is in the virtual tree
	g[x][0] = cur; cur += U + 2; g[x][1] = cur; cur += U + 2;
	if(!hav[x].size()) {
		int stu = 0; for(auto v : bel[x]) stu |= 1 << v;
		g[x][0][0] = f[x][0]; g[x][1][stu] = f[x][1];
		hav[x].eb(x); return;
	} // bottom
	if(hav[x].size()) {
		int stu = 0; for(auto v : bel[x]) stu |= 1 << v;
		g[x][0][0] = g[x][1][stu] = 1;
		for(auto y : G[x]) {
			if(y ^ p && !hav[y].size()) {
				g[x][0][0] = 1ll * g[x][0][0] * (f[y][0] + f[y][1]) % mod;
				g[x][1][stu] = 1ll * g[x][1][stu] * f[y][0] % mod;
			}
		}
		for(auto y : hav[x]) {
			calc(y, x);
			clear(); merge(g[x][0], g[y][0], wk[x][0][0]); merge(g[x][0], g[y][1], wk[x][1][0]); rep(i, 0, U) g[x][0][i] = tmp[i];
			clear(); merge(g[x][1], g[y][0], wk[x][0][1]); merge(g[x][1], g[y][1], wk[x][1][1]); rep(i, 0, U) g[x][1][i] = tmp[i];
		}
		hav[x].clear(); hav[x].eb(x);
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("duliu.in", "r", stdin); freopen("P4426.out", "w", stdout);
#endif
	n = in, m = in; D.reset();
	rep(i, 1, m) {
		int u = in, v = in;
		if(D.gf(u) == D.gf(v)) ed.eb(u, v);
		else G[u].eb(v), G[v].eb(u), D.fa[D.gf(u)] = D.gf(v);
	}
	rep(i, 0, int(ed.size()) - 1) bel[ed[i].fi].eb(i), bel[ed[i].se].eb(i);
	U = 1 << ed.size(); U--;
	dfs(1, 0); int ans = 0; rep(i, 0, U) ans = (ans + g[1][0][i]) % mod, ans = (ans + g[1][1][i]) % mod; printf("%d\n", ans);
	return 0;
}
