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

const int T = 131072;
const Z inv2 = Z(2).inv();

int n, a[N], b[N], c[N], K;
Z x, y, z;
Z f[N], g[N], h[N];

void FWT(Z *f, int fl = 1) {
	for(int h = 2; h <= 1 << K; h <<= 1) {
		for(int i = 0, j = h >> 1; i < (1 << K); i += h) {
			for(int k = 0; k < j; k++) {
				Z u = f[i | k], v = f[i | j | k];
				f[i | k] = u + v, f[i | j | k] = u - v;
			}
		}
	}
	if(fl == -1) {
		Z t = Z(1 << K).inv();
		rep(i, 0, (1 << K) - 1) f[i] *= t;
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, K = in, x = in, y = in, z = in;
	rep(i, 1, n) {
		a[i] = in, b[i] = in, c[i] = in;
		b[i] ^= a[i], c[i] ^= a[i];
		f[b[i]] += 1, g[c[i]] += 1, h[b[i] ^ c[i]] += 1;
	}
	FWT(f); FWT(g); FWT(h);
	rep(i, 0, (1 << K) - 1) {
		ll l1 = f[i].val(), l2 = g[i].val(), l3 = h[i].val();
		if(l1 > n) l1 -= mod; if(l2 > n) l2 -= mod; if(l3 > n) l3 -= mod;
		l1 = (n + l1) / 2, l2 = (n + l2) / 2, l3 = (n + l3) / 2;
		ll u = (l1 + l2 + l3 - n) / 2, v = l1 - u, w = l2 - u, t = l3 - u;
		f[i] = qp(x + y + z, u) * qp(x + y - z, v) * qp(x - y + z, w) * qp(x - y - z, t);
	}
	FWT(f, -1); int t = 0; rep(i, 1, n) t ^= a[i];
	rep(i, 0, (1 << K) - 1) printf("%d ", f[i ^ t].val()); puts("");
	return 0;
}
