// this code is written with microsoft notepad, so maybe CE many times.

#include <bits/stdc++.h>

#define rep(i, x, y) for(int i = (x); i <= (y); i++)
#define per(i, x, y) for(int i = (x); i >= (y); i--)

using namespace std;

const int N = 2e5 + 10;

using ll = long long;

int n;
vector < int > G[N];

int fa[N], siz[N], top[N], dfn[N], tim, dep[N], son[N], ind[N], idp[N];

ll f[N], a[N];

ll tval[N];
bool leaf[N];

void dfs(int x, int p) {
	dep[x] = dep[p] + 1; siz[x] = 1; fa[x] = p; leaf[x] = true;
	for(auto y : G[x]) if(y ^ p) {
		leaf[x] = false, dfs(y, x), siz[x] += siz[y]; son[x] = siz[y] > siz[son[x]] ? y : son[x], f[x] += f[y];
	} if(leaf[x]) f[x] = a[x]; f[x] = min(f[x], a[x]);
}

void dfs1(int x, int anc) {
	top[x] = anc; idp[x] = x; dfn[x] = ++tim; ind[tim] = x; if(son[x]) dfs1(son[x], anc), idp[x] = idp[son[x]];
	for(auto y : G[x]) if(y ^ son[x] && y ^ fa[x]) dfs1(y, y), tval[x] += f[y];
}

struct node {
	ll x, y;
	node(ll x = 0, ll y = 0) : x(x), y(y) { } 
	friend node operator + (node a, node b) {
		return node(a.x + b.x, min(b.y, b.x + a.y));
	}
}; 

namespace seg {
	node val[N << 2];
	void pu(int o) { val[o] = val[o << 1 | 1] + val[o << 1]; }
	void init(int o, int pos) {
		val[o].x = tval[pos], val[o].y = a[pos];
		if(leaf[pos]) val[o].x = a[pos];
	}
	void upd(int pos, int o = 1, int l = 1, int r = n) {
		if(l == r) return init(o, ind[l]); int mid = l + r >> 1; 
		pos <= mid ? upd(pos, o << 1, l, mid) : upd(pos, o << 1 | 1, mid + 1, r); pu(o);
	}
	node query(int xl, int xr, int o = 1, int l = 1, int r = n) {
		if(xl == l && xr == r) return val[o]; int mid = l + r >> 1;
		if(xr <= mid) return query(xl, xr, o << 1, l, mid); if(xl > mid) return query(xl, xr, o << 1 | 1, mid + 1, r);
		else return query(mid + 1, xr, o << 1 | 1, mid + 1, r) + query(xl, mid, o << 1, l, mid);
	}
	void build(int o = 1, int l = 1, int r = n) {
		if(l == r) return init(o, ind[l]); int mid = l + r >> 1;
		build(o << 1, l, mid), build(o << 1 | 1, mid + 1, r); pu(o);
	}
} 

ll getf(int x) {
	node ret = seg :: query(dfn[x], dfn[idp[x]]);
	return min(ret.x, ret.y);
}

void modify(int x, int v) {
	ll odp = getf(top[x]);
	a[x] += v; seg :: upd(dfn[x]);
	while(x > 1) {
		ll ndp = getf(top[x]);
		if(top[x] == 1) break;
		tval[fa[top[x]]] += ndp - odp; odp = getf(top[fa[top[x]]]);
		seg :: upd(dfn[fa[top[x]]]); x = fa[top[x]];
	}
}

int main() {
	scanf("%d", &n); rep(i, 1, n) scanf("%d", &a[i]);
	rep(i, 2, n) {
		int x, y; scanf("%d %d", &x, &y);
		G[x].emplace_back(y), G[y].emplace_back(x);
	}
	dfs(1, 0); dfs1(1, 1); seg :: build();
	int q; scanf("%d", &q);
	while(q--) {
		auto getal = [&]() {
			char ch = getchar(); while(!isalpha(ch)) ch = getchar();
			return ch;
		};
		char op = getal(); int x, y; scanf("%d", &x);
		if(op == 'Q') printf("%lld\n", getf(x));
		else scanf("%d", &y), modify(x, y);
	}
}