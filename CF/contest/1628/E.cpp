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

const int N = 6e5 + 10;

int n, Q, fa[N], tot, wval[N], stk[N << 1], dfn[N], top, dep[N];
tuple < int, int, int > ed[N];
vec G[N];

int gf(int x) { return fa[x] == x ? x : fa[x] = gf(fa[x]); }

void dfs(int x) {
	stk[dfn[x] = ++top] = x;
	for(auto y : G[x])
		dep[y] = dep[x] + 1, dfs(y), stk[++top] = x; 
}

namespace L { 
	int lg[N << 1], pw[50], mn[23][N << 1];
	int tmn(int x, int y) { return dep[x] < dep[y] ? x : y; }
	int LCA(int x, int y) {
		if(x == 0) return y; if(y == 0) return x;
		x = dfn[x], y = dfn[y]; if(x > y) swap(x, y);
		int k = lg[y - x + 1]; return tmn(mn[k][x], mn[k][y - pw[k] + 1]);
	}
	void init() {
		rep(i, 2, top) lg[i] = lg[i >> 1] + 1;
		pw[0] = 1; rep(i, 1, lg[top]) pw[i] = pw[i - 1] << 1;
		rep(i, 1, top) mn[0][i] = stk[i];
		rep(j, 1, lg[top])
			rep(i, 1, top - pw[j] + 1)
			mn[j][i] = tmn(mn[j - 1][i], mn[j - 1][i + pw[j - 1]]);
	}
}

int val[N << 2], tval[N << 2], tg[N << 2];

void pt(int o, int v) { tg[o] = v; if(v == 0) val[o] = 0; else val[o] = tval[o]; }
void pd(int o) {
	if(tg[o] != -1) {
		pt(o << 1, tg[o]); pt(o << 1 | 1, tg[o]);
		tg[o] = -1;
	}
}

void build(int o = 1, int l = 1, int r = n) {
	tg[o] = -1; if(l == r) return val[o] = 0, tval[o] = l, void(); int mid = l + r >> 1;
	build(o << 1, l, mid); build(o << 1 | 1, mid + 1, r);
	tval[o] = L :: LCA(tval[o << 1], tval[o << 1 | 1]); val[o] = L :: LCA(val[o << 1], val[o << 1 | 1]);
}

void upd(int xl, int xr, int v, int o = 1, int l = 1, int r = n) {
	if(xl == l && xr == r) return pt(o, v); int mid = l + r >> 1; pd(o);
	if(xr <= mid) upd(xl, xr, v, o << 1, l, mid); else if(xl > mid) upd(xl, xr, v, o << 1 | 1, mid + 1, r);
	else upd(xl, mid, v, o << 1, l, mid), upd(mid + 1, xr, v, o << 1 | 1, mid + 1, r);
	val[o] = L :: LCA(val[o << 1], val[o << 1 | 1]);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = tot = in, Q = in; rep(i, 1, n) fa[i] = i;
	rep(i, 1, n - 1) {
		int u = in, v = in, w = in;
		ed[i] = make_tuple(w, u, v);
	}
	sort(ed + 1, ed + n);
	rep(i, 1, n - 1) {
		int w, u, v; tie(w, u, v) = ed[i];
		if(gf(u) == gf(v)) continue;
		++tot; u = gf(u), v = gf(v); G[tot].eb(u); G[tot].eb(v); wval[tot] = w;
		fa[u] = tot; fa[v] = tot; fa[tot] = tot;
	} dep[tot] = 1; dfs(tot); L :: init();
	build();
	while(Q--) {
		int op = in, x = in, y;
		if(op != 3) y = in;
		if(op == 1) upd(x, y, 1);
		else if(op == 2) upd(x, y, 0);
		else {
			int t = val[1];
			if(t == 0 || (t == x)) puts("-1");
			else printf("%d\n", wval[L :: LCA(x, t)]);
		}
	}
	return 0;
}
