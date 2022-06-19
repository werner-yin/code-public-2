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

int n, Q;
int x[N];

ll mx[N << 2], mn[N << 2], cover[N << 2], add[N << 2], sum[N << 2];
int l[N << 2], r[N << 2];

void cv(int o, ll v) { cover[o] = v; add[o] = 0; mx[o] = mn[o] = v; sum[o] = 1ll * (r[o] - l[o] + 1) * v; }
//void ad(int o, ll v) { if(cover[o]) cover[o] += v; else add[o] += v, sum[o] += 1ll * (r[o] - l[o] + 1) * v; }
void pu(int o) {
	mx[o] = max(mx[o << 1], mx[o << 1 | 1]), mn[o] = min(mn[o << 1], mn[o << 1 | 1]);
	sum[o] = sum[o << 1] + sum[o << 1 | 1];
}

void pd(int x) {
	if(cover[x] != -1) cv(x << 1, cover[x]), cv(x << 1 | 1, cover[x]), cover[x] = -1;
}

void build(int o = 1, int l = 1, int r = n) {
	cover[o] = -1; ::l[o] = l, ::r[o] = r; if(l == r) return mx[o] = mn[o] = sum[o] = x[l], void(); int mid = l + r >> 1;
	build(o << 1, l, mid); build(o << 1 | 1, mid + 1, r); pu(o);
}

void cvit(int xl, int xr, int v, int o = 1, int l = 1, int r = n) {
	if(xl <= l && r <= xr) return cv(o, v); int mid = l + r >> 1; pd(o);
	if(xl <= mid) cvit(xl, xr, v, o << 1, l, mid); if(xr > mid) cvit(xl, xr, v, o << 1 | 1, mid + 1, r); pu(o);
}

void getdiv(int v, int o) {
	int a = mn[o] / v, b = mx[o] / v;
	if(a == b) return cv(o, a);
	else {
		pd(o); getdiv(v, o << 1), getdiv(v, o << 1 | 1); pu(o);
	}
}

void div(int xl, int xr, int v, int o = 1, int l = 1, int r = n) {
	if(xl <= l && r <= xr) return getdiv(v, o), void(); int mid = l + r >> 1; pd(o);
	if(xl <= mid) div(xl, xr, v, o << 1, l, mid); if(xr > mid) div(xl, xr, v, o << 1 | 1, mid + 1, r); pu(o);
}

ll query(int xl, int xr, int o = 1, int l = 1, int r = n) {
	if(xl <= l && r <= xr) return sum[o]; int mid = l + r >> 1; pd(o); ll ans = 0;
	if(xl <= mid) ans += query(xl, xr, o << 1, l, mid); if(xr > mid) ans += query(xl, xr, o << 1 | 1, mid + 1, r); return ans;
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, Q = in; rep(i, 1, n) x[i] = in;
	build();
	while(Q--) {
		int op = in, L = in, R = in;
		if(op == 1) div(L, R, in);
		else if(op == 2) cvit(L, R, in);
		else printf("%lld\n", query(L, R));
	}
	return 0;
}
