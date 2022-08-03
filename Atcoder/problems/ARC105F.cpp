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
	int val() const { return x; }
	Z inv() const { assert(x); return qp(*this, mod - 2); }
	Z &operator += (const Z &t) { x = reduce(x + t.x); return *this; }
	Z &operator -= (const Z &t) { x = reduce(x - t.x); return *this; }
	Z &operator *= (const Z &t) { x = (ll)x * t.x % mod; return *this; }
	Z &operator /= (const Z &t) { return *this *= t.inv(); }
	friend Z operator + (const Z &a, const Z &b) { Z res = a; res += b; return res; }
	friend Z operator - (const Z &a, const Z &b) { Z res = a; res -= b; return res; }
	friend Z operator * (const Z &a, const Z &b) { Z res = a; res *= b; return res; }
	friend Z operator / (const Z &a, const Z &b) { Z res = a; res /= b; return res; }
	friend ostream & operator << (ostream &out, const Z &x) {
		out << x.val();
		return out;
	}
};


Z fac[N], ifac[N];
Z C(int x, int y) { return x < 0 || y < 0 || x < y ? Z(0) : fac[x] * ifac[y] * ifac[x - y]; }
void init(int l) {
	fac[0] = 1; rep(i, 1, l) fac[i] = fac[i - 1] * Z(i); ifac[l] = fac[l].inv();
	per(i, l - 1, 0) ifac[i] = ifac[i + 1] * Z(i + 1);
}

/* prime, mu, phi */
int mu[N], phi[N], pnum, pri[N];
bool v[N];

void shai(int l) {
	mu[1] = phi[1] = 1;
	rep(i, 2, l) {
		if(!v[i]) pri[++pnum] = i, mu[i] = -1, phi[i] = i - 1;
		rep(j, 1, pnum) {
			int t = i * pri[j]; if(t > l) break; v[t] = 1; 
			if(i % pri[j] == 0) { mu[t] = 0, phi[t] = phi[i] * pri[j]; break; }
			phi[t] = phi[i] * phi[pri[j]], mu[t] = -mu[i];
		}
	} 
}

Z f[1 << 17], g[1 << 17], pw[400];
int cnt[1 << 17], n, m, U;

int main() {
#ifdef YJR_2333_TEST
	freopen("1.in", "r", stdin);
#endif
	n = in, m = in; U = 1 << n; U--;
	pw[0] = 1; rep(i, 1, m) pw[i] = pw[i - 1] * 2;
	rep(i, 1, m) {
		int u = in - 1, v = in - 1;
		cnt[(1 << u) | (1 << v)] += 1;
	}
	rep(i, 0, n - 1)
		rep(j, 0, U) if(j >> i & 1)
		cnt[j] += cnt[j ^ 1 << i];
	rep(i, 1, U) {
		for(int s = i; ; s = (s - 1) & i) {
			f[i] += pw[cnt[i] - cnt[s] - cnt[s ^ i]];
			if(s == 0) break;
		} g[i] = f[i]; 
		int x = __builtin_ctz(i);
		for(int s = (i - 1) & i; s; s = (s - 1) & i)
			if(s >> x & 1)
				g[i] -= g[s] * f[s ^ i];
	} Z ans = g[U]; cout << ans / 2 << endl;
	return 0;
}
