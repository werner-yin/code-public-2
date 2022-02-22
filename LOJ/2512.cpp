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

const int N = 2e5 + 10;
const int mod = 1e9 + 7;
const int inv2 = (mod + 1) >> 1;

using ar3 = array < int, 3 >;

ar3 val[N << 2], tg[N << 2], sum[N << 2];
int a[N], s[N], ss[N], n, m;

ar3 operator * (ar3 a, ar3 b) {
	ar3 c; rep(i, 0, 2) c[i] = 1ll * a[i] * b[i] % mod;
	return c;
}

ar3 operator + (ar3 a, ar3 b) {
	ar3 c; rep(i, 0, 2) c[i] = (a[i] + b[i]) % mod;
	return c;
}

void pt(int o, ar3 v) { tg[o] = tg[o] + v; val[o] = val[o] + sum[o] * v; }
void pd(int o) {
	bool fl = 0; rep(i, 0, 2) fl |= tg[o][i];
	if(!fl) return; pt(o << 1, tg[o]); pt(o << 1 | 1, tg[o]);
	rep(i, 0, 2) tg[o][i] = 0;
}
void upd(int xl, int xr, ar3 v, int o = 1, int l = 1, int r = n) {
	if(xl <= l && r <= xr) return pt(o, v); int mid = l + r >> 1; pd(o);
	if(xl <= mid) upd(xl, xr, v, o << 1, l, mid); if(xr > mid) upd(xl, xr, v, o << 1 | 1, mid + 1, r);
	val[o] = val[o << 1] + val[o << 1 | 1];
}
void init(int o, int p) {
	val[o][0] = ss[p]; sum[o][2] = 1; sum[o][1] = p; sum[o][0] = 1ll * p * p % mod;
}
void build(int o = 1, int l = 1, int r = n) {
	if(l == r) return init(o, l); int mid = l + r >> 1;
	build(o << 1, l, mid); build(o << 1 | 1, mid + 1, r);
	val[o] = val[o << 1] + val[o << 1 | 1]; sum[o] = sum[o << 1] + sum[o << 1 | 1];
}
ar3 query(int xl, int xr, int o = 1, int l = 1, int r = n) {
	if(xl <= l && r <= xr) return val[o]; int mid = l + r >> 1; pd(o);
	ar3 ans = { 0, 0, 0 }; if(xl <= mid) ans = ans + query(xl, xr, o << 1, l, mid);
	if(xr > mid) ans = ans + query(xl, xr, o << 1 | 1, mid + 1, r);
	return ans;
}

void modify(int l, int r, int d) {
	upd(l, r, {
			1ll * d * inv2 % mod,
			(mod - 1ll * (mod + 2 * l - 3) % mod * d % mod) % mod * inv2 % mod,
			1ll * (l - 1) * (l - 2) % mod * inv2 % mod * d % mod
		});
	/*
	rep(i, l, r) (ss[i] += 1ll * (i - l + 1) * (i - l + 2) / 2 % mod * d % mod) %= mod;
	rep(i, r + 1, n)
		(ss[i] += 1ll * (r - l + 1) * (r - l + 2) / 2 % mod * d % mod + 1ll * (r - l + 1) * d % mod * (i - r) % mod) %= mod;
	*/
	if(r < n)
		upd(r + 1, n, {
				0,
				1ll * (r - l + 1) * d % mod,
				(1ll * (r - l + 1) * (r - l + 2) / 2 % mod * d % mod + mod - 1ll * (r - l + 1) * r % mod * d % mod) % mod
			});
}

int get(ar3 v) { int res = 0; rep(i, 0, 2) res = (res + v[i]) % mod; return res; }

int qry(int l, int r) {
	int res = 0, len = r - l + 1;
	res = (res + 1ll * get(query(n, n)) * len % mod) % mod;
	if(max(l - 1, 1) <= r - 1) res = (res + mod - get(query(max(l - 1, 1), r - 1))) % mod;
	if(l != n) res = (res + mod - get(query(max(1, n - r), n - l))) % mod;
	return res;
}

/*
ll tq(int l, int r) { int res = 0; rep(i, l, r) res = (res + ss[i]) % mod; return res; }
int qqry(int l, int r) {
	int res = 0, len = r - l + 1;
	res = (res + 1ll * tq(n, n) * len % mod) % mod;
	if(max(l - 1, 1) <= r - 1) res = (res + mod - tq(max(l - 1, 1), r - 1)) % mod;
	if(l != n) res = (res + mod - tq(max(1, n - r), n - l)) % mod;
	return res;
}
*/

signed main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in; rep(i, 1, n) a[i] = in, s[i] = (s[i - 1] + a[i]) % mod, ss[i] = (ss[i - 1] + s[i]) % mod;
	build(); 
	while(m--) {
		int op = in, l = in, r = in, d; if(l > r) swap(l, r);
		if(op == 1) d = in, modify(l, r, d);
		else printf("%d\n", qry(l, r)); 
	}
	return 0;
}
