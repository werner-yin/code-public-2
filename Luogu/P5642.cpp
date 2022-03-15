#include <bits/stdc++.h>

#define eb emplace_back
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

template < typename T > void chkmax(T &x, const T &y) { x = x > y ? x : y; }

const int N = 1e6 + 10;
const int mod = 998244353;

int n, m;
int fa[N], siz[N], son[N], top[N], dep[N], tim, dfn[N], R[N], ind[N];
ll f[N], g[N], c[N], h[N], pc[N];
vec G[N];
vector < tuple < int, int, int > > vpot[N];

void dfs(int x, int p) {
	fa[x] = p; siz[x] = 1; dep[x] = dep[p] + 1;
	for(auto y : G[x]) if(y ^ p) dfs(y, x), siz[x] += siz[y], son[x] = siz[y] > siz[son[x]] ? y : son[x];
}

void dfs1(int x, int anc) {
	top[x] = anc; ind[dfn[x] = ++tim] = x; if(son[x]) dfs1(son[x], anc);
	for(auto y : G[x]) if(y ^ fa[x] && y ^ son[x]) dfs1(y, y); R[x] = tim;
}

int lca(int x, int y) {
	while(top[x] ^ top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		x = fa[top[x]];
	} return dep[x] < dep[y] ? x : y;
}

struct {
	ll tr[N];
	void add(int x, ll v) { for(; x <= n; x += x & -x) tr[x] += v; }
	ll query(int x) { ll res = 0; for(; x; x -= x & -x) res += tr[x]; return res; }
} T;
	
void DP(int x, int p) {
	for(auto y : G[x])
		if(y ^ p)
			DP(y, x), g[x] += f[y];
	f[x] = g[x];
	for(auto v : vpot[x]) {
		int a, b, w; tie(a, b, w) = v;
		chkmax(f[x], g[x] + T.query(dfn[a]) + T.query(dfn[b]) + w);
	} c[x] = g[x] - f[x]; T.add(dfn[x], c[x]); T.add(R[x] + 1, -c[x]);
}

vector < tuple < ll, int, int > > tvpot[N];

const ll inf = 0xcfcfcfcfcfcfcfcf;

namespace seg {
	ll val[N << 2], tg[N << 2];
	void pu(int o) { val[o] = max(val[o << 1], val[o << 1 | 1]); }
	void pt(int o, ll v) { chkmax(val[o], v), chkmax(tg[o], v); }
	void pd(int o) { if(tg[o] != inf) pt(o << 1, tg[o]), pt(o << 1 | 1, tg[o]), tg[o] = inf; }
	void init() { memset(val, 0xcf, sizeof val); memset(tg, 0xcf, sizeof tg); }
	void upd(int xl, int xr, ll v, int o = 1, int l = 1, int r = n) {
		if(xl <= l && r <= xr) return pt(o, v); int mid = l + r >> 1; pd(o);
		if(xl <= mid) upd(xl, xr, v, o << 1, l, mid); if(xr > mid) upd(xl, xr, v, o << 1 | 1, mid + 1, r);
		pu(o);
	}
	ll query(int pos, int o = 1, int l = 1, int r = n) {
		if(l == r) return val[o]; int mid = l + r >> 1; pd(o);
		if(pos <= mid) return query(pos, o << 1, l, mid); else return query(pos, o << 1 | 1, mid + 1, r);
	}
	void modify(int x, int p, ll v) {
		int lst = 0;
		while(top[x] ^ top[p]) {
			if(dfn[top[x]] < dfn[x]) upd(dfn[top[x]], dfn[x] - 1, v);
			tvpot[x].eb(v, lst, 0);	lst = top[x]; x = fa[top[x]];
		}
		tvpot[x].eb(v, lst, 0); if(dfn[p] < dfn[x]) upd(dfn[p], dfn[x] - 1, v); 
	}
}

int jump(int x, int p) {
	int lst = 0;
	while(top[x] ^ top[p]) lst = top[x], x = fa[top[x]];
	return x == p ? lst : ind[dfn[p] + 1];
}

void DPH(int x, int p) {
	for(auto y : G[x]) if(y ^ p) h[y] = h[x] + c[x];
	for(auto v : vpot[x]) {
		int a, b, w; tie(a, b, w) = v;
		if(a == x && b == x) tvpot[x].eb(h[x] + c[x] + w, 0, 0);
		else if(a == x || b == x) a = a ^ b ^ x, seg :: modify(a, x, h[x] + pc[a] - pc[fa[x]] + w);
		else {
			int na = jump(a, x), nb = jump(b, x); ll val = h[x] + pc[a] - pc[x] + pc[b] - pc[fa[x]] + w;
			tvpot[x].eb(val, na, nb); seg :: modify(a, na, val); seg :: modify(b, nb, val);
		}
	}
	tvpot[x].eb(seg :: query(dfn[x]), son[x], 0); sort(tvpot[x].begin(), tvpot[x].end());
	for(auto y : G[x]) if(y ^ p) {
			vector < tuple < ll, int, int > > amp;
			while(tvpot[x].size() && (get<1>(tvpot[x].back()) == y || get<2>(tvpot[x].back()) == y)) amp.eb(tvpot[x].back()), tvpot[x].pop_back();
			if(tvpot[x].size()) chkmax(h[y], get<0>(tvpot[x].back()));
			while(amp.size()) tvpot[x].eb(amp.back()), amp.pop_back();
		}
	for(auto y : G[x]) if(y ^ p) DPH(y, x);
}

void DPC(int x, int p) { pc[x] = pc[p] + c[x]; for(auto y : G[x]) if(y ^ p) DPC(y, x); }

ll ans = 0;

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in;
	rep(i, 2, n) { int u = in, v = in; G[u].eb(v), G[v].eb(u); }
	dfs(1, 0); dfs1(1, 1);
	rep(i, 1, m) { int s = in, t = in, z = in, l = lca(s, t); vpot[l].eb(s, t, z); }
	DP(1, 0); h[1] = f[1]; seg :: init(); DPC(1, 0); DPH(1, 0);
	ans = f[1] % mod * n % mod * n % mod; ans = (ans + mod) % mod;
	rep(i, 1, n) {
		ll res = 1ll * siz[i] * siz[i];
		for(auto y : G[i]) if(y ^ fa[i]) res -= 1ll * siz[y] * siz[y];
		res %= mod;	(ans -= 1ll * h[i] % mod * res % mod) %= mod; ans = (ans - 1ll * c[i] % mod * res % mod) % mod; ans = (ans + mod) % mod;
	} 
	rep(i, 1, n) ans -= 2ll * c[i] % mod * siz[i] % mod * (n - siz[i]) % mod, ans = (ans % mod + mod) % mod;
	cout << ans << endl;
	return 0;
}
