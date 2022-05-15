#include <bits/stdc++.h>

#define eb emplace_back
#define ep emplace
#define fi first
#define se second
#define in read<int>()
#define lin read<ll>()
#define rep(i, x, y) for(int i = (x); i <= (y); i++)
#define per(i, x, y) for(int i = (x); i >= (y); i--)
#define sz(x) int(x.size())

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
constexpr int G = 3;
//constexpr int mod = 1e9 + 7;

int reduce(int x) {
	x += x >> 31 & mod;
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
	Z &operator += (const Z &t) { x = reduce(x + t.x - mod); return *this; }
	Z &operator -= (const Z &t) { x = reduce(x - t.x); return *this; }
	Z &operator *= (const Z &t) { x = (ll)x * t.x % mod; return *this; }
	Z &operator /= (const Z &t) { return *this *= t.inv(); }
	friend Z operator + (const Z &a, const Z &b) { Z res = a; res += b; return res; }
	friend Z operator - (const Z &a, const Z &b) { Z res = a; res -= b; return res; }
	friend Z operator * (const Z &a, const Z &b) { Z res = a; res *= b; return res; }
	friend Z operator / (const Z &a, const Z &b) { Z res = a; res /= b; return res; }
};

using poly = vector < Z >;

int rev[N << 2], len;
Z A[N << 2], B[N << 2];

void init(int l) {
	for(len = 1; len <= l + 2; len <<= 1);
	rep(i, 1, len - 1) rev[i] = rev[i >> 1] >> 1 | (i & 1 ? len >> 1 : 0);
	rep(i, 0, len - 1) A[i] = B[i] = 0;
}

void NTT(Z *f, int fl = 1) {
	rep(i, 1, len - 1) if(i < rev[i]) swap(f[i], f[rev[i]]);
	for(int h = 2; h <= len; h <<= 1) {
		Z wn = qp(Z(G), (mod - 1) / h);
		for(int i = 0, j = h >> 1; i < len; i += h) {
			Z ww = 1;
			for(int k = i; k < i + j; k++) {
				Z u = f[k], v = f[k + j] * ww; ww *= wn;
				f[k] = u + v; f[k + j] = u - v;
			}
		}
	} if(fl == -1) {
		reverse(f + 1, f + len); Z t = len; t = t.inv();
		rep(i, 0, len - 1) f[i] *= t;
	}
}

poly operator * (const poly a, const poly b) {
	init(max(a.size(), b.size()) * 2);
	rep(i, 0, sz(a) - 1) A[i] = a[i]; 
	rep(i, 0, sz(b) - 1) B[i] = b[i]; 
	NTT(A), NTT(B); rep(i, 0, len - 1) A[i] = A[i] * B[i]; NTT(A, -1);
	poly c; rep(i, 0, len - 1) c.eb(A[i]); /*c.resize(a.size() + b.size() - 1); */return c;
}

Z fac[N], ifac[N], pw[N], ipw[N];
Z C(int x, int y) { return x < 0 || y < 0 || x < y ? Z(0) : fac[x] * ifac[y] * ifac[x - y]; }
void tinit(int l) {
	fac[0] = 1, pw[0] = 1; rep(i, 1, l) fac[i] = fac[i - 1] * Z(i), pw[i] = pw[i - 1] * 2; ifac[l] = fac[l].inv(), ipw[l] = qp(pw[l], mod - 2);
	per(i, l - 1, 0) ifac[i] = ifac[i + 1] * Z(i + 1), ipw[i] = ipw[i + 1] * 2;
}

int n, m, D;

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	D = in, n = in, m = in; tinit(D);
	if(n - m * 2 >= D) return printf("%d\n", qp(Z(D), n).val()), 0;
	if(2 * m > n) return puts(0), 0;
	poly f, g; rep(i, 0, D) f.eb(ifac[i]), g.eb(qp(Z(D - 2 * i), n) * (i & 1 ? -1 : 1) * ifac[i]);
	g = f * g; rep(i, 0, D) g[i] = g[i] * fac[D] * ifac[D - i] * ipw[i] * fac[i];
	while(g.size() > D + 1) g.pop_back();
	f.clear(); rep(i, 0, D) f.eb(ifac[i] * (i & 1 ? -1 : 1));
	reverse(g.begin(), g.end()); f = f * g; while(f.size() > D + 1) f.pop_back();
	reverse(f.begin(), f.end()); Z ans = 0; rep(i, 0, n - 2 * m) ans += f[i] * ifac[i]; cout << ans.val() << endl; return 0;
}
