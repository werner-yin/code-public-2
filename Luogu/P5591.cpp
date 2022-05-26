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

const int N = 2e6 + 10;
constexpr int mod = 998244353;
//constexpr int mod = 1e9 + 7;

int reduce(int x) {
	if(x < 0) x += mod;
	if(x >= mod) x -= mod;
	return x;
}

template < typename T > T qp(T x, ll t) { t %= mod - 1; if(t < 0) t += mod - 1; T res = 1; for(; t; t >>= 1, x *= x) if(t & 1) res *= x; return res; }

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

Z fac[N], ifac[N];
Z C(int x, int y) { return x < 0 || y < 0 || x < y ? Z(0) : fac[x] * ifac[y] * ifac[x - y]; }
void init(int l) {
	fac[0] = 1; rep(i, 1, l) fac[i] = fac[i - 1] * Z(i); ifac[l] = fac[l].inv();
	per(i, l - 1, 0) ifac[i] = ifac[i + 1] * Z(i + 1);
}

int n, p, K;
Z wk[N], ans, pt[N];

int main() {
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
#endif
	n = in, p = in, K = in; wk[0] = 1; wk[1] = qp(Z(3), (mod - 1) / K);
	rep(i, 2, K - 1) wk[i] = wk[i - 1] * wk[1];
	for(int t = 1; t <= K; t <<= 1) {
		Z vt = t, s = 0;
		rep(j, 0, K - 1) {
			s += wk[j];
			j += t - 1;
		} pt[t] = s * vt;
	}
	//cerr << (qp(Z(p + 1), n - 1) * n * p).val() << endl;
	//rep(j, 0, K - 1) 
	//	ans += qp(p + wk[j] + 1, n) * pt[__gcd(j, K)];
	//ans = 0; init(n);
	/*
	rep(i, 0, n) ans += C(n, i) * qp(Z(p), i) * (i % K);
	*/
	/*
	rep(j, 0, K - 1) {
		Z pt = qp(p + wk[j] + 1, n), vt = 0;
		rep(d, 0, K - 1) vt += qp(wk[1], -1ll * d * j) * d;
		//cerr << vt.val() << " " << (::pt[__gcd(j, K)]).val() << endl;
		//assert(vt.val() == ::pt[__gcd(j, K)].val());
		ans += pt * vt;
	}
	*/
	rep(d, 0, K - 1) rep(j, 0, K - 1)
		//rep(i, 0, n) ans += d * C(n, i) * qp(Z(p), i) * qp(wk[1], 1ll * j * i - j * d);
		ans += qp(wk[1], -1ll * d * j) * qp(p * wk[j] + 1, n) * d;
	ans /= K; ans = qp(Z(p + 1), n - 1) * n * p - ans; ans /= K; cout << ans.val() << endl;
	return 0;
}
