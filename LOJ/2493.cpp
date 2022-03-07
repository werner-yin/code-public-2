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

struct node {
	int cnt0, cnt1, l0, l1, r0, r1, tl, tr, L[2][2], R[2][2];
	ll tot;
} val[N << 2];

node operator + (const node &a, const node &b) {
	node c; c.cnt0 = a.cnt0 + b.cnt0; c.cnt1 = a.cnt1 + b.cnt1; c.tot = a.tot + b.tot; c.tl = a.tl; c.tr = b.tr;
	c.l0 = a.cnt1 ? a.l0 : a.l0 + b.l0; c.l1 = a.cnt1 ? a.l1 : a.l1 + b.l1; if(a.cnt1 == 1) c.l1 += b.l0;
	c.r0 = b.cnt1 ? b.r0 : b.r0 + a.r0; c.r1 = b.cnt1 ? b.r1 : b.r1 + a.r1; if(b.cnt1 == 1) c.r1 += a.r0;
	rep(i, 0, 1) rep(j, 0, 1) c.L[i][j] = a.L[i][j], c.R[i][j] = b.R[i][j];
	rep(i, 0, 1) rep(j, 0, 1) if(j + a.cnt0 <= 1) c.L[(a.cnt1 + i) & 1][j + a.cnt0] += b.L[i][j];
	rep(i, 0, 1) rep(j, 0, 1) if(j + b.cnt0 <= 1) c.R[(b.cnt1 + i) & 1][j + b.cnt0] += a.R[i][j];
	c.tot += 1ll * a.r0 * b.l1 + 1ll * a.r1 * b.l0;
	rep(i, 0, 1) rep(j, 0, 1)
		rep(k, 0, 1) if((i + k) & 1)
		rep(d, 0, 1) if(j + d <= 1)
			c.tot += 1ll * a.R[i][j] * b.L[k][d];
	c.tot -= (a.tr + b.tl) == 1; return c;
}

void init(int o, int v) {
	val[o].tl = val[o].tr = v; memset(val[o].L, 0, sizeof val[o].L); memset(val[o].R, 0, sizeof val[o].R);
	if(v == 1) {
		val[o].cnt0 = val[o].l0 = val[o].r0 = 0;
		val[o].cnt1 = val[o].l1 = val[o].r1 = 1;
		val[o].tot = 1; val[o].L[1][0] = 1; val[o].R[1][0] = 1;
	} else {
		val[o].cnt0 = val[o].l0 = val[o].r0 = 1;
		val[o].cnt1 = val[o].l1 = val[o].r1 = 0;
		val[o].tot = 0; val[o].L[0][1] = 1; val[o].R[0][1] = 1;
	}
}

int a[N], n, m;

void build(int o = 1, int l = 1, int r = n) {
	if(l == r) return init(o, a[l]), void(); int mid = (l + r) >> 1;
	build(o << 1, l, mid); build(o << 1 | 1, mid + 1, r); val[o] = val[o << 1] + val[o << 1 | 1];
}

void upd(int p, int o = 1, int l = 1, int r = n) {
	if(l == r) return init(o, a[l]), void(); int mid = (l + r) >> 1;
	if(p <= mid) upd(p, o << 1, l, mid); else upd(p, o << 1 | 1, mid + 1, r); val[o] = val[o << 1] + val[o << 1 | 1];
}

node query(int xl, int xr, int o = 1, int l = 1, int r = n) {
	if(xl == l && r == xr) return val[o]; int mid = (l + r) >> 1;
	if(xr <= mid) return query(xl, xr, o << 1, l, mid); else if(xl > mid) return query(xl, xr, o << 1 | 1, mid + 1, r);
	else return query(xl, mid, o << 1, l, mid) + query(mid + 1, xr, o << 1 | 1, mid + 1, r);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; rep(i, 1, n) a[i] = in; build(); m = in;
	while(m--) {
		int op = in, l = in, r;
		if(op == 1) a[l] ^= 1, upd(l);
		else r = in, printf("%lld\n", 1ll * (r - l + 1) * (r - l + 2) / 2 - query(l, r).tot);
	}
	return 0;
}
