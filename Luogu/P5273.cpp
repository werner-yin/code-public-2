#include <bits/stdc++.h>

#define eb emplace_back
#define ep emplace
#define fi first
#define se second
#define in read<int>()
#define lin read<ll>()
#define rep(i, x, y) for(int i = (x); i <= (y); i++)
#define per(i, x, y) for(int i = (x); i >= (y); i--)
#define deg(x) int(x.size())

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

template < typename T > T qp(T x, ll t = mod - 2) { T res = 1; for(; t; t >>= 1, x *= x) if(t & 1) res *= x; return res; }

struct Z { // modint
	int x;
	Z(int x = 0) : x(reduce(x)) {}
	Z(ll x) : x(reduce(x % mod)) {}
	Z operator -() const { return Z(reduce(mod - x)); }
	int val() const { return x; }
	Z inv() const { assert(x); return qp(*this); }
	Z &operator += (const Z &t) { x = reduce(x + t.x - mod); return *this; }
	Z &operator -= (const Z &t) { x = reduce(x - t.x); return *this; }
	Z &operator *= (const Z &t) { x = (ll)x * t.x % mod; return *this; }
	Z &operator /= (const Z &t) { return *this *= t.inv(); }
	friend Z operator + (const Z &a, const Z &b) { Z res = a; res += b; return res; }
	friend Z operator - (const Z &a, const Z &b) { Z res = a; res -= b; return res; }
	friend Z operator * (const Z &a, const Z &b) { Z res = a; res *= b; return res; }
	friend Z operator / (const Z &a, const Z &b) { Z res = a; res /= b; return res; }
};

Z fac[N], ifac[N];
Z C(int x, int y) { return x < 0 || y < 0 || x < y ? Z(0) : fac[x] * ifac[y] * ifac[x - y]; }
void init(int l) {
	fac[0] = 1; rep(i, 1, l) fac[i] = fac[i - 1] * Z(i); ifac[l] = fac[l].inv();
	per(i, l - 1, 0) ifac[i] = ifac[i + 1] * Z(i + 1);
}

using poly = vector < Z >;

int rev[N << 2], len;
Z A[N << 2], B[N << 2], w[N << 2];

void init_NTT(int l) {
	for(len = 1; len <= l + 2; len <<= 1);
	rep(i, 1, len - 1) rev[i] = rev[i >> 1] >> 1 | (i & 1 ? len >> 1 : 0);
	rep(i, 0, len - 1) A[i] = B[i] = 0;
}

void NTT(Z *f, int fl = 1) {
	rep(i, 1, len - 1) if(i < rev[i]) swap(f[i], f[rev[i]]);
	for(int h = 2; h <= len; h <<= 1) {
		Z wn = qp(Z(G), (mod - 1) / h), ww = 1;
		for(int k = 0, j = h >> 1; k < j; k++) w[k] = ww, ww = ww * wn;
		for(int i = 0, j = h >> 1; i < len; i += h) {
			for(int k = 0; k < j; k++) {
				Z u = f[i | k], v = f[i | k | j] * w[k];
				f[i | k] = u + v; f[i | k | j] = u - v;
			}
		}
	} if(fl == -1) {
		reverse(f + 1, f + len); Z t = len; t = t.inv();
		rep(i, 0, len - 1) f[i] *= t;
	}
}

poly operator + (const poly &a, const poly &b) {
	poly c = a; c.resize(max(deg(a), deg(b)));
	rep(i, 0, deg(b) - 1) c[i] += b[i];
	return c;
}

poly operator - (const poly &a, const poly &b) {
	poly c = a; c.resize(max(deg(a), deg(b)));
	rep(i, 0, deg(b) - 1) c[i] -= b[i];
	return c;
}

poly operator * (const poly &a, Z t) { poly c; for(const auto &v : a) c.eb(v * t); return c; }

poly operator * (const poly &a, const poly &b) {
	init_NTT(max(deg(a), deg(b)) * 2);
	rep(i, 0, deg(a) - 1) A[i] = a[i]; rep(i, 0, deg(b) - 1) B[i] = b[i];
	NTT(A), NTT(B); rep(i, 0, len - 1) A[i] = A[i] * B[i]; NTT(A, -1);
	poly c; rep(i, 0, len - 1) c.eb(A[i]); c.resize(deg(a) + deg(b) - 1); return c;
}

void getinv(const poly &a, poly &b) {
	if(deg(a) == 1) b.eb(qp(a.front()));
	else {
		poly t = a; t.resize(deg(a) + 1 >> 1); getinv(t, b);
		init_NTT(deg(a) * 2);
		rep(i, 0, deg(a) - 1) A[i] = a[i]; rep(i, 0, deg(b) - 1) B[i] = b[i];
		NTT(A), NTT(B); rep(i, 0, len - 1) A[i] = B[i] * 2 - B[i] * B[i] * A[i];
		NTT(A, -1); b.resize(deg(a)); rep(i, 0, deg(a) - 1) b[i] = A[i]; 
	}
}

poly inv(const poly &a) { poly b; getinv(a, b); return b; }

poly operator / (const poly &a, const poly &b) { return a * inv(b); }

void getsqrt(const poly &a, poly &b) {
	if(deg(a) == 1) assert(a.front().val() == 1), b.eb(1);
	else {
		poly t = a; t.resize(deg(a) + 1 >> 1); getsqrt(t, b); b.resize(deg(a));
		b = (b + a / b) * Z(2).inv(); b.resize(deg(a));
	}
}

poly sqrt(const poly &a) { poly b; getsqrt(a, b); return b; }

poly der(const poly &a) { poly b; rep(i, 1, deg(a) - 1) b.eb(a[i] * i); return b; }

poly inte(const poly &a) { poly b; b.eb(0); rep(i, 0, deg(a) - 1) b.eb(a[i] / (i + 1)); return b; }

poly ln(const poly &a) { assert(a.front().val() == 1); return inte(der(a) / a); }

int n, m, k1, k2;

void getexp(const poly &a, poly &b) {
	if(deg(a) == 1) assert(a.front().val() == 0), b.eb(1);
	else {
		poly t = a; t.resize(deg(a) + 1 >> 1); getexp(t, b); b.resize(deg(a));
		b = b + b * (a - ln(b)); b.resize(deg(a));
	}
}

poly exp(const poly &a) { poly b; getexp(a, b); return b; }

poly div(poly a, poly b) { // a / b = c
	int t = deg(a) - deg(b) + 1; reverse(a.begin(), a.end()); reverse(b.begin(), b.end());
	a.resize(t); b.resize(t); poly c = a / b; c.resize(t); reverse(c.begin(), c.end()); return c;
}

ll tk = 0;

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in; char ch = getchar(); while(!isdigit(ch)) ch = getchar();
	while(isdigit(ch)) {
		int x = ch - '0';
		k1 = (k1 * 10ll + x) % mod, k2 = (k2 * 10ll + x) % (mod - 1);
		if(tk < 1e6) tk = tk * 10ll + x;
		ch = getchar(); 
	}
	poly f; rep(i, 1, n) f.eb(in);
	reverse(f.begin(), f.end());
	int shift = 0; while(f.size() && f.back().val() == 0) f.pop_back(), shift++;
	if(1ll * shift * tk > n || !f.size()) { rep(i, 1, n) printf("%d ", 0); return 0;	}
	reverse(f.begin(), f.end()); Z t = f.front().inv(), pt = qp(f.front(), k2); f = f * t; f = exp(ln(f) * k1);
	f = f * pt; reverse(f.begin(), f.end()); rep(i, 1, shift * k1) f.eb(0); reverse(f.begin(), f.end()); f.resize(n);
	rep(i, 0, n - 1) printf("%d ", f[i].val()); puts(""); return 0;
}
