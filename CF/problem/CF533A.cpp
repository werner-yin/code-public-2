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

int n, h[N], s[N], m, mn[N], mnn[N], mnp[N];
vec G[N], lp[N];

void dfs(int x, int p) {
	mn[x] = mn[p]; mnn[x] = mnn[p]; mnp[x] = mnp[p]; 
	if(h[x] <= mn[x]) mnp[x] = x, mnn[x] = mn[x], mn[x] = h[x];
	else chkmin(mnn[x], h[x]);
	if(mnp[x]) lp[mnp[x]].eb(x);
	for(auto y : G[x]) if(y ^ p) dfs(y, x);
}

namespace seg {
	int val[N << 2], tg[N << 2];
	void pt(int o, int v) { val[o] += v; tg[o] += v; }
	void pu(int o) { val[o] = min(val[o << 1], val[o << 1 | 1]); }
	void pd(int o) { if(tg[o]) pt(o << 1, tg[o]), pt(o << 1 | 1, tg[o]), tg[o] = 0; }
	void upd(int xl, int xr, int v, int o = 1, int l = 1, int r = m) {
		if(xl <= l && r <= xr) return pt(o, v), void(); int mid = l + r >> 1; pd(o);
		if(xl <= mid) upd(xl, xr, v, o << 1, l, mid);
		if(xr > mid) upd(xl, xr, v, o << 1 | 1, mid + 1, r);
		pu(o);
	}
	int query(int pos, int o = 1, int l = 1, int r = m) {
		if(l == r) return val[o]; int mid = l + r >> 1; pd(o);
		if(pos <= mid) return query(pos, o << 1, l, mid);
		else return query(pos, o << 1 | 1, mid + 1, r);
	}
}

void modify(int x, int v) {
	int p = upper_bound(s + 1, s + m + 1, x) - s - 1;
	if(p > 0) seg :: upd(1, p, v);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) h[i] = in; rep(i, 2, n) { int u = in, v = in; G[u].eb(v); G[v].eb(u); }
	m = in; rep(i, 1, m) s[i] = in; sort(s + 1, s + m + 1);
	mn[0] = mnn[0] = 2e9; dfs(1, 0); rep(i, 1, n) modify(mn[i], 1);
	rep(i, 1, m) seg :: upd(1, i, -1); int limpos = -1;
	per(i, m, 1) if(seg :: query(i) < 0) { limpos = i; break; }
	if(limpos == -1) return puts("0"), 0;
	int ans = 0x3f3f3f3f;
	rep(i, 1, n) {
		for(auto v : lp[i]) modify(h[i], -1), modify(min(mnn[v], s[limpos]), 1);
		if(seg :: val[1] >= 0) chkmin(ans, s[limpos] - h[i]);
		for(auto v : lp[i]) modify(min(mnn[v], s[limpos]), -1), modify(h[i], 1);
	} if(ans >= 0x3f3f3f3f) ans = -1; printf("%d\n", ans);
	return 0;
}
