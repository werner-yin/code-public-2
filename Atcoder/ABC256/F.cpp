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

constexpr int mod = 998244353;
//constexpr int mod = 1e9 + 7;

int reduce(int x) {
	if(x < 0) x += mod;
	if(x >= mod) x -= mod;
	return x;
}

template < typename T > T qp(T x, ll t) { T res = 1; for(; t; t >>= 1, x *= x) if(t & 1) res *= x; return res; }

struct Z { // modint
	int x;
	Z(int x = 0) : x(reduce(x)) {}
	Z(ll x) : x(reduce(x % mod)) {}
	Z operator -() const { return Z(reduce(mod - x)); }
	int val() { return x; }
	Z inv() const { assert(x); return qp(*this, mod - 2); }
	Z &operator += (const Z &t) { x = reduce(x + t.x); return *this; }
	Z &operator -= (const Z &t) { x = reduce(x - t.x); return *this; }
	Z &operator *= (const Z &t) { x = (ll)x * t.x % mod; return *this; }
	Z &operator /= (const Z &t) { return *this *= t.inv(); }
	friend Z operator + (const Z &a, const Z &b) { Z res = a; res += b; return res; }
	friend Z operator - (const Z &a, const Z &b) { Z res = a; res -= b; return res; }
	friend Z operator * (const Z &a, const Z &b) { Z res = a; res *= b; return res; }
	friend Z operator / (const Z &a, const Z &b) { Z res = a; res /= b; return res; }
};

Z S(ll x) { return x; return x * (x - 1) / 2; }

Z T(ll l, ll r) { return S(r) - S(l - 1) + r - l + 1 - r  + l - 1; }

int n, Q, a[N];

struct node {
	int l, r; Z sum1, sum2, sum3;
	node(int l = 0, int r = 0, Z sum1 = 0, Z sum2 = 0, Z sum3 = 0) : l(l), r(r), sum1(sum1), sum2(sum2), sum3(sum3) { }
	void setup(int p) { l = r = p; sum1 = Z(a[l]) * l * l, sum2 = Z(a[l]) * l, sum3 = a[l]; }
	node &operator += (node t) {
		r = t.r; sum1 += t.sum1, sum2 += t.sum2, sum3 += t.sum3;
		return *this;
	}
	friend node operator + (node a, node b) { node ret = a; ret += b; return ret; }
} v[N];

template < int N, class node > struct segtree {
	node val[N << 2];
	void pu(int o) { val[o] = val[o << 1] + val[o << 1 | 1]; }
	void pd(int o) { }
	void upd(int xl, int xr, int o = 1) {
		if(xl <= val[o].l && val[o].r <= xr) return val[o].setup(val[o].l), void(); int mid = val[o].l + val[o].r >> 1; pd(o);
		if(xl <= mid) upd(xl, xr, o << 1); if(xr > mid) upd(xl, xr, o << 1 | 1); pu(o);
	}
	node query(int xl, int xr, int o = 1) {
		if(xl <= val[o].l && val[o].r <= xr) return val[o]; int mid = val[o].l + val[o].r >> 1; pd(o); node ans;
		if(xl <= mid) ans += query(xl, xr, o << 1); if(xr > mid) ans += query(xl, xr, o << 1 | 1); return ans;
	}
	void init(node *a, int n) {
		function< void(int, int, int) > build =
			[&](int l, int r, int o) {
				if(l == r) return val[o] = a[l], void(); int mid = l + r >> 1;
				build(l, mid, o << 1), build(mid + 1, r, o << 1 | 1); pu(o);
			};
		build(1, n, 1);
	}
};

segtree < 200010, node > V;

const Z inv2 = Z(2).inv();

Z get(int x, node v) {
	Z ans = v.sum1 + v.sum2 * (-2 * x - 3) + v.sum3 * (1ll * x * x + 3 * x + 2);
	ans *= inv2;
	return ans;
}

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, Q = in; rep(i, 1, n) a[i] = in;
	rep(i, 1, n) v[i].setup(i);
	V.init(v, n);
	while(Q--) {
		int op = in, x = in;
		if(op == 1) a[x] = in, V.upd(x, x);
		else printf("%d\n", get(x, V.query(1, x)).val());
	}
	return 0;
}
