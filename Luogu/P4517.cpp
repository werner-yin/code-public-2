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

const int N = 410;
const int mod = 1e9 + 7;
const int inv2 = (mod + 1) >> 1;

int n, m;
struct edge { int v, nxt; } e[N << 1];
int h[N], cnt = 1, vis[N << 1], fa[N], to[N];
void link(int x, int y) { e[++cnt] = (edge) { y, h[x] }; h[x] = cnt; }

int stk[N], top, ans, s[N], f[N], g[N], sg[N], siz[N], pw[N], dep[N];
veg pot;

void getchain(int x, int lst) {
	stk[top = 1] = x;
	while(x != lst) vis[to[x]] = vis[to[x] ^ 1] = true, x = fa[x], stk[++top] = x;
}

void dfs(int x, int p) {
	int lst = 0; fa[x] = p; siz[x] = 1; dep[x] = dep[p] + 1;
	for(int i = h[x], y = e[i].v; i; i = e[i].nxt, y = e[i].v) if(y ^ p && !vis[i]) {
			if(siz[y]) { if(dep[x] > dep[y]) getchain(x, lst = y); }
			else to[y] = i, dfs(y, x), siz[x] += siz[y];
	}
	for(int i = h[x], y = e[i].v; i; i = e[i].nxt, y = e[i].v)
		if(dep[x] == dep[y] - 1 && !vis[i]) ans = (ans + 1ll * (pw[siz[y]] - 1) * (pw[n - siz[y]] - 1) % mod) % mod;
	if(lst) pot.eb(x, lst);
}

void solve(int x, int lst) {
	getchain(x, lst); per(i, top, 1) s[i] = siz[stk[i]] - siz[stk[i - 1]];
	s[top] += n - siz[stk[top]]; rep(len, 0, top) f[len] = 0;
	rep(len, 1, top)
		rep(l, 1, len) {
		rep(i, 1, top) g[i] = sg[i] = 0;
		g[l] = sg[l] = pw[s[l]] - 1;
		rep(i, l + 1, top) {
			g[i] = 1ll * (pw[s[i]] - 1) * (sg[i - 1] - sg[max(i - len - 1, l - 1)] + mod) % mod;
			sg[i] = (sg[i - 1] + g[i]) % mod;
		}
		f[len] = (f[len] + (sg[top] - sg[max(l, top - len + l - 1)] + mod) % mod) % mod;
	} rep(len, 1, top) ans = (ans + 1ll * (top - len) * (f[len] - f[len - 1] + mod) % mod) % mod;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in;
	rep(i, 1, m) {
		int u = in, v = in;
		link(u, v); link(v, u);
	} pw[0] = 1; rep(i, 1, n) pw[i] = pw[i - 1] * 2ll % mod;
	dfs(1, 0); for(auto v : pot) solve(v.fi, v.se);
	rep(i, 1, n) ans = 1ll * ans * inv2 % mod; printf("%d\n", ans);
	return 0;
}
